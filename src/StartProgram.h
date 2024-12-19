#ifndef STARTPROGRAM_H
#define STARTPROGRAM_H
#include <iostream>
#include <condition_variable>

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

void startProgram()
{
    WeatherData weatherdata;
    TempSensor TemperatureSensor1;
    HumiditySensor HumiditySensor1;
    WindSensor WindSensor1;

    std::thread popWeatherData(populateWeatherData, std::ref(weatherdata), std::ref(TemperatureSensor1), std::ref(HumiditySensor1), std::ref(WindSensor1));

    printWeatherData(weatherdata);

    Running = false;
    popWeatherData.join();
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

#endif
