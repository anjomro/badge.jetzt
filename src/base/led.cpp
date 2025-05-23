//
// Created by Anton Mrosek on 19.05.25.
//


#include "pins.h"
#include "led.h"



#include <Adafruit_NeoPixel.h>

namespace led
{

    Adafruit_NeoPixel l(1, LEDL, NEO_GRB + NEO_KHZ800);
    Adafruit_NeoPixel r(1, LEDR, NEO_GRB + NEO_KHZ800);

    void init()
    {
        l.begin();
        r.begin();
        l.show();
        r.show();
    }

    Adafruit_NeoPixel &get_l()
    {
        return l;
    }
    Adafruit_NeoPixel &get_r()
    {
        return r;
    }


    void set_r(const uint8_t red, const uint8_t green, const uint8_t blue)
    {
        r.setPixelColor(0, Adafruit_NeoPixel::Color(red, green, blue));
        r.show();
    }
    void set_l(const uint8_t red, const uint8_t green, const uint8_t blue)
    {
        l.setPixelColor(0, Adafruit_NeoPixel::Color(red, green, blue));
        l.show();
    }

}
