//
// Created by Ferfoui on 13/04/2025.
//

#include "chinese.hpp"

#include "Screen.hpp"

ChineseChar chineseDictionary[] = {
        {"中", zhong_bmp},
        {"文", wen_bmp}
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


