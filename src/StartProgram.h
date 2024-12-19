#ifndef STARTPROGRAM_H
#define STARTPROGRAM_H
#include <iostream>
#include <condition_variable>
#include <typeinfo>

#include "Sensor.h"
#include "TempSensor.h"
#include "HumiditySensor.h"
#include "WindSensor.h"

bool Running = true;
bool newDataAvailable = false;
std::condition_variable cv;
std::mutex mutex;

struct WeatherData
{
    std::vector<float> TemperatureData;
    std::vector<float> HumidityData;
    std::vector<float> WindspeedData;
};

void populateWeatherData(WeatherData &weatherdata, TempSensor &TemperatureSensor1, HumiditySensor &HumiditySensor1, WindSensor &WindSensor1);
void printWeatherData(const WeatherData &weatherdata);
void printLatestSensorData(const std::vector<std::unique_ptr<Sensor>>& sensors);
void printSensorData(const std::vector<std::unique_ptr<Sensor>>& sensors);

void startProgram()
{
    /*
    WeatherData weatherdata;
    TempSensor TemperatureSensor1;
    HumiditySensor HumiditySensor1;
    WindSensor WindSensor1;
    // std::thread popWeatherData(populateWeatherData, std::ref(weatherdata), std::ref(TemperatureSensor1), std::ref(HumiditySensor1), std::ref(WindSensor1));    
    std::this_thread::sleep_for(std::chrono::seconds(2));
    std::cout << "Printing average data of Temperature Sensor 1: " << TemperatureSensor1.getAverageData() << std::endl;
    std::cout << "Printing maximum data of Temperature Sensor 1: " << TemperatureSensor1.getMaxData() << std::endl;
    std::cout << "Printing minimum data of Temperature Sensor 1: " << TemperatureSensor1.getMinimumData() << std::endl;
    printWeatherData(weatherdata);    
    std::vector<TempSensor> t_v;
    */

    std::vector<std::unique_ptr<Sensor>> sensors;
    for (int i = 0; i < 5; i++) 
    {
        sensors.emplace_back(std::make_unique<TempSensor>());
    }
    for (int i = 0; i < 5; i++) 
    {
        sensors.emplace_back(std::make_unique<HumiditySensor>());
    }
    for (int i = 0; i < 5; i++) 
    {
        sensors.emplace_back(std::make_unique<WindSensor>());
    }
    std::this_thread::sleep_for(std::chrono::seconds(5));
    printSensorData(sensors);
    printLatestSensorData(sensors);
    Running = false;

    // popWeatherData.join();
}

void populateWeatherData(WeatherData &weatherdata, TempSensor &TemperatureSensor1, HumiditySensor &HumiditySensor1, WindSensor &WindSensor1)
{
    while (Running)
    {
        {
            std::unique_lock<std::mutex> lock(mutex);
            weatherdata.TemperatureData = TemperatureSensor1.getData();
            weatherdata.HumidityData = HumiditySensor1.getData();
            weatherdata.WindspeedData = WindSensor1.getData();
            newDataAvailable = true;
        }
        std::this_thread::sleep_for(std::chrono::seconds(1));
        cv.notify_one();
    }
}

void printWeatherData(const WeatherData &weatherdata)
{
    while (Running)
    {
        std::unique_lock<std::mutex> lock(mutex);
        cv.wait(lock, [] {return newDataAvailable;});

        std::cout << "Temperature Data: ";
        for (const float &temp : weatherdata.TemperatureData)
        {
            std::cout << temp << " ";
        }
        std::cout << std::endl;

        std::cout << "Humidity Data: ";
        for (const float &humidity : weatherdata.HumidityData)
        {
            std::cout << humidity << " ";
        }
        std::cout << std::endl;

        std::cout << "Windspeed Data: ";
        for (const float &windspeed : weatherdata.WindspeedData)
        {
            std::cout << windspeed << " ";
        }
        std::cout << std::endl;

        newDataAvailable = false;
    }
}

void printSensorData(const std::vector<std::unique_ptr<Sensor>>& sensors)
{
    std::cout << "Sensor Data: " << std::endl;
    for (int i = 0; i < sensors.size(); i++)
    {
        if (typeid(*sensors[i]) == typeid(TempSensor)) 
        {
            std::cout << "Temperature Sensor " << i + 1 << ": ";
        }
        else if (typeid(*sensors[i]) == typeid(HumiditySensor)) 
        {
            std::cout << "Humidity Sensor " << i + 1 << ": ";
        }
        else if (typeid(*sensors[i]) == typeid(WindSensor)) 
        {
            std::cout << "Windspeed Sensor " << i + 1 << ": ";
        }
        for (const float& temperature : sensors[i]->getData())
        {
            std::cout << temperature << " ";
        }
        std::cout << std::endl;
    }
}

void printLatestSensorData(const std::vector<std::unique_ptr<Sensor>>& sensors)
{
    std::cout << "Latest temperature Data: " << std::endl;
    for (int i = 0; i < sensors.size(); ++i) 
    {
        if (typeid(*sensors[i]) == typeid(TempSensor))
        {
            std::cout << "Temperature Sensor " << i + 1 << ": ";
        }
        else if (typeid(*sensors[i]) == typeid(HumiditySensor))
        {
            std::cout << "Humidity Sensor " << i + 1 << ": ";
        }
        if (typeid(*sensors[i]) == typeid(WindSensor))
        {
            std::cout << "Windspeed Sensor " << i + 1 << ": ";
        }
        std::cout << sensors[i]->getLatestData() << std::endl;
    }    
}

#endif