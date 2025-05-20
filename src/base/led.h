//
// Created by Anton Mrosek on 19.05.25.
//

#ifndef LED_H
#define LED_H
#include <Adafruit_NeoPixel.h>
#include "pins.h"


namespace led
{



    void init();

    void set_r(uint8_t red,  uint8_t green, uint8_t blue);
    void set_l(uint8_t red,  uint8_t green, uint8_t blue);

    Adafruit_NeoPixel &get_l();
    Adafruit_NeoPixel &get_r();


}

#endif //LED_H
