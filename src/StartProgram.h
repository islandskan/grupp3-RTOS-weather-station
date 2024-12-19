#ifndef STARTPROGRAM_H
#define STARTPROGRAM_H
#include <iostream>
#include <typeinfo>

#include "Sensor.h"
#include "TempSensor.h"
#include "HumiditySensor.h"
#include "WindSensor.h"

bool Running = true;

void printLatestSensorData(const std::vector<std::unique_ptr<Sensor>>& sensors);
void printStatistics(const std::vector<std::unique_ptr<Sensor>>& sensors);

void startProgram()
{
    std::vector<std::unique_ptr<Sensor>> sensors;
    std::cout << "Runs you fool???" << std::endl;
    int runs;
    std::cin >> runs;
    for (int i = 0; i < runs; i++) 
    {
        sensors.emplace_back(std::make_unique<TempSensor>());
    }
    for (int i = 0; i < runs; i++) 
    {
        sensors.emplace_back(std::make_unique<HumiditySensor>());
    }
    for (int i = 0; i < runs; i++) 
    {
        sensors.emplace_back(std::make_unique<WindSensor>());
    }
    std::this_thread::sleep_for(std::chrono::seconds(5));
    std::thread t_printAllSensorData([&sensors] {printStatistics(sensors);});
    std::thread t_printLatestSensorData([&sensors] {printLatestSensorData(sensors);});
    t_printAllSensorData.join();
    t_printLatestSensorData.join();
}

void printStatistics(const std::vector<std::unique_ptr<Sensor>>& sensors)
{
    while (Running)
    {
        std::this_thread::sleep_for(std::chrono::seconds(10));
        std::cout << "Sensor Statistical Data: " << std::endl;
        for (int i = 0; i < sensors.size(); i++)
        {
            if (typeid(*sensors[i]) == typeid(TempSensor)) 
            {
                std::cout << "Temperature Sensor " << i + 1;
            }
            else if (typeid(*sensors[i]) == typeid(HumiditySensor)) 
            {
                std::cout << "Humidity Sensor " << i + 1;
            }
            else if (typeid(*sensors[i]) == typeid(WindSensor)) 
            {
                std::cout << "Windspeed Sensor " << i + 1;
            }
            std::cout << "\n- Average: " << sensors[i]->getAverageData() << "\n"
                      << "- Minimum Data: " << sensors[i]->getMinimumData() << "\n"
                      << "- Maximum Data: " << sensors[i]->getMaxData() << "\n";
        }
    }
}

void printLatestSensorData(const std::vector<std::unique_ptr<Sensor>>& sensors)
{
    while (Running)
    {
        std::this_thread::sleep_for(std::chrono::seconds(2));
        std::cout << "Latest Sensor Data: " << std::endl;
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
}

#endif
