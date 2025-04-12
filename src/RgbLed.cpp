//
// Created by Ferfoui on 11/04/2025.
//

#include "RgbLed.hpp"

RgbLed::RgbLed(const uint8_t pin) : mPin(pin) {
    pinMode(pin, OUTPUT);
}

void RgbLed::setColor(const uint8_t red_value, const uint8_t green_value, const uint8_t blue_value) const {
    neopixelWrite(mPin, red_value, green_value, blue_value);
}

void RgbLed::setColor(const uint32_t color) const {
    // Extract the red, green, and blue values from the 32-bit color value
    const uint8_t red_value = (color >> 16) & 0xFF;
    const uint8_t green_value = (color >> 8) & 0xFF;
    const uint8_t blue_value = color & 0xFF;
    setColor(red_value, green_value, blue_value);
}

void RgbLed::turnOff() const {
    setColor(0, 0, 0);
}
