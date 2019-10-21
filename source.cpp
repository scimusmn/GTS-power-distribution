/*
  Source.h - Source library for power distribution Gateway to Science
  Joe Meyer created 9/9/2019 at the science museum of mn
*/

#include "Arduino.h"
#include "source.h"
#include "Adafruit_NeoPixel.h"

Source::Source(int up_pin, int down_pin, int react_spd, int neo_pin, int num_pixels, int cap_kw)
{
  _cap_kw = cap_kw;
  _up_pin = up_pin;
  _down_pin = down_pin;
  _react_spd = react_spd;
  _num_pixels = num_pixels;
  pinMode(neo_pin, OUTPUT);
  _pixels = Adafruit_NeoPixel (_num_pixels, neo_pin, NEO_RGB + NEO_KHZ800);
  pinMode( _up_pin, INPUT);
  pinMode( _down_pin, INPUT);
  _pixels.begin();
  _react_spd = react_spd;
  _target_percent = 0;
  _current_percent = 0;
  _up_toggle = false;
  _down_toggle = false;
}

// Public Methods //////////////////////////////////////////////////////////////
void Source::setPowerAvailable(int percentage)
{
  _available_percent = percentage;
}

int Source::getPowerProduced()
{
  int totalp = (_cap_kw*_current_percent);
  return (totalp);
}

void Source::update(void)
{
  currentMillis = millis();

  if (!digitalRead(_up_pin)) {
    if (_up_toggle) {
      last_btn_millis = currentMillis;
      _target_percent = _target_percent + 5;
      _up_toggle = false;
    }
    if ((currentMillis - last_btn_millis) > 200) {
      _up_toggle = true;
      last_btn_millis = currentMillis;
    }
  } else {
    _up_toggle = true;
  }

  if (!digitalRead(_down_pin)) {
    if (_down_toggle) {
      last_btn_millis = currentMillis;
      _target_percent = _target_percent - 5;
      _down_toggle = false;
    }
    if ((currentMillis - last_btn_millis) > 200) {
      _down_toggle = true;
      last_btn_millis = currentMillis;
    }

  } else {
    _down_toggle = true;
  }

  _target_percent = constrain(_target_percent, 0, 100);

  if (_current_percent < _target_percent) {
    if ((currentMillis - last_change) > _react_spd) {
      _current_percent = _current_percent + 5;

      last_change = currentMillis;
    }
  }
  _current_percent = constrain(_current_percent, 0, _available_percent);
  if (_current_percent > _target_percent) {
    _current_percent = _target_percent;
  }

  lightPixels();
}

// Private Methods /////////////////////////////////////////////////////////////

void Source::lightPixels(void)
{
  int current_pixels = map(_current_percent, 0, 100, 0, _num_pixels);
  int available_pixels = map(_available_percent, 0, 100, 0, _num_pixels);

  _pixels.clear(); // Set all pixel colors to 'off'

  for (int i = 1; i <= _num_pixels; i++) { // For each pixel...
    if (i <= (current_pixels)) _pixels.setPixelColor(i-1, _pixels.Color(5, 0, 0)); //green
    if (i > (current_pixels) && i <= (available_pixels)) _pixels.setPixelColor(i-1, _pixels.Color(0, 0, 3)); //blue
  }

  int _target_pixel = map(_target_percent, 0, 100, 0, _num_pixels);
  if (_target_pixel > (available_pixels)) {
    _pixels.setPixelColor(_target_pixel-1, _pixels.Color(0, 5, 0)); //red
  } else {
    _pixels.setPixelColor(_target_pixel-1, _pixels.Color(50, 0, 0)); //bright green
  }

  _pixels.show();   // Send the updated pixel colors to the hardware
}
