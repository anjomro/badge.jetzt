        /*

    Eine eigene Anwendung entwickeln in 4 Schritten:

    1. Eine Methode nach den Beispielen unten anlegen. Entweder da, oder in einer neuen Datei
        - Die Anwendung muss eine blockierende Funktion sein. (z.B. mit delay()-Funktion, oder while-Schleife)
        - Mit einem return aus der Methode, wird die Anwendung beendet
    2. Vorwärtsdeklaration in dieser Datei (siehe unten) einfügen, damit der Compiler schon von von Anfang an die Signatur der Methode kennt.
    3. Einen Menüeintrag mit Titel und Methodenname im menu[]-Array (siehe unten) eintragen.
    4. Das Projekt kompilieren!

    */

#include "menusystem.h"

#include "../exampleApps/exampleApps.h"

namespace menusystem {
    // Menü-Einträge -- Methoden ohne "()" angeben, da diese hier nicht aufgerufen werden
    MenuEntry menu[] = {
        { "Splash Image", exampleApps::appSplashImage },
        { "Blink LED", exampleApps::appBlink },
        // { "Taster Test", appTasterTest },
        // { "WiFi Scan", appScanWiFi },
        // { "Serial Test", appSerialDemo },
        // { "Info", appInfo },
    };

    // Menü-Zustand
    int selected = 0;
    bool inMenu = true;
    const int menuSize = sizeof(menu) / sizeof(menu[0]);

    void launch() {

        display::println("Yet Another Menu System");
        display::display();
        delay(1500);
        display::clearDisplay();

        while (inMenu) {
            handleMenuInput();
            drawMenu();
            delay(50);
        }
    }


    // Eingabelogik
    void handleMenuInput() {
        if (button::down(BTN1)) {
        selected = (selected - 1 + menuSize) % menuSize;
        delay(150); // Button-Debounce
        }
        else if (button::down(BTN2)) {
        selected = (selected + 1) % menuSize;
        delay(150); // Button-Debounce
        }
        else if (button::down(BTN3)) {
        // display zurücksetzen
        display::clearDisplay();
        display::setTextColor(SSD1306_WHITE, SSD1306_BLACK);
        delay(150); // Button-Debounce
        
        inMenu = false; // Menü pausieren
        menu[selected].action(); // Anwendung ausführen
        inMenu = true;
        }
    }
    
    // Menüanzeige
    void drawMenu() {
        display::clearDisplay();

        // display::println("Läuft");
    
        int visibleLines = 3;
        int start = selected - (selected % visibleLines); // Startindex des sichtbaren Blocks
    
        for (int i = 0; i < visibleLines; i++) {
            int index = start + i;
            if (index >= menuSize) break;
    
            if (index == selected)
                display::setTextColor(SSD1306_BLACK, SSD1306_WHITE); // Farben invertieren
            else
                display::setTextColor(SSD1306_WHITE, SSD1306_BLACK);
    
            // display.setCursor(0, i * 10);
            display::println(menu[index].title);
        }
    
        display::display();
    }
}