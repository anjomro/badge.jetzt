//
// Created by Anton Mrosek on 19.05.25.
//

#include "button.h"

namespace button
{
    void init()
    {
        // Buttons
        for (uint8_t pin : {BTN1, BTN2, BTN3, BTN4, BTN5, BTN6}) {
            pinMode(pin, INPUT_PULLDOWN);
        }
    }


    bool down(uint8_t pin) {
        if (pin == BTN6 || pin == BTN4)
        {
            // Special PullUp; Low = 2.5V, High = 3.3V
            // Workaround: analogRead to get the voltage
            int value = analogRead(pin);
            if (value > 4000) {
                return true;
            }
            return false;
        }
        return digitalRead(pin);
    }
}
