#ifndef LED_STRIP_DRIVER_H
#define LED_STRIP_DRIVER_H

#include <Arduino.h>
#include <FastLED.h>
#include "FillJob.h"

class LEDStripDriver {
public:
    /**
     * @brief Constructs a new LEDStripDriver instance.
     */
    LEDStripDriver();

    /**
     * @brief Initializes the LED strip with specified parameters and data pin.
     * 
     * @tparam DATA_PIN GPIO pin connected to the LED strip.
     * @param numPixels Number of pixels in the strip. Minimum enforced is 1.
     * @param brightness Brightness level (0–255).
     * @param updateInterval Delay between progressive fill steps in milliseconds.
     */
    template<uint8_t DATA_PIN>
    void init(uint16_t numPixels, uint8_t brightness, uint32_t updateInterval = 20) {
        if (numPixels <= 0) numPixels = 1;
        if (brightness > 255) brightness = 255;
        if (brightness < 0) brightness = 0;

        _leds = new CRGB[numPixels];
        _fillJob.setNumPixels(numPixels);
        _fillJob.setUpdateInterval(updateInterval);

        FastLED.addLeds<NEOPIXEL, DATA_PIN>(_leds, numPixels);
        FastLED.setBrightness(brightness);

        for (int i = 0; i < numPixels; i++) {
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
    String _lastColors;
    FillJob _fillJob;

    void persistLastColors();
    String getLastColorsFromStorage();
};

#endif
