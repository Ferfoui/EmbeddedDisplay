//
// Created by Ferfoui on 13/04/2025.
//

#include "chinese.hpp"

#include "Screen.hpp"

ChineseChar chineseDictionary[] = {
        {"中", char_zhong1_bmp},
        {"文", char_wen2_bmp},
        {"系", char_xi4_bmp},
        {"统", char_tong3_bmp},
        {"已", char_yi3_bmp},
        {"初", char_chu1_bmp},
        {"始", char_shi3_bmp},
        {"化", char_hua4_bmp},
        {"设", char_she4_bmp},
        {"备", char_bei4_bmp},
        {"连", char_lian2_bmp},
        {"接", char_jie1_bmp},
        {"建", char_jian4_bmp},
        {"立", char_li4_bmp},
        {"蓝", char_lan2_bmp},
        {"牙", char_ya2_bmp},
        {"断", char_duan4_bmp},
        {"开", char_kai1_bmp},
};

bool isValidUtf8Char(const char *character)
{
    // Check if the character is a valid UTF-8 encoded Chinese character
    return (character[0] & 0xF0) == 0xE0 && (character[1] & 0xC0) == 0x80 && (character[2] & 0xC0) == 0x80;
}


void drawChineseChar(short x, short y, const char *character, Screen* screen)
{
    if (!isValidUtf8Char(character))
    {
        Serial.println("Invalid UTF-8 character");
        return;
    }
    // Search for the character in the chineseDictionary
    for (const auto &ch : chineseDictionary)
    {
        if (strcmp(ch.utf8, character) == 0)
        {
            screen->drawBitmap(ch.bitmap, x, y, CHAR_WIDTH, CHAR_HEIGHT);
            return;
        }
    }
    screen->drawBitmap(char_placeholder_bmp, x, y, CHAR_WIDTH, CHAR_HEIGHT);
}

void drawChineseString(short x, short y, const char *characters, Screen* screen)
{
    short offsetX = 0;
    short offsetY = 0;

    // Iterate through the string and draw each character
    for (int i = 0; characters[i] != '\0'; i += 3)
    {
        char character[4] = {characters[i], characters[i + 1], characters[i + 2], '\0'};
        short xPosition = x + offsetX;
        short yPosition = y + offsetY;
        drawChineseChar(xPosition, yPosition, character, screen);
        offsetX += CHAR_WIDTH + GAP_BETWEEN_CHARS; // Adjust the offset for the next character
    }
}


