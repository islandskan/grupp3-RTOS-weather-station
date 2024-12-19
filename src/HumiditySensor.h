#ifndef HUMIDITYSENSOR_H
#define HUMIDITYSENSOR_H
#include "Sensor.h"

class HumiditySensor : public Sensor
{
public:
    HumiditySensor();
    ~HumiditySensor();
    std::string getSensorType() const override;

private:
    void runSensor() override;
};

#endif
