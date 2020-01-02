#include "config.h"
#include "HardwareSerial.h"
#include "events.h"
#include "control.h"
#include "source.h"
#include "Adafruit_NeoPixel.h"
#include "arduino-base/Libraries/SerialManager.h"

int totalPower = 0;
int lastTotalPower = 0;
int pastTime = 0;

SerialManager serialManager;

Source Source1(s1_up_pin, s1_down_pin , s1_react_time, s1_neo_pin, num_pixels_source, s1_max_pwr);
Source Source2(s2_up_pin, s2_down_pin , s2_react_time, s2_neo_pin, num_pixels_source, s2_max_pwr);
Source Source3(s3_up_pin, s3_down_pin , s3_react_time, s3_neo_pin, num_pixels_source, s3_max_pwr);
Source Source4(s4_up_pin, s4_down_pin , s4_react_time, s4_neo_pin, num_pixels_source, s4_max_pwr);
Source Source5(s5_up_pin, s5_down_pin , s5_react_time, s5_neo_pin, num_pixels_source, s5_max_pwr);
BarGraph Production(prod_neo_pin, 70, 10,0,0);
BarGraph Demand(demand_neo_pin, 70, 5,5,5);
Schedule schedule1(&Source1, &Source2, &Source3, &Source4, &Source5); // solar, wind, hydro, gas, coal

void setup() {
  long baudRate = 115200;
  // Enables/disables debug messaging from ArduinoJson
  boolean arduinoJsonDebug = false;

  // Ensure Serial Port is open and ready to communicate
  serialManager.setup(baudRate, [](char* message, char* value) {
    onParse(message, value);
  }, arduinoJsonDebug);


  Production.setLevel(0);
  Demand.setLevel(50);
}

void loop() {

  schedule1.runClock();
  int theTime = schedule1.getTime();

  if ((pastTime != theTime)  && (theTime % 5 == 0)){
    serialManager.sendJsonMessage("clock", theTime );
    pastTime = theTime;
  }

  totalPower =  Source1.getPowerProduced() + Source2.getPowerProduced() + Source3.getPowerProduced() + Source4.getPowerProduced() + Source5.getPowerProduced();

  if (totalPower != lastTotalPower){
    int P = totalPower/(s1_max_pwr + s2_max_pwr + s3_max_pwr + s4_max_pwr + s5_max_pwr);
    Production.setLevel(P);
    lastTotalPower =  totalPower;
    //serialManager.sendJsonMessage("totalPower", totalPower);
  }

  serialManager.idle();
}

void onParse(char* message, int value) {

//  if (strcmp(message, "led") == 0) {
//    // Turn-on led
//    digitalWrite(ledPin, value);
//  }
//  else if (strcmp(message, "pwm-output") == 0 && value >= 0) {
//    // Set pwm value to pwm pin
//    analogWrite(pwmOutputPin, value);
//    serialManager.sendJsonMessage("pwm-set", value);
//  }
//  else if (strcmp(message, "pot-rotation") == 0) {
//    serialManager.sendJsonMessage(message, analogInput1.readValue());
//  }
  if (strcmp(message, "wake-arduino") == 0 && value == 1) {
    serialManager.sendJsonMessage("arduino-ready", 1);
  } else {
    serialManager.sendJsonMessage("unknown-command", 1);
    serialManager.sendJsonMessage(message, value);
  }
}
