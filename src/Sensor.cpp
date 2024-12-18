#include "Sensor.h"

Sensor::Sensor() : mt(std::random_device{}()), Running(true)
{
}

float Sensor::calculateAverage()
{
    return (std::accumulate(dataList.begin(), dataList.end(), 0.0) / dataList.size());
}

float Sensor::calculateMinimum(const std::vector<float> &dataList)
{
}

float Sensor::calculateMaximum(const std::vector<float> &dataList)
{
}

float Sensor::getLatestData()
{
}

float Sensor::getAverageData()
{
    return calculateAverage();
}

float Sensor::getMinimumData()
{
}

float Sensor::getMaxData()
{
}