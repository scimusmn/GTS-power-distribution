#include "dial.h"

Dial windDial;

void setup() {
  // put your setup code here, to run once:
  windDial.setup(A0,12,0,24,50,800);
  windDial.setPowerAvailable(70);
}

void loop() {
  // put your main code here, to run repeatedly:
  windDial.idle();
}
