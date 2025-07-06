#ifndef LED_STRIP_DRIVER_H
#define LED_STRIP_DRIVER_H

#include <Arduino.h>
#include <FastLED.h>

template<uint16_t DATA_PIN, uint16_t NUM_PIXELS, uint16_t BRIGHTNESS, uint32_t UPDATE_INTERVAL>
class LEDStripDriver {
public:
    LEDStripDriver() : _isOn(false) {
        _leds = new CRGB[NUM_PIXELS];
    }

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
};

#endif
