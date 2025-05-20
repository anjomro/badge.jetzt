//
// Created by Anton Mrosek on 19.05.25.
//

#include "display.h"

namespace display
{

    Adafruit_SSD1306 oled(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

    uint8_t current_y = 0;

    void init()
    {
        oled.begin(SSD1306_SWITCHCAPVCC, 0x3C);
        oled.clearDisplay();
        oled.setTextSize(1);
        oled.setTextColor(SSD1306_WHITE);
        oled.display();
    }

    Adafruit_SSD1306& get()
    {
        return oled;
    }

    void clearDisplay()
    {
        oled.clearDisplay();
        current_y = 0;
    }

    void println(const char* text)
    {
        oled.setCursor(0, current_y);
        oled.print(text);
        current_y += 8;
    }

}
