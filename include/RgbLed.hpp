//
// Created by Ferfoui on 11/04/2025.
//

#ifndef RGBLED_HPP
#define RGBLED_HPP

#include <Arduino.h>

class RgbLed {
public:
    explicit RgbLed(int pin);
    void setColor(uint8_t red_value, uint8_t green_value, uint8_t blue_value);
    void setColor(uint32_t color);
    void turnOff();

private:
    int mPin;
};



#endif //RGBLED_HPP
