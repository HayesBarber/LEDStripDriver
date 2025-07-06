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

    void init() {
        FastLED.addLeds<NEOPIXEL, DATA_PIN>(_leds, NUM_PIXELS);
        FastLED.setBrightness(BRIGHTNESS);

        for (int i = 0; i < NUM_PIXELS; i++) {
            _leds[i] = CRGB::Black;
        }

        FastLED.show();
    }

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
