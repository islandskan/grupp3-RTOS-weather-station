#ifndef TEMPSENSOR_H
#define TEMPSENSOR_H

#include "Sensor.h"
#include <random>

class TempSensor : Sensor
{
public:
    TempSensor();

private:
};

// how the sub classes are going to run and create their own mock data
// double Sensor::generateRandom(double minValue, double maxValue)

// {
//     std::uniform_real_distribution<> dist(minValue, maxValue);
//     return dist(mt);
// }

// void TempSensor::runSensor()
// {
//     while (Running)
//     {
//         std::lock_guard<std::mutex> lock(sensorMutex);
//         temperature = generateRandom(-30.0, 30.0);
//     }
//     std::this_thread::sleep_for(std::chrono::milliseconds(400));
// }

#endif
