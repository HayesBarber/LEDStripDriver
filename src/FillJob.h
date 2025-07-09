#ifndef FILL_JOB_H
#define FILL_JOB_H

#include <Arduino.h>
#include <FastLED.h>

/**
 * @brief Internal class used by LEDStripDriver to perform progressive fills.
 * 
 * This class is not intended for external use.
 * Its API may change without notice.
 */
class FillJob {
public:
    FillJob();
    ~FillJob();

    void begin(String colorString);
    void applyStep(CRGB* leds);
    void setNumPixels(uint16_t numPixels);
    void setUpdateInterval(uint32_t updateInterval);

private:
    CRGB* _colors;
    uint8_t _numColors;

    uint16_t _pixelsPerColor;
    uint16_t _currentPixel;
    uint8_t _currentColorIdx;

    uint32_t _updateInterval;
    uint16_t _numPixels;
    bool _inProgress;
    unsigned long _lastUpdate;

    CRGB _parseColor(const String& hex);
};

#endif
