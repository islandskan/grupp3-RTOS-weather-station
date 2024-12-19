#ifndef STARTPROGRAM_H
#define STARTPROGRAM_H
#include <iostream>
#include <thread>
#include <mutex>
#include <atomic>
#include <memory>

#include "Sensor.h"
#include "TempSensor.h"
#include "HumiditySensor.h"
#include "WindSensor.h"

void printLatestSensorData(const std::vector<std::unique_ptr<Sensor>>& sensors, std::atomic<bool>& running, std::mutex& mtx);
void printStatistics(const std::vector<std::unique_ptr<Sensor>>& sensors, std::atomic<bool>& running, std::mutex& mtx);

void startProgram()
{
    std::vector<std::unique_ptr<Sensor>> sensors;
    std::atomic<bool> running = true;
    std::mutex mtx;
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

    std::thread t_printStatistics(printStatistics, std::ref(sensors), std::ref(running), std::ref(mtx));
    std::thread t_printLatest(printLatestSensorData, std::ref(sensors), std::ref(running), std::ref(mtx));
    std::this_thread::sleep_for(std::chrono::seconds(5));
    running = false;

    t_printStatistics.join();
    t_printLatest.join();
}

void printStatistics(const std::vector<std::unique_ptr<Sensor>>& sensors, std::atomic<bool>& running, std::mutex& mtx)
{
    while (running)
    {
        std::this_thread::sleep_for(std::chrono::seconds(10));
        std::lock_guard<std::mutex> lock(mtx);
        std::cout << "Sensor Statistical Data: " << std::endl;
        for (int i = 0; i < sensors.size(); i++)
        {
            std::cout << sensors[i]->getSensorType() << "\n";
            std::cout << "\n- Average: " << sensors[i]->getAverageData() << "\n"
                      << "- Minimum Data: " << sensors[i]->getMinimumData() << "\n"
                      << "- Maximum Data: " << sensors[i]->getMaxData() << "\n";
        }
    }
}

void printLatestSensorData(const std::vector<std::unique_ptr<Sensor>>& sensors, std::atomic<bool>& running, std::mutex& mtx)
{
    while (running)
    {
        std::this_thread::sleep_for(std::chrono::seconds(2));
        std::lock_guard<std::mutex> lock(mtx);
        std::cout << "Latest Sensor Data: " << std::endl;
        for (int i = 0; i < sensors.size(); ++i)
        {
            std::cout << sensors[i]->getSensorType() << ": " << sensors[i]->getLatestData() << "\n";
        }
    }
}

#endif
