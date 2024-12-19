#ifndef STARTPROGRAM_H
#define STARTPROGRAM_H
#include <iostream>
#include <typeinfo>

#include "Sensor.h"
#include "TempSensor.h"
#include "HumiditySensor.h"
#include "WindSensor.h"

bool Running = true;
bool newDataAvailable = false;

void printLatestSensorData(const std::vector<std::unique_ptr<Sensor>>& sensors);
void printSensorData(const std::vector<std::unique_ptr<Sensor>>& sensors);

void startProgram()
{
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

#endif
