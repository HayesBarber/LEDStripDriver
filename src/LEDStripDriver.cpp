#include "LEDStripDriver.h"
#include <MicroStorage.h>

LEDStripDriver::LEDStripDriver()
    : _isOn(false),
      _lastColors("") {}

void LEDStripDriver::toggle() {
    _isOn ? off() : on();
}

void LEDStripDriver::on() {
    if (_lastColors.isEmpty()) {
        fill("FF0000");
    } else {
        fill(_lastColors);
    }
}

void LEDStripDriver::off() {
    fill("000000");
}

void LEDStripDriver::fill(String colors) {
    if (colors.isEmpty()) return;

    bool turningOn = (colors != "000000");
    _isOn = turningOn;

    if (turningOn) {
        _lastColors = colors;
    }

    _fillJob.begin(colors);
}

void LEDStripDriver::loop() {
    _fillJob.applyStep(_leds);
}

bool LEDStripDriver::getPowerState() {
    return _isOn;
}

String LEDStripDriver::getCurrentColors() const {
    return _isOn ? _lastColors : "000000";
}

void LEDStripDriver::persistLastColors() {
    MicroStorage::set("LED",
        StringEntry("lastColors", _lastColors)
    );
}
