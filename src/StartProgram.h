#ifndef STARTPROGRAM_H
#define STARTPROGRAM_H
#include <iostream>
#include "Sensor.h"
#include "TempSensor.h"
#include "HumiditySensor.h"
#include "WindSensor.h"

void startProgram()
{
    TempSensor Temp1;
    HumiditySensor HumiditySensor1;
    WindSensor WindSensor1;

    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    std::cout << "Printing average data of Temperature Sensor 1: " << Temp1.getAverageData() << std::endl;
    std::cout << "Printing maximum data of Temperature Sensor 1: " << Temp1.getMaxData() << std::endl;
    std::cout << "Printing minimum data of Temperature Sensor 1: " << Temp1.getMinimumData() << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(5500));
    std::cout << "Printing average data of Temperature Sensor 1: " << Temp1.getAverageData() << std::endl;
    std::cout << "Printing maximum data of Temperature Sensor 1: " << Temp1.getMaxData() << std::endl;
    std::cout << "Printing minimum data of Temperature Sensor 1: " << Temp1.getMinimumData() << std::endl;
}

#endif