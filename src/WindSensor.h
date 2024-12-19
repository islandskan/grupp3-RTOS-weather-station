#ifndef WINDSENSOR_H
#define WINDSENSOR_H
#include "Sensor.h"

class WindSensor : public Sensor
{
public:
    WindSensor();
    ~WindSensor();
    std::string getSensorType() const override;


private:
    void runSensor() override;
};

#endif
