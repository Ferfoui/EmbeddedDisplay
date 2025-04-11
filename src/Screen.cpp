//
// Created by Ferfoui on 11/04/2025.
//

#include "Screen.hpp"

Screen::Screen(uint8_t width, uint8_t height, int sda_pin, int sck_pin, int8_t resetPin) {
    mI2c.begin(sda_pin, sck_pin);
    mDisplay = Adafruit_SSD1306(width, height, &mI2c, resetPin);
}

bool Screen::begin() {
    // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
    if (!mDisplay.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
        return false; // Don't proceed
    }
    mDisplay.display();
    return true;
}
