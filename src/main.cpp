#include "Sensor.h"
#include "TempSensor.h"
#include "Startprogram.h"
#include <iostream>

int main()
{
    startProgram();

    // Pseudo code: what main is going to do
    // while (Running)
    // {
    //     std::thread.sleep 2 sekunder
    //     object.statistics.print
    //     std::thread.sleep 10 sekunder
    // }

    /* La till detta då jag tänker det är ett första test om klassen och dess autogenererade data fungerar */
    // TempSensor TempSensor1;
    // std::this_thread::sleep_for(std::chrono::seconds(5)); // 5 sekunder borde vara nog för andra tråden att generera lite.
    // TempSensor1.getLatestData();

    return 0;
}
