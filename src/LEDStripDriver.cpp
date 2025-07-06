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

void LEDStripDriver::on() {
    fill("FF0000");
}

void LEDStripDriver::off() {
    fill("000000");
}

void LEDStripDriver::fill(String colors) {
    bool turningOn = (colors != "000000");
    _isOn = turningOn;
    _fillJob.begin(colors, _numPixels);
}

void LEDStripDriver::update() {
    _fillJob.applyStep(_leds);
}

bool LEDStripDriver::getPowerState() {
    return _isOn;
}
