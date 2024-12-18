#ifndef TEMPSENSOR_H
#define TEMPSENSOR_H

#include "Sensor.h"

class TempSensor : public Sensor
{
public:
    TempSensor();

private:
void runSensor() override;
};


#endif
