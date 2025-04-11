//
// Created by Ferfoui on 11/04/2025.
//

#include "RgbLed.hpp"

RgbLed::RgbLed(int pin) : mPin(pin) {
    pinMode(pin, OUTPUT);
}

void RgbLed::setColor(uint8_t red_value, uint8_t green_value, uint8_t blue_value) {
    neopixelWrite(mPin, red_value, green_value, blue_value);
}

void RgbLed::setColor(uint32_t color) {
    // Extract the red, green, and blue values from the 32-bit color value
    uint8_t red_value = (color >> 16) & 0xFF;
    uint8_t green_value = (color >> 8) & 0xFF;
    uint8_t blue_value = color & 0xFF;
    setColor(red_value, green_value, blue_value);
}

void RgbLed::turnOff() {
    setColor(0, 0, 0);
}
