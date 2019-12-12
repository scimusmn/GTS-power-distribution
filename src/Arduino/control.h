/*
  control.h - Control library for power distribution Gateway to Science
  Joe Meyer created 10/17/2019 at the science museum of mn
*/
#include "Arduino.h"
#include "Adafruit_NeoPixel.h"

// ensure this library description is only included once
#ifndef Control_h
#define Control_h

// library interface description
class BarGraph
{
    // user-accessible "public" interface
  public:
    BarGraph(int, int, int, int, int); //neo pin, num pixel
    void setLevel(int); //0 to 100 indicating percent

    // library-accessible "private" interface
  private:
    Adafruit_NeoPixel pixels;
    int num_pixels;
    int level;
    int red;
    int blue;
    int green;
};

#endif
