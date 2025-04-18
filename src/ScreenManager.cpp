//
// Created by Ferfoui on 13/04/2025.
//

#include "ScreenManager.hpp"

ScreenManager::ScreenManager(RgbLed led) :
        mLed(led),
        mScreen(SCREEN_WIDTH, SCREEN_HEIGHT, I2C_SDA_PIN, I2C_SCL_PIN, OLED_RESET)
{
}

void ScreenManager::init()
{
    mLed.setColor(INIT_COLOR);
    initScreen();
    if (!screenEnabled)
        return;
    writeChineseMessage(INIT_TEXT);

    initBluetooth();
    writeChineseMessage(INITIALIZED_TEXT);
}

void ScreenManager::update()
{
    if (!screenEnabled)
        return;

    mBluetoothSerial.loop();
}

void ScreenManager::initScreen()
{
    Serial.println("Initializing screen...");
    if (!mScreen.begin())
    {
        mLed.setColor(ERROR_COLOR); // Red color
        delay(500);
        return;
    }
    screenEnabled = true;
    mLed.setColor(SUCCESS_COLOR); // Green color
    Serial.println("Screen initialized");
}

void ScreenManager::initBluetooth()
{
    mBluetoothSerial.setName("Chinese ESP32");
    mBluetoothSerial.onConnect([this](const BLEDevice& device) { handleConnect(device); });
    mBluetoothSerial.onDisconnect([this](const BLEDevice& device) { handleDisconnect(device); });
    mBluetoothSerial.onReceive([this](const char *message) { handleReceive(message); });
    mBluetoothSerial.start();
    mLed.setColor(DISCONNECTED_COLOR);
}

void ScreenManager::handleConnect(const BLEDevice& device)
{
    Serial.println("Device connected");
    mLed.setColor(CONNECTED_COLOR);
    writeChineseMessage(CONNECTED_TEXT);
}

void ScreenManager::handleDisconnect(const BLEDevice& device)
{
    Serial.println("Device disconnected");
    mLed.setColor(DISCONNECTED_COLOR);
    writeChineseMessage(DISCONNECTED_TEXT);
}

void ScreenManager::handleReceive(const char *message)
{
    Serial.print("Message received: ");
    Serial.println(message);
    mScreen.clear();
    mScreen.writeText(message, 0, 0, 1);
}

Screen* ScreenManager::getScreen() {
    return &mScreen;
}

void ScreenManager::writeChineseMessage(const char *message)
{
    mScreen.clear();
    drawChineseString(0, SCREEN_HEIGHT/4, message, &mScreen);
}
