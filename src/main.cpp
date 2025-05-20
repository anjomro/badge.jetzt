

#include "base/display.h"
#include "base/led.h"
#include "base/button.h"
#include "base/pins.h"


void setup() {
    Serial.begin(115200);
    Serial.println("badge.jetzt");

    button::init();
    led::init();
    display::init();


}



void loop() {
    String msg_l = "";
    String msg_r = "";


    if (button::down(BTN1)) { led::set_l(255,0,0); msg_l = "BTN1: Left Red"; }
    else if (button::down(BTN2)) { led::set_l(0,255,0); msg_l = "BTN2: Left Green"; }
    else if (button::down(BTN3)) { led::set_l(0,0,255); msg_l = "BTN3: Left Blue"; }
    else
    {
        led::set_l(0,0,0);
        msg_l = "--";
    }
    if (button::down(BTN4)) { led::set_r(255,0,0); msg_r = "BTN4: Right Red"; }
    else if (button::down(BTN5)) { led::set_r(0,255,0); msg_r = "BTN5: Right Green"; }
    else if (button::down(BTN6)) { led::set_r(0,0,255); msg_r = "BTN6: Right Blue"; }
    else
    {
        led::set_r(0,0,0);
        msg_r = "--";
    }


    // Update display::display
    display::clearDisplay();
    display::println("Button Test");
    display::println(msg_l);
    display::println(msg_r);
    display::println("Press any button");
    display::println("to change color");
    display::display();

    delay(100);
}