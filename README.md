# LEDStripDriver

A lightweight, Arduino-compatible C++ library for controlling addressable LED strips using FastLED. Designed with simplicity in mind, it enables progressive color animations with minimal code.

## Features

- Progressive fill animations with customizable update intervals
- Support for comma-separated hex color strings (e.g. `"FF0000,00FF00,0000FF"`)
- On/off/toggle controls
- Queryable power state and last-used colors

## Usage

```cpp
#include <LEDStripDriver.h>

const uint16_t NUM_PIXELS = 60;
const uint8_t BRIGHTNESS = 64;

LEDStripDriver strip(NUM_PIXELS, BRIGHTNESS);

void setup() {
    strip.init<5>(); // Set your actual data pin
    strip.fill("FF0000,00FF00,0000FF");
}

void loop() {
    strip.loop();
}
```
