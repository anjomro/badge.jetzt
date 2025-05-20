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
    void println(const char* text);
    inline void println(const String& text) { println(text.c_str()); }


}

#endif //DISPLAY_H
