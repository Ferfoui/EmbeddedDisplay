//
// Created by Ferfoui on 13/04/2025.
//

#ifndef SCREEN_MANAGER_HPP
#define SCREEN_MANAGER_HPP

#include "Screen.hpp"
#include "RgbLed.hpp"
#include <BluetoothTerminal.h>

#define I2C_SDA_PIN 4
#define I2C_SCL_PIN 5

#define OLED_RESET (-1) // Reset pin # (or -1 if sharing Arduino reset pin)

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32

#define INIT_COLOR         16, 0, 16  // Purple
#define ERROR_COLOR        32, 0, 0   // Red
#define SUCCESS_COLOR      0, 32, 0   // Green
#define CONNECTED_COLOR    0, 0, 32   // Blue
#define DISCONNECTED_COLOR 16, 16, 0  // Yellow

class ScreenManager {
public:
    explicit ScreenManager(RgbLed led);
    void init();
    void update();
    Screen* getScreen();
private:
    Screen mScreen;
    BluetoothTerminal mBluetoothSerial;
    RgbLed mLed;
    bool screenEnabled = false;
    void initScreen();
    void initBluetooth();
    void handleConnect(const BLEDevice& device);
    void handleDisconnect(const BLEDevice& device);
    void handleReceive(const char *message);
};


#endif //SCREEN_MANAGER_HPP
