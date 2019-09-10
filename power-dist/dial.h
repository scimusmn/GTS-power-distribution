/*
  Dial.h - Dial library for power distribution Gateway to Science
  Joe Meyer created 9/9/2019 at the science museum of mn
*/

// ensure this library description is only included once
#ifndef Dial_h
#define Dial_h


// library interface description
class Dial
{
  // user-accessible "public" interface
  public:
    Dial(int, int, int, int, int, int); //analog pin, neopixel pin, first pixel, last pixel, dial_min, dial_max
    void setPowerAvailable(int); //0 to 100 indicating percent
    void idle();
    int dialPercent;
    int powerProduced;

  // library-accessible "private" interface
  private:
    int _dial_min;
    int _dial_max;
    int _first_pixel;
    int _last_pixel;
    int _power_available; //percentage of power available.
    getDialPercentage();
  //  int value;
  //  void doSomethingSecret(void);
};

#endif
