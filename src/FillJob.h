#ifndef FILL_JOB_H
#define FILL_JOB_H

#include <Arduino.h>
#include <FastLED.h>

class FillJob {
public:
    FillJob();
    ~FillJob();

    void begin(String colorString);
    void applyStep(CRGB* leds, uint32_t updateInterval);
    void setNumPixels(uint16_t numPixels);

private:
    CRGB* _colors;
    uint8_t _numColors;

    uint16_t _pixelsPerColor;
    uint16_t _currentPixel;
    uint8_t _currentColorIdx;

    uint16_t _numPixels;
    bool _inProgress;
    unsigned long _lastUpdate;

    CRGB _parseColor(const String& hex);
};

#endif
