//
// Created by Ferfoui on 11/04/2025.
//

#ifndef RGB_LED_HPP
#define RGB_LED_HPP

#include <Arduino.h>

class RgbLed {
public:
    explicit RgbLed(uint8_t pin);
    void setColor(uint8_t red_value, uint8_t green_value, uint8_t blue_value) const;
    void setColor(uint32_t color) const;
    void turnOff() const;

private:
    int mPin;
};



#endif //RGB_LED_HPP
