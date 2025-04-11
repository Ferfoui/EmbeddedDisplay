#include <Arduino.h>

#include "RgbLed.hpp"
#include "Screen.hpp"

#define RGB_LED_PIN 38


#define I2C_SDA_PIN 4
#define I2C_SCL_PIN 5

#define OLED_RESET (-1) // Reset pin # (or -1 if sharing Arduino reset pin)

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32


RgbLed rgbLed(RGB_LED_PIN);
Screen i2cScreen(SCREEN_WIDTH, SCREEN_HEIGHT, I2C_SDA_PIN, I2C_SCL_PIN, OLED_RESET);

void setup()
{
    rgbLed.setColor(16, 0, 16);

    if (!i2cScreen.begin())
    {
        rgbLed.setColor(32, 0, 0); // Red color
    }
    else
    {
        rgbLed.setColor(0, 32, 0); // Green color
    }

    delay(3000);
}

void loop()
{
    // Set the RGB LED to blue
    rgbLed.setColor(0, 0, 32);
    delay(1000);

    // Set the RGB LED to purple
    rgbLed.setColor(16, 0, 16);
    delay(1000);

    rgbLed.turnOff();
    delay(1000);
}
