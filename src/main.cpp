#include <Arduino.h>

#include "RgbLed.hpp"
#include "Screen.hpp"

#define RGB_LED_PIN 38


#define I2C_SDA_PIN 4
#define I2C_SCL_PIN 5

#define OLED_RESET (-1) // Reset pin # (or -1 if sharing Arduino reset pin)

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32

#define CHAR_HEIGHT 16
#define CHAR_WIDTH 16
static const unsigned char PROGMEM character_bmp[] =
{
    0x00, 0x00,
    0x01, 0x80,
    0x01, 0x80,
    0x01, 0x80,
    0x1F, 0xF8,
    0x3F, 0xFC,
    0x31, 0x8C,
    0x31, 0x8C,
    0x31, 0x8C,
    0x3F, 0xFC,
    0x1F, 0xF8,
    0x01, 0x80,
    0x01, 0x80,
    0x01, 0x80,
    0x01, 0x80,
    0x00, 0x00
};


RgbLed rgbLed(RGB_LED_PIN);
Screen i2cScreen(SCREEN_WIDTH, SCREEN_HEIGHT, I2C_SDA_PIN, I2C_SCL_PIN, OLED_RESET);

void setup()
{
    rgbLed.setColor(16, 0, 16);

    if (!i2cScreen.begin())
    {
        rgbLed.setColor(32, 0, 0); // Red color
        delay(500);
        return;
    }

    rgbLed.setColor(0, 32, 0); // Green color

    delay(2000);

    i2cScreen.clear();
    i2cScreen.drawBitmap(character_bmp,(SCREEN_WIDTH - CHAR_WIDTH) / 2, (SCREEN_HEIGHT - CHAR_HEIGHT) / 2, CHAR_WIDTH, CHAR_HEIGHT);
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
