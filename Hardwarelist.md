# Hardware Information

Pocket Remote v1 was designed around inexpensive, reliable and widely available components.

---

## ESPDuino-32

Main controller.

Responsibilities:

- OLED control
- IR learning
- IR transmission
- EEPROM storage
- Joystick handling
- Battery monitoring

The firmware is also fully compatible with ESP32-WROOM development boards.

---

## OLED Display

Model

SSD1306

Resolution

128 × 64

Interface

I2C

Purpose

Displays:

- Menus
- Button names
- Battery percentage
- Settings
- Learning screens

---

## IR Receiver

38kHz Infrared Receiver Module

Purpose

Receives infrared signals from existing remote controls.

Used only while learning.

---

## IR Transmitter

KY-005

Purpose

Transmits learned infrared commands.

---

## Battery

3.7V
950mAh
LiPo

Advantages

- Rechargeable
- Lightweight
- High energy density
- Portable

---

## Charging Circuit

MCP73831

The battery is **never connected directly to USB.**

The MCP73831:

- controls charging current
- prevents overcharging
- automatically stops charging at 4.2V
- protects battery life
- increases overall safety

This makes the device significantly safer than charging the battery directly.

---

## Joystick

Two-axis analog joystick.

Functions

- Up
- Down
- Left
- Right
- Push button

Used for complete menu navigation.

---

## Power Switch

Disconnects battery from the system.

No standby current is consumed when switched off.

---

## Storage

ESP32 Preferences library

No SD card required.

All buttons are stored in internal flash memory.

---

## Capacity

Maximum saved buttons

20

Maximum RAW signal length

300 timing values
