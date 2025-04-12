//
// Created by Ferfoui on 11/04/2025.
//

#include "Screen.hpp"

Screen::Screen(const uint8_t width, const uint8_t height, const int sda_pin, const int sck_pin, const int8_t reset_pin) {
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

void Screen::writeText(const char* text, const short x, const short y, const uint8_t size) {
    mDisplay.setTextSize(size);
    mDisplay.setTextColor(SSD1306_WHITE);
    mDisplay.setCursor(x, y);
    mDisplay.print(text);
    mDisplay.display();
}

void Screen::drawBitmap(const uint8_t* bitmap, const short x, const short y, const short width, const short height) {
    mDisplay.drawBitmap(x, y, bitmap, width, height, SSD1306_WHITE);
    mDisplay.display();
}

void Screen::scrollRight() {
    mDisplay.startscrollright(0x00, 0x0F);
}
