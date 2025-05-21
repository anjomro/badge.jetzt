//
// Created by Anton Mrosek on 19.05.25.
//

#ifndef DISPLAY_H
#define DISPLAY_H

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// OLED Display
// SSD1306, 128x32, 0.91 inch
// Connected via I2C
// Default I2C pins: SDA: 8, SCL: 9
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32
#define OLED_RESET    -1



namespace display
{
    void init();
    Adafruit_SSD1306& get();


    void clearDisplay();
    inline void display() { get().display(); }
    inline void print(const char* text) { get().print(text); }
    inline void setCursor(uint8_t x, uint8_t y) { get().setCursor(x, y); }
    void println(const char* text);
    inline void println(const String& text) { println(text.c_str()); }

    inline int getCurrentCharHeight() { return 8; }
    int availableLineCount();
    int makeMenu(const char* title, const char* options[], int numOptions);
    inline int makeMenu(const char* options[], int numOptions) { return makeMenu(nullptr, options, numOptions); }
    void drawMenu(const char* options[], int numOptions, int selected);
    inline int mod(int a, int b) { return (a % b + b) % b; }

}

#endif //DISPLAY_H
