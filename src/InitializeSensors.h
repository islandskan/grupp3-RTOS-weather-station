#ifndef INITIALIZESENSORS_H
#define INITIALIZESENSORS_H
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
    std::cout << Temp1.getLatestData() << std::endl;
}

#endif