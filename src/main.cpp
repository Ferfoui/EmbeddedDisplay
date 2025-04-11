#include <Arduino.h>

#include "RgbLed.hpp"

#define RGB_LED_PIN 38

RgbLed rgbLed(RGB_LED_PIN);

void setup() {
}

void loop() {
    // Set the RGB LED to blue
    rgbLed.setColor(0, 0, 32);
    delay(1000);

    // Set the RGB LED to purple
    rgbLed.setColor(16, 0, 16);
    delay(1000);

    rgbLed.turnOff();
    delay(1000);

}