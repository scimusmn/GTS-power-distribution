/*
  Schedule.h - Schedule library for power distribution Gateway to Science
  Joe Meyer created 10/18/2019 at the science museum of mn
*/
#include "Arduino.h"
#include "source.h"
#include "arduino-base/Libraries/SerialManager.h"

// ensure this library description is only included once
#ifndef Schedule_h
#define Schedule_h


class Schedule
{
  public:
    Schedule(Source*, Source*, Source*, Source*, Source*, SerialManager*); // solar, wind, hydro, gas, coal
    void runClock();
    int getTime();
    Source* solar;
    Source* wind;
    Source* hydro;
    Source* gas;
    Source* coal;
    SerialManager* serialManager;



  private:
    unsigned long currentMillis;
    unsigned long lastMinMillis;
    int minute;
    int hour;
    void timeUpdate();
    void minuteTasks();
    void hourTasks();
    int solar_percent;
    int windSpeed;
    int cloudCover;
};




#endif
