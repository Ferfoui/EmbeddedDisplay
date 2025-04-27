# EmbeddedDisplay

This is a little project to display things through a small OLED display connected to an
[ESP32-S3-DevKitC-1 v1.1](https://docs.espressif.com/projects/esp-dev-kits/en/latest/esp32s3/esp32-s3-devkitc-1/user_guide.html#esp32-s3-devkitc-1-v1-1) board.
The display is a 128x32 pixel monochrome OLED screen,
and the project uses the [ssd1306 library](https://github.com/adafruit/Adafruit_SSD1306) to control it.

The project is built using [PlatformIO](https://platformio.org/)
and the [Arduino framework](https://docs.platformio.org/en/latest/frameworks/arduino.html).
Moreover, it has been built for a Chinese class presentation (about chinese electronics).

## What does this project do?

This project allows the ESP32-S3 board to display chinese characters on an OLED screen.
It supports Bluetooth (Low Energy) communication, enabling users to send commands or messages to the board.
The board can display predefined chinese messages or user-provided (ASCII) text,
and it uses the embedded RGB LED to indicate the system's status (e.g., initialization, connection, or errors).

## How to build the project

1. Install [PlatformIO](https://platformio.org/) in your preferred IDE
(e.g., [CLion](https://docs.platformio.org/en/latest/integration/ide/clion.html#ide-clion),
[VS Code](https://docs.platformio.org/en/latest/integration/ide/vscode.html#ide-vscode)).
2. Clone this repository to your local machine.
3. Open the project folder in your IDE.
4. Connect your ESP32-S3 board to your computer via UART USB.
5. Build and upload the project using the PlatformIO interface.

## Configuration

- **ESP32-S3 Board**: [ESP32-S3-DevKitC-1 v1.1](https://docs.espressif.com/projects/esp-dev-kits/en/latest/esp32s3/esp32-s3-devkitc-1/user_guide.html#esp32-s3-devkitc-1-v1-1)
  - **Module Integrated**: ESP32-S3-WROOM-1-N8R2
  - **Flash Size**: 8 MB
  - **PSRAM**: 2 MB
  - **Power Supply**: USB power supply
- **OLED Display**: [APKLVSR I2C 128x32 OLED Display](https://www.amazon.fr/dp/B0D2L1ZDWP)

## Chinese characters integration

The project supports displaying Chinese characters on the OLED screen.
Each character is represented as a 16x16 bitmap stored in program memory (PROGMEM).
These bitmaps are mapped to their corresponding UTF-8 encoded characters in a dictionary (`chineseDictionary`). 

To display a character, the program searches the dictionary for the UTF-8 string and retrieves the associated bitmap.
If the character is not found, a placeholder bitmap is displayed instead.
The `drawChineseChar` and `drawChineseString` functions handle rendering individual characters and strings,
respectively, with proper spacing between characters.

Files [`chinese.h`](include/chinese.hpp) and
[`chinese.cpp`](src/chinese.cpp) contain the character bitmaps and the functions to display them.

## Libraries

- [Adafruit SSD1306](https://registry.platformio.org/libraries/adafruit/Adafruit%20SSD1306)
- [BluetoothTerminal](https://registry.platformio.org/libraries/loginov-rocks/BluetoothTerminal)

