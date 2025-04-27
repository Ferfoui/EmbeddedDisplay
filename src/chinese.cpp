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
        {"消", char_xiao1_bmp},
        {"息", char_xi1_bmp},
        {"你", char_ni3_bmp},
        {"好", char_hao3_bmp},
        {"我", char_wo3_bmp},
        {"是", char_shi4_bmp},
        {"电", char_dian4_bmp},
        {"子", char_zi3_bmp},
        {"屏", char_ping2_bmp},
        {"幕", char_mu4_bmp},
        {"奥", char_ao4_bmp},
        {"剑", char_jian4_2_bmp},
        {"治", char_zhi4_bmp},
        {"计", char_ji4_bmp},
        {"了", char_le5_bmp},
};

bool isAValidChar(const char *character)
{
    // Check if the character is a valid UTF-8 encoded Chinese character (this is a simplified check)
    return (character[0] & 0xF0) == 0xE0 && (character[1] & 0xC0) == 0x80 && (character[2] & 0xC0) == 0x80;
}


void drawChineseChar(short x, short y, const char* character, Screen* screen)
{
    if (!isAValidChar(character))
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

void drawChineseString(const short x, const short y, const char* characters, Screen* screen)
{
    short offsetX = 0;

    // Iterate through the string and draw each character
    for (int i = 0; characters[i] != '\0'; i += 3)
    {
        const char character[4] = {characters[i], characters[i + 1], characters[i + 2], '\0'};
        const short xPosition = x + offsetX;
        drawChineseChar(xPosition, y, character, screen);
        offsetX += CHAR_WIDTH + GAP_BETWEEN_CHARS; // Adjust the offset for the next character
    }
}


