#ifndef LED_STRIP_DRIVER_H
#define LED_STRIP_DRIVER_H

#include <Arduino.h>
#include <FastLED.h>

class LEDStripDriver {
public:
    LEDStripDriver(uint16_t numPixels, uint8_t brightness, uint32_t updateInterval);

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

    uint8_t _dataPin;
    uint16_t _numPixels;
    uint8_t _brightness;
    uint32_t _updateInterval;

    CRGB _parseColor(String hexColor);
};

#endif
