#include "HumiditySensor.h"

HumiditySensor::HumiditySensor() : Sensor() {}
HumiditySensor::~HumiditySensor() {}

void HumiditySensor::runSensor()
{
    while (Running)
    {
        {
            std::lock_guard<std::mutex> lock(sensorMutex);
            dataList.push_back(generateRandomSensorData(5.0, 100.0));
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}

std::string HumiditySensor::getSensorType() const
{
    return "HumiditySensor";
}
