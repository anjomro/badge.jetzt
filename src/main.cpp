#include "base/display.h"
#include "base/led.h"
#include "base/button.h"
#include "base/pins.h"
#include <WiFi.h>


void appInfo();
void appSerialDemo();
void appScanWiFi();
void appSplashImage();
void appBlink();
void appTasterTest();

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

    display::clearDisplay();

    display::drawSplashImage();
    display::display();
    delay(4000);

    // Six example options
    // const char* options[] = {
    //     "Lionbbb",
    //     "Tiger",
    //     "Bear",
    //     "Elephant",
    //     "Giraffe",
    //     "Zebra"
    // };
    // int todo = display::makeMenu("Button Test", options, 6);
    // display::clearDisplay();

    // // Print Result
    // display::print("Selected Option: ");
    // display::println(String(todo));
    // display::println(options[todo]);
    // display::display();
    // delay(3000);
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

    // String msg_l = "";
    // String msg_r = "";


    // if (button::down(BTN1)) { led::set_l(255,0,0); msg_l = "BTN1: Left Red"; }
    // else if (button::down(BTN2)) { led::set_l(0,255,0); msg_l = "BTN2: Left Green"; }
    // else if (button::down(BTN3)) { led::set_l(0,0,255); msg_l = "BTN3: Left Blue"; }
    // else
    // {
    //     led::set_l(0,0,0);
    //     msg_l = "--";
    // }
    // if (button::down(BTN4)) { led::set_r(255,0,0); msg_r = "BTN4: Right Red"; }
    // else if (button::down(BTN5)) { led::set_r(0,255,0); msg_r = "BTN5: Right Green"; }
    // else if (button::down(BTN6)) { led::set_r(0,0,255); msg_r = "BTN6: Right Blue"; }
    // else
    // {
    //     led::set_r(0,0,0);
    //     msg_r = "--";
    // }


    // // Update display::display
    // display::clearDisplay();
    // display::println("Button Test");
    // display::println(msg_l);
    // display::println(msg_r);
    // display::println("Press any button");
    // display::println("to change color");
    // display::display();

    // delay(100);
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

  // Eintrag-Nummer unten rechts anzeigen
    // display::setTextColor(SSD1306_WHITE, SSD1306_BLACK);
    // display::setCursor(108, 22);
    // display::print(selected+1);
    // display::print("/");
    // display::print(menuSize);

  display::display();
}

void appSplashImage() {
    display::clearDisplay();
    display::drawSplashImage();
    display::display();
    delay(1000);
}

void appInfo() {
    display::println("Chaos.JETZT! #9");
    display::println("26.05.2025 in Leipzig");
    display::println("");
    display::println("ESP-C3 - v1.0");
    display::display();
    delay(5000);
}

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