#ifndef LED_STRIP_DRIVER_H
#define LED_STRIP_DRIVER_H

#include <Arduino.h>
#include <FastLED.h>

class LEDStripDriver {
public:
    LEDStripDriver();

    void init();
    void on();
    void off();
    void toggle();
    void fill();
    bool getPowerState();
    void update();
private:
    CRGB* _leds;
    bool _isOn;
    unsigned long _updateInterval;
};

#endif
