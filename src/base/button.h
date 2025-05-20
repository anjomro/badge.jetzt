//
// Created by Anton Mrosek on 19.05.25.
//

#ifndef BUTTON_H
#define BUTTON_H

#include <Arduino.h>
#include "pins.h"

namespace button
{
    void init();
    bool down(uint8_t pin);
}

#endif //BUTTON_H
