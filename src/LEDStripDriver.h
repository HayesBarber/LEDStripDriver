#ifndef LED_STRIP_DRIVER_H
#define LED_STRIP_DRIVER_H

#include <Arduino.h>
#include <FastLED.h>
#include "FillJob.h"

class LEDStripDriver {
public:
    /**
     * @brief Constructs a new LEDStripDriver instance.
     * 
     * @param numPixels Number of pixels in the LED strip.
     * @param brightness Brightness level (0–255).
     * @param updateInterval Interval between color updates in milliseconds.
     */
    LEDStripDriver(uint16_t numPixels, uint8_t brightness, uint32_t updateInterval = 20);

    /**
     * @brief Initializes the LED strip using the specified data pin.
     * 
     * @tparam DATA_PIN GPIO pin connected to the LED strip.
     */
    template<uint8_t DATA_PIN>
    void init() {
        FastLED.addLeds<NEOPIXEL, DATA_PIN>(_leds, _numPixels);
        FastLED.setBrightness(_brightness);

        for (int i = 0; i < _numPixels; i++) {
            _leds[i] = CRGB::Black;
        }

        FastLED.show();
    }

    /**
     * @brief Turns the LED strip on, restoring the last color pattern.
     */
    void on();

    /**
     * @brief Turns the LED strip off.
     */
    void off();

    /**
     * @brief Toggles the LED strip power state.
     */
    void toggle();

    /**
     * @brief Begins a fill operation with the specified colors.
     * 
     * @param colors Comma-separated hex color codes (e.g., "FF0000,00FF00,0000FF").
     */
    void fill(String colors);

    /**
     * @brief Returns the current power state of the LED strip.
     * 
     * @return true if the strip is on, false otherwise.
     */
    bool getPowerState();

    /**
     * @brief Performs a step in the progressive fill animation.
     * Should be called periodically, e.g., from loop().
     */
    void loop();

    /**
     * @brief Returns the last set color pattern.
     * 
     * @return Comma-separated hex color string if on, otherwise "000000".
     */
    String getCurrentColors() const;

private:
    CRGB* _leds;
    bool _isOn;
    uint8_t _brightness;
    String _lastColors;
    FillJob _fillJob;
};

#endif
