#include "TempSensor.h"

TempSensor::TempSensor() : Sensor() {}
TempSensor::~TempSensor() {}

void TempSensor::runSensor()
{
    while (Running)
    {
        {
            std::lock_guard<std::mutex> lock(sensorMutex);
            dataList.push_back(generateRandomSensorData(-30.0, 30.0));
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}

    std::string TempSensor::getSensorType() const
    {
        return "TempSensor";
    }
