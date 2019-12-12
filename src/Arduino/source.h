/*
  Source.h - Source library for power distribution Gateway to Science
  Joe Meyer created 9/9/2019 at the science museum of mn
*/
#include "Arduino.h"
#include "Adafruit_NeoPixel.h"

// ensure this library description is only included once
#ifndef Source_h
#define Source_h

// library interface description
class Source
{
    // user-accessible "public" interface
  public:
    Source(int, int, int, int, int, int); //up pin, down pin, neopixel pin, num pixel, react speed, max production (kw?)
    void setPowerAvailable(int); //0 to 100 indicating percent
    int getPowerProduced(); //returns percent * capacity
    void update();

    // library-accessible "private" interface
  private:
    Adafruit_NeoPixel _pixels;
    void lightPixels();
    int _cap_kw;
    int _neopixel_pin;
    int _react_spd;
    int _target_percent;
    int _current_percent;
    int _available_percent;
    int _up_pin;
    int _down_pin;
    int _num_pixels;
    unsigned long currentMillis;
    unsigned long last_change;
    unsigned long last_btn_millis;
    bool _up_toggle;
    bool _down_toggle;


};

#endif
