#include "Sensor.h"

Sensor::Sensor() : mt(std::random_device{}()), Running(true)
{
    sensorThread = std::thread(&Sensor::runSensor, this);
    calculationThread = std::thread(&Sensor::calculateStatistics, this);
}

Sensor::~Sensor()
{
    Running = false;
    sensorThread.join();
    calculationThread.join();
}

float Sensor::calculateAverage()
{
    std::lock_guard<std::mutex> lock(sensorMutex);
    return dataList.empty() ? 0 :(std::accumulate(dataList.begin(), dataList.end(), 0.0) / dataList.size());
}

std::vector<float> Sensor::getData()
{
    std::lock_guard<std::mutex> lock(sensorMutex);
    return dataList;
}

float Sensor::calculateMinimum()
{
    std::lock_guard<std::mutex> lock(sensorMutex);
    return dataList.empty() ? 0 : *std::min_element(dataList.begin(), dataList.end());
}

float Sensor::calculateMaximum()
{
    std::lock_guard<std::mutex> lock(sensorMutex);
    return dataList.empty() ? 0: *std::max_element(dataList.begin(), dataList.end());
}

void Sensor::calculateStatistics()
{
    while(Running)
    {
        {
                std::lock_guard<std::mutex> lock(sensorMutex);
                max = calculateMaximum();
                min = calculateMinimum();
                average = calculateAverage();
        }
    std::this_thread::sleep_for(std::chrono::seconds(5));
    }

}

float Sensor::getLatestData()
{
    std::lock_guard<std::mutex> lock(sensorMutex);
    return dataList.empty() ? 0 : dataList.back();
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

void Sensor::runSensor()
{
}
