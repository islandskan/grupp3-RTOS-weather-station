#ifndef SENSOR_H
#define SENSOR_H

#include <vector>
#include <random>
#include <thread>
#include <mutex>
#include <atomic>

class Sensor {
    public:
    // Constructor
    Sensor();
    // Destructor
    ~Sensor();

    // Getters
    std::vector<float> getData();

    // Methods
    float getLatestData();
    float getAverageData();
    float getMinimumData();
    float getMaxData();

    private:  // <-- Protected?
    // Members
    std::vector<float> dataList;
    std::mt19937 mt;

    std::thread sensorThread;
    std::atomic<bool> Running;
    std::mutex sensorMutex;

    virtual double generateRandomSensorData(double minValue, double maxValue);

    // Methods
    float calculateAverage(const std::vector<float>& dataList);
    float calculateMinimum(const std::vector<float>& dataList);
    float calculateMaximum(const std::vector<float>& dataList);
};

#endif
