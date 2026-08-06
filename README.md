# Pocket Remote v1

Pocket Remote v1 is an open-source universal infrared remote built around the ESP32 platform.

It allows users to learn, store, organize and transmit infrared signals from almost any IR-controlled device while remaining fully portable thanks to its rechargeable Li-Po battery.

The project was designed to be inexpensive, easy to build and completely open source.

---

# Features

- Learn almost any IR remote
- Store up to 20 buttons
- OLED graphical interface
- Rechargeable Li-Po battery
- Battery percentage indicator
- Delete saved buttons
- Portable handheld design
- ESP32 based
- Open Source (MIT License)

---

# Hardware

- ESPDuino-32
- (Compatible with ESP32-WROOM DevKit without changing the code)
- SSD1306 OLED Display
- KY-005 IR Transmitter
- 38kHz IR Receiver
- MCP73831 LiPo Charging Module
- 950mAh LiPo Battery
- Analog Joystick
- Power Switch

---

# Compatibility

The firmware was originally developed using the ESPDuino-32 board.

Since ESPDuino internally uses the ESP32-WROOM module, the exact same firmware also works on a regular ESP32-WROOM DevKit.

No code changes are required.

---

# Memory

Maximum saved buttons:

20

Maximum raw IR length:

300 samples

---

# User Interface

Main Menu

- New Button
- Buttons
- Battery
- Settings

---

# Learning a Remote

1. Select **New Button**
2. Enter a name.
3. Point your remote at the receiver.
4. Press any button.
5. Signal is stored automatically.

---

# Sending

1. Open Buttons.
2. Select the saved button.
3. Press OK.
4. Signal is transmitted.

---

# Supported Protocols

The project uses IRremoteESP8266 which supports many protocols including:

- NEC
- Sony
- Samsung
- LG
- Panasonic
- JVC
- RC5
- RC6
- Sharp
- Denon
- and many more.

Unknown protocols can also be stored as RAW timing data.

---

# Power

Powered by one 3.7V LiPo battery.

Charging is handled safely by the MCP73831 charging IC.

---

# License

MIT License
