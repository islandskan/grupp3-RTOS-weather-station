#include "WindSensor.h"

WindSensor::WindSensor(/* args */)
{
}

WindSensor::~WindSensor()
{
}

void WindSensor::runSensor()
{
    while (Running)
    {
        {
            std::lock_guard<std::mutex> lock(sensorMutex);
            dataList.push_back(generateRandomSensorData(0.0, 25.0));
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}
