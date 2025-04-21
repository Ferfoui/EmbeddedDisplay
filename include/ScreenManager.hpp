//
// Created by Ferfoui on 13/04/2025.
//

#ifndef SCREEN_MANAGER_HPP
#define SCREEN_MANAGER_HPP

#include <BluetoothTerminal.h>
#include "Screen.hpp"
#include "RgbLed.hpp"
#include "chinese.hpp"

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

#define INIT_TEXT "初始化中"
#define INITIALIZED_TEXT "系统已初始化"
#define CONNECTED_TEXT "连接已建立"
#define DISCONNECTED_TEXT "蓝牙已断开"
#define MESSAGE_TEXT "消息"
#define HELLO_TEXT "你好"
#define PRESENTATION_TEXT "我是电子屏幕"

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
    void writeChineseText(const char *text);

    void writeHelloMessage();
    void writePresentationMessage();
    void writeUserMessage(const char *message);
};


#endif //SCREEN_MANAGER_HPP
