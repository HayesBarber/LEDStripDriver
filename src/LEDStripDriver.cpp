#include "LEDStripDriver.h"

LEDStripDriver::LEDStripDriver(uint16_t numPixels, uint8_t brightness, uint32_t updateInterval)
    : _numPixels(numPixels),
      _brightness(brightness),
      _updateInterval(updateInterval),
      _isOn(false)
{
    _leds = new CRGB[_numPixels];
}

void LEDStripDriver::toggle() {
    _isOn ? off() : on();
}

bool LEDStripDriver::getPowerState() {
    return _isOn;
}

CRGB LEDStripDriver::_parseColor(String hexColor) {
    long number = strtol(hexColor.c_str(), NULL, 16);
    return CRGB((number >> 16) & 0xFF, (number >> 8) & 0xFF, number & 0xFF);
}
