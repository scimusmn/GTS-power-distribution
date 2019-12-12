#include "config.h"
#include "HardwareSerial.h"
#include "events.h"
#include "control.h"
#include "source.h"
#include "Adafruit_NeoPixel.h"

int totalPower = 0;
int lastTotalPower = 0;

Source Source1(s1_up_pin, s1_down_pin , s1_react_time, s1_neo_pin, num_pixels_source, s1_max_pwr);
Source Source2(s2_up_pin, s2_down_pin , s2_react_time, s2_neo_pin, num_pixels_source, s2_max_pwr);
Source Source3(s3_up_pin, s3_down_pin , s3_react_time, s3_neo_pin, num_pixels_source, s3_max_pwr);
Source Source4(s4_up_pin, s4_down_pin , s4_react_time, s4_neo_pin, num_pixels_source, s4_max_pwr);
Source Source5(s5_up_pin, s5_down_pin , s5_react_time, s5_neo_pin, num_pixels_source, s5_max_pwr);
BarGraph Production(prod_neo_pin, 70, 10,0,0);
BarGraph Demand(demand_neo_pin, 70, 5,5,5);
Schedule schedule1(&Source1, &Source2, &Source3, &Source4, &Source5); // solar, wind, hydro, gas, coal

void setup() {
  Serial.begin(9600);
  Serial.println("GTS Power");
  Production.setLevel(0);
  Demand.setLevel(50);
}

void loop() {

  schedule1.runClock();

  totalPower =  Source1.getPowerProduced() + Source2.getPowerProduced() + Source3.getPowerProduced() + Source4.getPowerProduced() + Source5.getPowerProduced();

  if (totalPower != lastTotalPower){
    int P = totalPower/(s1_max_pwr + s2_max_pwr + s3_max_pwr + s4_max_pwr + s5_max_pwr);
    Production.setLevel(P);
    lastTotalPower =  totalPower;
  }

}
