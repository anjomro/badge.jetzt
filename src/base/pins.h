//
// Created by Anton Mrosek on 19.05.25.
//

#ifndef PINS_H
#define PINS_H

// Buttons, layouted like the following
// Connected to 3V3, need internal pulldown
// Default Low, High when pressed

// BTN1      DISPLAY       BTN4
// BTN2 BTN3         BTN6  BTN5

#define BTN1 7
#define BTN2 6
#define BTN3 5
#define BTN4 0
#define BTN5 3
#define BTN6 4

//uint8_t buttons[] = {BTN1, BTN2, BTN3, BTN4, BTN5, BTN6};


// LED Left and Right
// One LED (WS2812B) per pin/side

#define LEDL 21
#define LEDR 1


#endif //PINS_H
