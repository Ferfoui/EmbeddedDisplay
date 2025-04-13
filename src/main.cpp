#include <Arduino.h>

#include "RgbLed.hpp"
#include "ScreenManager.hpp"

#define RGB_LED_PIN 38

RgbLed rgbLed(RGB_LED_PIN);

ScreenManager screenManager(rgbLed);


void setup()
{
    Serial.begin(9600);
    while (!Serial) {}

    screenManager.init();

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


