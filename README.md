# ARRP-26

## Connecting to the AP Portal

1. Power on the robot via USB-C or battery
2. On your phone or laptop, open WiFi settings and connect to the network **ARRP-26** with password **arrp2026**
3. Open a browser and go to **192.168.4.1**
4. The control portal will load with buttons for Lay Down, Stand Up, and Wave

## Flashing

1. Open `firmware/main.ino` in Arduino IDE
2. Select board: **LOLIN S2 Mini** under Tools → Board
3. Set **USB CDC On Boot** to Enabled
4. Upload
