#include <Arduino.h>

#include "main.hpp"
#include "RgbLed.hpp"
#include "Screen.hpp"

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
    i2cScreen.drawBitmap(zhong_bmp, (SCREEN_WIDTH - CHAR_WIDTH) / 2, (SCREEN_HEIGHT - CHAR_HEIGHT) / 2, CHAR_WIDTH, CHAR_HEIGHT);
    i2cScreen.drawBitmap(wen_bmp, (SCREEN_WIDTH - CHAR_WIDTH) / 2 + 18, (SCREEN_HEIGHT - CHAR_HEIGHT) / 2, CHAR_WIDTH, CHAR_HEIGHT);
    i2cScreen.scrollRight();
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
