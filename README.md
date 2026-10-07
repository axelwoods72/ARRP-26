# ARRP-26

## Connecting to the AP Portal

1. Power on the robot
2. On your phone or laptop, open WiFi settings and connect to the network **ARRP-26** with password **arrp2026**
3. Open a browser and go to **192.168.4.1**
4. The control portal will load with buttons for servo animations and OLED display faces

## Flashing

### First-time Arduino IDE setup

1. Open Settings (`Cmd + ,` on Mac, or File → Preferences on Windows)
2. Paste this into **Additional boards manager URLs**:
   ```
   https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
   ```
3. Go to Tools → Board → Boards Manager, search `esp32` by Espressif, and install it

### Uploading

1. Open `firmware/firmware.ino` in Arduino IDE
2. Select board: Tools → Board → ESP32 → **LOLIN S2 Mini**
3. Set Tools → **USB CDC On Boot** → **Enabled**
4. Enter bootloader mode: hold the **0** (BOOT) button, press and release **RST**, then release **0**
5. Upload
6. Press **RST** once more to boot into the firmware
