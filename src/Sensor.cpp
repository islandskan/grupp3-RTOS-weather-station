#include "Sensor.h"

Sensor::Sensor() : mt(std::random_device{}()), Running(true)
{}

float Sensor::calculateAverage(const std::vector<float>& dataList)
{}

float Sensor::calculateMinimum(const std::vector<float>& dataList)
{}

float Sensor::calculateMaximum(const std::vector<float>& dataList)
{}

float Sensor::getLatestData()
{}

float Sensor::getAverageData()
{}

float Sensor::getMinimumData()
{}

float Sensor::getMaxData()
{}
