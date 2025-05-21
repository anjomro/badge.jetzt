//
// Created by Anton Mrosek on 19.05.25.
//

#include "display.h"

#include "button.h"

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
        current_y += getCurrentCharHeight();
    }

    int availableLineCount()
    {
        // 32px / font height
        // Only count full lines
        return SCREEN_HEIGHT / getCurrentCharHeight();
    }


    int makeMenu(const char* title, const char* options[], int numOptions)
    {
        clearDisplay();
        if (title != nullptr && strlen(title) > 0)
        {
            setCursor(0, current_y);
            print(title);
            // Display for 60ms per character, + 500ms for reaction time
            delay(60 * strlen(title) + 500);
            display();
            clearDisplay();
        }
        int choosen = -1;
        int selected = 0;
        bool updated = true;

        // Repeat until a valid option is selected
        while (choosen == -1)
        {
            if (updated)
            {
                drawMenu(options, numOptions, selected);
                updated = false;
            }
            if (button::down(BTN1))
            {
                // Move cursor up, or wrap around
                selected = mod(selected - 1, numOptions);
                updated = true;
                delay(200);
            }
            else if (button::down(BTN2))
            {
                // Move cursor down, or wrap around
                selected = mod(selected + 1, numOptions);
                updated = true;
                delay(200);
            }
            else if (button::down(BTN3))
            {
                // Select option
                choosen = selected;
            }
        }
        return choosen;
    }


    void drawMenu(const char* options[], int numOptions, int selected)
    {
        clearDisplay();

        // Calculate how many lines we can display
        int maxLines = availableLineCount();
        int startIndex = 0;

        // Determine which options to display (create a scroll window)
        if (numOptions > maxLines)
        {
            // Try to center the selected item
            startIndex = selected - maxLines / 2;

            // Adjust if we would go out of bounds
            if (startIndex < 0)
            {
                startIndex = 0;
            }
            else if (startIndex + maxLines > numOptions)
            {
                startIndex = numOptions - maxLines;
            }
        }

        // Display visible options
        for (int i = 0; i < min(maxLines, numOptions); i++)
        {
            int optionIndex = startIndex + i;
            setCursor(0, i * getCurrentCharHeight());

            // Show selection marker
            if (optionIndex == selected)
            {
                print(">");
            }
            else
            {
                print(" ");
            }

            // Print the full option text
            setCursor(8, i * getCurrentCharHeight());
            print(options[optionIndex]);
        }

        // Update the display
        display();
    }
}
