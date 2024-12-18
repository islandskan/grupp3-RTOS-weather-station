#include "Sensor.h"

Sensor::Sensor() : mt(std::random_device{}()), Running(true)
{
}

float Sensor::calculateAverage()
{
    return (std::accumulate(dataList.begin(), dataList.end(), 0.0) / dataList.size());
}

float Sensor::calculateMinimum()
{
    return 0.0; // <-- To remove warnings
}

float Sensor::calculateMaximum()
{
    return 0.0; // <-- To remove warnings
}

float Sensor::getLatestData()
{
    return 0.0; // <-- To remove warnings
}

float Sensor::getAverageData()
{
    return calculateAverage();
}

float Sensor::getMinimumData()
{
    return calculateMinimum();
}

float Sensor::getMaxData()
{
    return calculateMaximum();
}