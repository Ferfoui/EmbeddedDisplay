#include <Arduino.h>

#include "main.hpp"
#include "RgbLed.hpp"

#include "ScreenManager.hpp"


RgbLed rgbLed(RGB_LED_PIN);

ScreenManager screenManager(rgbLed);


void setup()
{
    Serial.begin(9600);
    while (!Serial) {}

    screenManager.init();

    screenManager.getScreen()->clear();
    screenManager.getScreen()->drawBitmap(zhong_bmp, (SCREEN_WIDTH - CHAR_WIDTH) / 2 - 50, (SCREEN_HEIGHT - CHAR_HEIGHT) / 2, CHAR_WIDTH, CHAR_HEIGHT);
    delay(500);
    screenManager.getScreen()->drawBitmap(wen_bmp, (SCREEN_WIDTH - CHAR_WIDTH) / 2 + 18 - 50, (SCREEN_HEIGHT - CHAR_HEIGHT) / 2, CHAR_WIDTH, CHAR_HEIGHT);
    delay(500);
    screenManager.getScreen()->scrollRight();
}

unsigned long lastTimeMs = 0;

void loop()
{
    const unsigned long currentTimeMs = millis();

    if (currentTimeMs > lastTimeMs + 5000)
    {
        lastTimeMs = currentTimeMs;
    }

    screenManager.update();
}


