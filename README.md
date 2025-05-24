# badge.jetzt


## How to build the badge hardware

1. Get the PCB
2. Solder the ESP32-C3 module to the PCB
3. Solder the WS2812B LEDs to the PCB
   1. The LEDs have a white corner on one corner, this needs to be on the top left corner for both LEDs
4. Solder the OLED Display to the PCB
5. Solder the buttons to the PCB
6. Flash the software to the ESP32-C3 module
   1. Install [platformio](https://platformio.org/platformio-ide) or the [CLI](https://docs.platformio.org/en/latest/core/index.html)
   2. Clone the repository: `git clone git@github.com:anjomro/badge.jetzt.git`
   3. Upload the project, run `pio run -t upload`

![ESP-C3 with PCB](images/esp_with_pcb_separated.jpg "ESP-C3 with PCB separated")
![ESP-C3 with PCB soldered](images/esp_with_pcb_soldered.jpg "ESP-C3 with PCB soldered")
![PCB front with display](images/pcb_with_display.jpg "PCB with display soldered on ti")

## PlatformIO on different Systems:
**Arch**: `sudo pacman -Sy platformio-core`

**Debian/Ubuntu**: 

 1. PlatformIO installieren ([Platformio install](https://docs.platformio.org/en/latest/core/installation/methods/installer-script.html)), zum Beispiel:
    1. `wget -O get-platformio.py https://raw.githubusercontent.com/platformio/platformio-core-installer/master/get-platformio.py`
    2.  `python3 get-platformio.py`
2. Repo klonen: `git clone https://github.com/anjomro/badge.jetzt.git`
3. add PlatformIO Core binary directory to the system environment PATH variable (im bashrc), zum Beispiel
   1. `nano .bashrc`
   2. ganz unten `export PATH="$PATH:Your/Path/To/PlatformIO/bin/directory"` hinzufügen
   3. `source .bashrc`
4. udev rules [siehe Anleitung installieren](https://docs.platformio.org/en/latest/core/installation/udev-rules.html), zum Beispiel
   1. `curl -fsSL https://raw.githubusercontent.com/platformio/platformio-core/develop/platformio/assets/system/99-platformio-udev.rules | sudo tee /etc/udev/rules.d/99-platformio-udev.rules`
   2. `sudo service udev restart`
   3. physically unplug and reconnect your board
5. im badge.jetzt directory `pio run -t upload` ausführen

**Nix**:
```Bash
git clone 'https://github.com/anjomro/badge.jetzt/tree/docs'
nix develop
pio run -t upload
```
