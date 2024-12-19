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
std::vector<Sensor*> sensors;

// struct WeatherData
// {
//     std::vector<float> TemperatureData;
//     std::vector<float> HumidityData;
//     std::vector<float> WindspeedData;
// };

void printLatestData();
// void populateWeatherData(WeatherData &weatherdata, TempSensor &TemperatureSensor1, HumiditySensor &HumiditySensor1, WindSensor &WindSensor1);
// void printWeatherData(const WeatherData &weatherdata);
void printWeatherStatistics();

void startProgram()
{
    // std::vector<std::unique_ptr<TempSensor>> t_v;
    // for (int i = 0; i < 5; i++)
    // {
    //     t_v.emplace_back(std::make_unique<TempSensor>());
    // }

    // std::this_thread::sleep_for(std::chrono::seconds(5));

    // std::cout << "Temperature Data: " << std::endl;
    // for (int i = 0; i < t_v.size(); ++i)
    // {
    //     std::cout << "Sensor " << i + 1 << ": ";
    //     for (const float& temp : t_v[i]->getData())
    //     {
    //         std::cout << temp << " ";
    //     }
    //     std::cout << std::endl;
    // }
    // std::cout << "Latest temperature Data: " << std::endl;
    // for (int i = 0; i < t_v.size(); ++i)
    // {
    //     std::cout << "Sensor " << i + 1 << ": ";
    //     std::cout << t_v[i]->getLatestData();
    //     std::cout << std::endl;
    // }

    // WeatherData weatherdata;
    TempSensor TemperatureSensor1;
    HumiditySensor HumiditySensor1;
    WindSensor WindSensor1;

    sensors.push_back(&TemperatureSensor1);
    sensors.push_back(&HumiditySensor1);
    sensors.push_back(&WindSensor1);

    // std::thread popWeatherData(populateWeatherData, std::ref(weatherdata), std::ref(TemperatureSensor1), std::ref(HumiditySensor1), std::ref(WindSensor1));

    //printWeatherData(weatherdata);
    // printWeatherStatistics(weatherdata);
    printLatestData();
    printWeatherStatistics();

    Running = false;
    //popWeatherData.join();
}

void printLatestData()
{
    while(Running)
    {
        for (const auto& sensor : sensors)
        {
            if (auto* tempSensor = dynamic_cast<TempSensor*>(sensor)) // If the type is TempSensor
            {
                std::cout << "Temp:" << std::endl;
            }
            else if (auto* tempSensor = dynamic_cast<HumiditySensor*>(sensor)) // If the type is HumiditySensor
            {
                std::cout << "Humidity:" << std::endl;
            }
            else if (auto* tempSensor = dynamic_cast<WindSensor*>(sensor)) // If the type is WindSensor
            {
                std::cout << "Windspeed:" << std::endl;
            }
            std::cout << sensor->getLatestData() << std::endl;
        }
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }
}

// void populateWeatherData(WeatherData &weatherdata, TempSensor &TemperatureSensor1, HumiditySensor &HumiditySensor1, WindSensor &WindSensor1)
// {
//     while (Running)
//     {
//         {
//             std::unique_lock<std::mutex> lock(mutex);
//             weatherdata.TemperatureData = TemperatureSensor1.getData();
//             weatherdata.HumidityData = HumiditySensor1.getData();
//             weatherdata.WindspeedData = WindSensor1.getData();
//             newDataAvailable = true;
//         }
//         std::this_thread::sleep_for(std::chrono::seconds(1));
//         cv.notify_one();
//     }
// }

void printWeatherStatistics()
{
   while (Running)
    {
        std::unique_lock<std::mutex> lock(mutex);
        cv.wait(lock, [] {return newDataAvailable;});

        std::cout << "Average: \n";

        for (int i = 0; i < sensors.size(); ++i)
        {
            std::cout << sensors[i]->getAverageData() << "\n";
        }
        std::cout << "Minimum: \n";

        for (int i = 0; i < sensors.size(); ++i)
        {
            std::cout << sensors[i]->getMinimumData() << "\n";
        }
                std::cout << "Maximum: \n";

        for (int i = 0; i < sensors.size(); ++i)
        {
            std::cout << sensors[i]->getMaxData() << "\n";
        }

        newDataAvailable = false;
        std::this_thread::sleep_for(std::chrono::seconds(10));
    }
}

// void printWeatherData(const WeatherData &weatherdata)
// {
//     while (Running)
//     {
//         std::unique_lock<std::mutex> lock(mutex);
//         cv.wait(lock, [] {return newDataAvailable;});

//         std::cout << "Temperature Data: ";
//             weatherdata.TemperatureData.back();
//         for (const float &temp : weatherdata.TemperatureData)
//         {
//             std::cout << temp << " ";
//         }
//         std::cout << std::endl;

//         std::cout << "Humidity Data: ";
//         for (const float &humidity : weatherdata.HumidityData)
//         {
//             std::cout << humidity << " ";
//         }
//         std::cout << std::endl;

//         std::cout << "Windspeed Data: ";
//         for (const float &windspeed : weatherdata.WindspeedData)
//         {
//             std::cout << windspeed << " ";
//         }
//         std::cout << std::endl;

//         newDataAvailable = false;
//         std::this_thread::sleep_for(std::chrono::seconds(2));
//     }
// }

#endif
