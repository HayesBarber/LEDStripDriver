#include "LEDStripDriver.h"
#include <MicroStorage.h>

LEDStripDriver::LEDStripDriver() : _isOn(false), _lastColors("") {}

void LEDStripDriver::toggle() { _isOn ? off() : on(); }

void LEDStripDriver::on() {
  if (_lastColors.isEmpty()) {
    fill("FF0000");
  } else {
    fill(_lastColors);
  }
}

void LEDStripDriver::off() { fill("000000"); }

void LEDStripDriver::fill(String colors) {
  if (colors.isEmpty())
    return;

  bool turningOn = (colors != "000000");
  _isOn = turningOn;

  if (turningOn) {
    _lastColors = colors;
    persistLastColors();
  }

  _fillJob.begin(colors);
}

void LEDStripDriver::loop() { _fillJob.applyStep(_leds); }

bool LEDStripDriver::getPowerState() const { return _isOn; }

String LEDStripDriver::getCurrentColors() const {
  return getLastColorsFromStorage();
}

void LEDStripDriver::persistLastColors() {
  MicroStorage::set("LED", StringEntry("lastColors", _lastColors));
}

String LEDStripDriver::getLastColorsFromStorage() const {
  auto [value] = MicroStorage::get("LED", StringEntry("lastColors", ""));

  return value;
}
