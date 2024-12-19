#ifndef SENSOR_H
#define SENSOR_H

#include <vector>
#include <random>
#include <thread>
#include <mutex>
#include <atomic>
#include <numeric> // <-- For accumulate
#include <algorithm>

class Sensor
{
public:
    // Constructor
    Sensor();
    // Destructor
    virtual ~Sensor();

    // Getters
    std::vector<float> getData();

    // Methods
    float getLatestData();
    float getAverageData();
    float getMinimumData();
    float getMaxData();
    virtual std::string getSensorType() const = 0;


protected:
    // Members
    float max;
    float min;
    float average;

    std::vector<float> dataList;
    std::mt19937 mt;

    std::thread sensorThread;
    std::thread calculationThread;
    std::atomic<bool> Running;
    std::mutex sensorMutex;
    float generateRandomSensorData(float minValue, float maxValue);

    virtual void runSensor() = 0;

    // Methods
    float calculateAverage();
    float calculateMinimum();
    float calculateMaximum();
    void calculateStatistics();
};

#endif
