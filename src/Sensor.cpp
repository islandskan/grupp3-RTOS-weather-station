#include "Sensor.h"

Sensor::Sensor() : mt(std::random_device{}()), Running(true)
{
    this->sensorThread = std::thread(&Sensor::runSensor, this);
    this->calculationThread = std::thread(&Sensor::calculateStatistics, this);
}

Sensor::~Sensor()
{
    Running = false;
    sensorThread.join();
    calculationThread.join();
}

std::vector<float> Sensor::getData()
{
    std::lock_guard<std::mutex> lock(sensorMutex);
    return dataList;
}

void Sensor::calculateStatistics()
{
    max = *std::max_element(dataList.begin(), dataList.end());
    min = *std::min_element(dataList.begin(), dataList.end());
    average = (std::accumulate(dataList.begin(), dataList.end(), 0.0) / dataList.size());
    std::this_thread::sleep_for(std::chrono::seconds(5));
}

float Sensor::getLatestData()
{
    std::lock_guard<std::mutex> lock(sensorMutex);
    return dataList.back();
}

float Sensor::getAverageData()
{
    return average;
}

float Sensor::getMinimumData()
{
    return min;
}

float Sensor::getMaxData()
{
    return max;
}

float Sensor::generateRandomSensorData(float minValue, float maxValue)
{
    std::uniform_real_distribution<> dist(minValue, maxValue);
    return dist(mt);
}

void Sensor::runSensor() {}
