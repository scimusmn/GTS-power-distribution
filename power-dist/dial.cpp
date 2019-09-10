/*
  Dial.h - Dial library for power distribution Gateway to Science
  Joe Meyer created 9/9/2019 at the science museum of mn
*/

#include "Dial.h"

// include description files for other libraries used (if any)
#include "HardwareSerial.h"
#include <Adafruit_NeoPixel.h>

// Constructor /////////////////////////////////////////////////////////////////
// Function that handles the creation and setup of instances

Dial::Dial(int analog_pin, int neopixel_pin, int first_pixel, int last_pixel, int dial_min, int dial_max)
{
  pinMode(analog_pin, INPUT);
  pinMode(neopixel_pin, OUTPUT);
  Serial.begin(9600);
  _analog_pin = analog_pin;
  _first_pixel = first_pixel;
  _last_pixel = last_pixel;
  _dial_min = dial_min;
  _dial_max = dial_max;
  Adafruit_NeoPixel pixels(_last_pixel, neopixel_pin, NEO_GRB + NEO_KHZ800); //TODO edit which strip.
  pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
}

// Public Methods //////////////////////////////////////////////////////////////
void Dial::setPowerAvailable(int percentage)
{
  _power_available = percentage;

}



void Dial::idle(void)
{
  dialPercent = getDialPercentage();

  Serial.print("Set at: ");
  Serial.print(dialPercent);
  Serial.print("% / ");
  Serial.print(_power_available);
  Serial.println("%");

  int power_unused = 0;
  int power_shortage = 0;
  if (dialPercent > _power_available){
    powerProduced = _power_available;
    power_unused = dialPercent - _power_available;
  }
  if (dialPercent <= _power_available){
    powerProduced = dialPercent;
    power_shortage = _power_available - dialPercent;
  }

  int pp = map(powerProduced,0,100,_first_pixel,_last_pixel);
  int ps = pp + map(power_shortage,0,100,_first_pixel,_last_pixel);
  int pu = pp + map(power_unused,0,100,_first_pixel,_last_pixel);

  // The first NeoPixel in a strand is #0, second is 1, all the way up
  // to the count of pixels minus one.
  for(int i=_first_pixel; i<_last_pixel; i++) { // For each pixel...
    if (i <= pp) pixels.setPixelColor(i, pixels.Color(0, 0, 255));
    if (power_unused>0 && i<= pu) pixels.setPixelColor(i, pixels.Color(0, 155, 0));
    if (power_shortage>0 && i<= ps) pixels.setPixelColor(i, pixels.Color(155, 0, 0));
  }

  pixels.clear(); // Set all pixel colors to 'off'
  pixels.show();   // Send the updated pixel colors to the hardware.

}

// Private Methods /////////////////////////////////////////////////////////////

void Dial::getDialPercentage(void)
{
  int read = analogRead(_analog_pin);
  return map(read,_dial_min,_dial_max, 0, 100);
}
