#ifndef TEMPSENSOR_H
#define TEMPSENSOR_H

#include "Sensor.h"

class TempSensor : public Sensor
{
public:
    TempSensor();
    ~TempSensor();
    std::string getSensorType() const override;

private:
    void runSensor() override;
};

#endif
