/*
  Control.h - Control library for power distribution Gateway to Science
  Joe Meyer created 10/17/2019 at the science museum of mn
*/

#include "Arduino.h"
#include "control.h"
#include "Adafruit_NeoPixel.h"

BarGraph::BarGraph(int neo_pin, int number_pixels, int G, int R, int B)
{
  num_pixels = number_pixels;
  pinMode(neo_pin, OUTPUT);
  pixels = Adafruit_NeoPixel (num_pixels, neo_pin, NEO_RGB + NEO_KHZ800);
  pixels.begin();
  percentage = 0;
  green = G;
  blue = B;
  red = R;
}

// Public Methods //////////////////////////////////////////////////////////////
void BarGraph::setPercent(int p){
  percentage = p;
  int P = map(percentage,0,100,0,num_pixels);
  pixels.clear();
  for (int i = 1; i <= num_pixels; i++) { // For each pixel...
    if (i <= P){
      pixels.setPixelColor(i-1, pixels.Color(green, red, blue)); //
    }
  }
 pixels.show();
}

void BarGraph::setColor(int G, int R, int B){
  green = G;
  blue = B;
  red = R;
}

int BarGraph::getPercent(){
  return percentage;
}
