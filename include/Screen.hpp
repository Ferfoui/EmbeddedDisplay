//
// Created by Ferfoui on 11/04/2025.
//

#ifndef SCREEN_HPP
#define SCREEN_HPP

#define SCREEN_ADDRESS 0x3C //< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>


class Screen {
public:
    explicit Screen(uint8_t width, uint8_t height, int sda_pin, int sck_pin, int8_t resetPin = -1);
    bool begin();

private:
    Adafruit_SSD1306 mDisplay;
    TwoWire mI2c = TwoWire(0);

};



#endif //SCREEN_HPP
