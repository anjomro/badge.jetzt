

#include "base/display.h"
#include "base/led.h"
#include "base/button.h"
#include "base/pins.h"
#include "etherbloom/mandelbrot.h"
#include "irrlicht/menusystem/menusystem.h"

void button_test();

int choice;

void setup() {
    Serial.begin(115200);
    Serial.println("badge.jetzt");

    button::init();
    led::init();
    display::init();

    display::clearDisplay();
    display::println("Chaos.JETZT! #9");
    display::println("26.05.2025 in Leipzig");
    display::println("");
    display::println("ESP-C3 - v1.0");
    display::display();

    // Six example options
    const char* options[] = {
        "Button Test",
        "Mandelbrot",
        "Y.A.M.S",
    };
    choice = display::makeMenu("Menu Test", options, 3);

    display::clearDisplay();
    // Workaround due to weird print and println shifts
    display::println("Selected: " + String(options[choice]));
    display::println("");
    display::println("Waiting for 2 seconds");
    display::display();
    delay(2000);
}


void loop() {
    display::clearDisplay();

    switch (choice) {
        case 0:
            button_test();
        break;
        case 1:
            mandelbrot::print_mandelbrot_set();
        break;
        case 2:
            menusystem::launch();
        break;
    }
}

void button_test() {
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