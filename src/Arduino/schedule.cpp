/*
  schedule.h - schedule library for power distribution Gateway to Science
  Joe Meyer created 10/18/2019 at the science museum of mn
*/

#include "Arduino.h"
#include "schedule.h"
#include "config.h"
#include "source.h"

Schedule::Schedule(Source* solar, Source* wind, Source* hydro, Source* gas, Source* coal)
{
  this->solar = solar;
  this->wind = wind;
  this->hydro = hydro;
  this->gas = gas;
  this->coal = coal;


  solar->setPowerAvailable(0);
  wind->setPowerAvailable(0);
  hydro->setPowerAvailable(80);
  gas->setPowerAvailable(100);
  coal->setPowerAvailable(100);

  currentMillis = 0;
  lastMinMillis = 0;
  minute = 0;  // start 1 min before midnight
  hour = 24;
  solar_percent = 0;
  windSpeed = 150;
}

//PUBLIC
void Schedule::runClock(void)
{
  timeUpdate();
  solar->update();
  wind->update();
  hydro->update();
  gas->update();
  coal->update();
}

//PRIVATE
void Schedule::timeUpdate(void){
  currentMillis = millis();
  if ((currentMillis - lastMinMillis) > min_in_millis){  //ONE MINUTE HAS PASSED
    minute++;
    minuteTasks();
    if (minute >= 60){      //ONE HOUR HAS PASSED
      hour++;
      minute = 0;
      if (hour > 24) hour =1;
      hourTasks();
    }
    lastMinMillis = currentMillis;
  }
}

int Schedule::getTime(){
  int theTime;
  theTime = hour*100 + minute;
  return theTime;
}

void Schedule::hourTasks(void){

  //WIND
  int windChange = random(-10,10);
  windSpeed = windSpeed + windChange;
  windSpeed = constrain(windSpeed,0,200);
  if (windSpeed > 99){
    wind->setPowerAvailable((windSpeed-100)) ;
  }

  //CLOUD COVER
  cloudCover = random(-50,50);
  cloudCover = constrain(cloudCover,0,50);
//  Serial.print(cloudCover*2);
//  Serial.println("%");
  cloudCover = (100/4); // - cloudCover)/4;

}

void Schedule::minuteTasks(void){

  //SOLAR
  if ((hour > 6) && (hour < 11)) solar_percent = ((hour-7) * cloudCover + (minute*cloudCover)/59);
  if ((hour > 16) && (hour < 21)) solar_percent = 100 - ((hour-17) * cloudCover + (minute*cloudCover)/59);
  if ((hour >=11) && (hour<=16)) solar_percent = (cloudCover*4);
  solar->setPowerAvailable(solar_percent);
}
