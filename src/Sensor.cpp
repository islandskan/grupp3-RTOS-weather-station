#include "Sensor.h"

Sensor::Sensor() : mt(std::random_device{}()), Running(true)
{
    this->sensorThread = std::thread(runSensor, this);
    this->calculationThread = std::thread(calculateStatistics, this);
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

    while (Running)
    {
        std::unique_lock<std::mutex> lock(sensorMutex);
        if (!dataList.empty())
        {
            max = *std::max_element(dataList.begin(), dataList.end());
            min = *std::min_element(dataList.begin(), dataList.end());
            average = (std::accumulate(dataList.begin(), dataList.end(), 0.0) / dataList.size());
        }
        lock.unlock();
        std::this_thread::sleep_for(std::chrono::seconds(5));
    }
}

float Sensor::getLatestData()
{
    std::lock_guard<std::mutex> lock(sensorMutex);
    if (!dataList.empty())
    {
        return dataList.back();
    }
    return 0.0f; // or some other default value
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
