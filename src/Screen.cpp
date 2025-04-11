//
// Created by Ferfoui on 11/04/2025.
//

#include "Screen.hpp"

Screen::Screen(uint8_t width, uint8_t height, int sda_pin, int sck_pin, int8_t reset_pin) {
    mI2c.begin(sda_pin, sck_pin);
    mDisplay = Adafruit_SSD1306(width, height, &mI2c, reset_pin);
}

bool Screen::begin() {
    // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
    if (!mDisplay.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
        return false; // Don't proceed
    }
    mDisplay.display();
    return true;
}

void Screen::clear() {
    mDisplay.clearDisplay();
}

void Screen::writeText(const char* text, int x, int y, int size) {
    mDisplay.setTextSize(size);
    mDisplay.setTextColor(SSD1306_WHITE);
    mDisplay.setCursor(x, y);
    mDisplay.print(text);
    mDisplay.display();
}

void Screen::drawBitmap(const uint8_t* bitmap, int x, int y, int width, int height) {
    mDisplay.drawBitmap(x, y, bitmap, width, height, SSD1306_WHITE);
    mDisplay.display();
}
