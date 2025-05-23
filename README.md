# Die Chaos.jetzt badge!

Dieser programmierbare handheld besteht aus:
- ESP-C3 super mini
- 128x32 OLED Display
- 3 Tastern
- 2 RGB-LEDs

## Dieses Projekt flashen

Um dieses Projekt auf den handheld zu flashen, brauchst du die [PlatformIO-CLI](https://docs.platformio.org/en/latest/core/index.html)

Mit
```
platformio device list
```
kannst du dir die aktuell angeschlossenen Geräte anzeigen lassen.

Mit
```
platformio run --target upload
```
kannst du das aktuelle Projekt auf den ESP flashen.

## Eine eigene Anwendung hinzufügen

Du kannst den Code frei bearbeiten und dein eigenes Projekt umsetzen. Allerdings haben wir ein kleines Menü-System umgesetzt, mit dem du verschiedenste kleine Programme starten kannst.
Um eine eigene Anwendung in das Menü einzufügen, folge diesen Schritten:

1. Erstelle eine Methode, die deinen C++-Code enthält.
2. Füge eine Vorwärtsdeklaration oben in der Datei hinzu.
3. trage Titel und Methodenname im menu[]-Array ein
4. flashe das Projekt neu

Du kannst dich an den gegebenen Beispielen orientieren!

**Viel Spaß auf dem #jetzt9-Geekend!**