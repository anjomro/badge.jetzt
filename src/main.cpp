/*

  Eine eigene Anwendung entwickeln in 4 Schritten:

  1. Eine Methode nach den Beispielen in example_apps.ino anlegen. Entweder dort, oder in einer neuen .ino-Datei
    - Die Anwendung muss eine blockierende Funktion sein. (z.B. mit delay()-Funktion, oder while-Schleife)
    - Mit einem return aus der Methode, wird die Anwendung beendet
  2. Vorwärtsdeklaration in dieser Datei (siehe unten) einfügen, damit der Compiler schon von von Anfang an die Signatur der Methode kennt.
  3. Einen Menüeintrag mit Titel und Methodenname im menu[]-Array (siehe unten) eintragen.
  4. Das Projekt kompilieren!

*/

#include "base/display.h"
#include "base/led.h"
#include "base/button.h"
#include "base/pins.h"
#include <WiFi.h>

// Vorwärts-Deklaration der Anwendungen
void appInfo();
void appSerialDemo();
void appScanWiFi();
void appSplashImage();
void appBlink();
void appTasterTest();

// Deklaration des Haupt-Menüs
void drawMenu();
void handleMenuInput();

// Struktur eines Menü-Eintrags
struct MenuEntry {
  const char* title;
  void (*action)();
};

// Menü-Einträge -- Methoden ohne "()" angeben, da diese hier nicht aufgerufen werden
MenuEntry menu[] = {
    { "Splash Image", appSplashImage },
    { "Blink LED", appBlink },
    { "Taster Test", appTasterTest },
    { "WiFi Scan", appScanWiFi },
    { "Serial Test", appSerialDemo },
    { "Info", appInfo },
};


void setup() {
    Serial.begin(115200);
    Serial.println("badge.jetzt");

    button::init();
    led::init();
    display::init();

    // splash-Image am Anfang
    display::clearDisplay();
    display::drawSplashImage();
    display::display();

    delay(4000); // <- hier ändern, wenn das Splash Image zu lang da is
}

// Menü-Zustand
int selected = 0;
bool inMenu = true;
const int menuSize = sizeof(menu) / sizeof(menu[0]);

void loop() {
    if (inMenu) {
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


/*
    Ab hier werden die Anwendungen definiert!
    Trage neue Anwendungen oben als Menü-Eintrag ein!
*/

void appSplashImage() {
    display::clearDisplay();
    display::drawSplashImage();
    display::display();
    delay(1000);
}

// Text auf dem Display anzeigen:
void appInfo() {
    display::println("Chaos.JETZT! #9");
    display::println("26.05.2025 in Leipzig");
    display::println("");
    display::println("ESP-C3 - v1.0");
    display::display();
    // wird die Vereinsgründung klappen?
    delay(5000);
}

// LEDs Blinken lassen:
void appBlink() {
    display::println("Blinking LED...");
    display::display();

    for (int i = 0; i < 5; i++) {
        led::set_r(100, 0, 0);
        delay(250);
        led::set_r(0, 100, 0);
        delay(250);
        led::set_r(0, 0, 100);
        delay(250);
        led::set_r(0, 0, 0);
        
        led::set_l(100, 0, 0);
        delay(250);
        led::set_l(0, 100, 0);
        delay(250);
        led::set_l(0, 0, 100);
        delay(250);
        led::set_l(0, 0, 0);
    }
}

// Eingaben der Taster erfassen:
void appTasterTest() {
  while(true) {
    display::clearDisplay();
    display::setCursor(0, 0);

    display::print(button::down(BTN1) ? "X " : "O ");
    display::print(button::down(BTN2) ? "X " : "O ");
    display::print(button::down(BTN3) ? "X " : "O ");
    display::print(button::down(BTN4) ? "X " : "O ");
    display::print(button::down(BTN5) ? "X " : "O ");
    display::print(button::down(BTN6) ? "X " : "O ");

    if (button::down(BTN1) && button::down(BTN2)) {
      return;
    }

    display::display();
    delay(100);
  }
}

// Diese Anwendung macht noch Probleme. Sie soll mit der seriellen Konsole kommunizieren.
void appSerialDemo() {
  delay(200);

  String inputBuffer = "";

  display::clearDisplay();
  display::println("Warte auf Input...");
  display::display();

  while (true) {
    char* lineBuffer = "test";
    while (Serial.available()) {
      char c = Serial.read();
    
      lineBuffer += c;

      if (c == '\n') {
        inputBuffer = lineBuffer + inputBuffer;

        // command parsing
        if(lineBuffer == "stop\n") {
          return;
        }

        lineBuffer = "";
      }
    }

    display::clearDisplay();
    display::println("Serieller Input:");
    display::print(lineBuffer);
    display::display();
    
    delay(200);
  } 
}

// Nach W-Lan-Netzen suchen und die SSIDs über die serielle Konsole ausgeben
void appScanWiFi() {
  display::println("Starte WiFi-Scan...");
  display::display();

  Serial.println("Starte WiFi-Scan...");
  
  WiFi.mode(WIFI_STA);
  WiFi.disconnect(true); // vorherige Verbindungen löschen
  delay(1000);

  int n = WiFi.scanNetworks();
  Serial.println("Netzwerke gefunden:");
  for (int i = 0; i < n; ++i) {
    Serial.print(i + 1);
    Serial.print(": ");
    Serial.print(WiFi.SSID(i));
    Serial.print(" (Signal: ");
    Serial.print(WiFi.RSSI(i));
    Serial.println(" dBm)");
  }

  display::clearDisplay();
  display::print(String(n).c_str());
  display::println("Netzwerke gefunden: ");
  display::println("siehe Serial Monitor!");
  display::display();
  delay(5000);
}