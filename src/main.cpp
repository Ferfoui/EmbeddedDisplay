#include <Arduino.h>

#include "main.hpp"
#include "RgbLed.hpp"
#include "Screen.hpp"

#include <BluetoothTerminal.h>


RgbLed rgbLed(RGB_LED_PIN);
Screen i2cScreen(SCREEN_WIDTH, SCREEN_HEIGHT, I2C_SDA_PIN, I2C_SCL_PIN, OLED_RESET);

BluetoothTerminal bluetoothTerminal;


void handleConnect(BLEDevice device)
{
    Serial.println("Device connected");
    rgbLed.setColor(0, 0, 32); // Blue color
}

void handleDisconnect(BLEDevice device)
{
    Serial.println("Device disconnected");
    rgbLed.setColor(32, 0, 0); // Red color
}

void handleReceive(const char *message)
{
    Serial.print("Message received: ");
    Serial.println(message);
    i2cScreen.clear();
    i2cScreen.writeText(message, 0, 0, 1);
}

void initBluetooth()
{
    bluetoothTerminal.setName("ESP32");
    bluetoothTerminal.onConnect(handleConnect);
    bluetoothTerminal.onDisconnect(handleDisconnect);
    bluetoothTerminal.onReceive(handleReceive);
    bluetoothTerminal.start();
}

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

    Serial.begin(9600);
    while (!Serial) {}

    initBluetooth();
}

unsigned long lastTimeMs = 0;

void loop()
{
    const unsigned long currentTimeMs = millis();

    if (currentTimeMs > lastTimeMs + 5000)
    {
        lastTimeMs = currentTimeMs;

        if (bluetoothTerminal.isConnected())
        {
            bluetoothTerminal.send("Hello, world!");
        }
    }

    bluetoothTerminal.loop();
}


