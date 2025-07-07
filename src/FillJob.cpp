#include "FillJob.h"

FillJob::FillJob()
    : _colors(nullptr), _numColors(0), _pixelsPerColor(0),
      _currentPixel(0), _currentColorIdx(0),
      _numPixels(0), _inProgress(false), _lastUpdate(0) {}

FillJob::~FillJob() {
    delete[] _colors;
}

void FillJob::begin(String colorString, uint16_t numPixels) {
    delete[] _colors;

    _numPixels = numPixels;
    _currentPixel = 0;
    _currentColorIdx = 0;
    _lastUpdate = millis();
    _inProgress = true;

    _numColors = 1;
    for (char c : colorString) {
        if (c == ',') _numColors++;
    }

    _colors = new CRGB[_numColors];
    _pixelsPerColor = _numPixels / _numColors;

    String current = "";
    uint8_t index = 0;
    for (unsigned int i = 0; i < colorString.length(); i++) {
        char c = colorString.charAt(i);
        if (c == ',') {
            _colors[index++] = _parseColor(current);
            current = "";
        } else {
            current += c;
        }
    }
    if (!current.isEmpty()) {
        _colors[index] = _parseColor(current);
    }
}

void FillJob::applyStep(CRGB* leds, uint32_t updateInterval) {
    if (!_inProgress) return;
    if (millis() - _lastUpdate < updateInterval) return;

    leds[_currentPixel] = _colors[_currentColorIdx];
    FastLED.show();

    _currentPixel++;
    if (_currentPixel >= (_currentColorIdx + 1) * _pixelsPerColor && _currentColorIdx < _numColors - 1)
    {
        _currentColorIdx++;
    }

    if (_currentPixel >= _numPixels) {
        _inProgress = false;
    }

    _lastUpdate = millis();
}

CRGB FillJob::_parseColor(const String& hex) {
    long val = strtol(hex.c_str(), NULL, 16);
    return CRGB((val >> 16) & 0xFF, (val >> 8) & 0xFF, val & 0xFF);
}
