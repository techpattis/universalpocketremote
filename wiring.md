# Wiring Guide

## OLED (SSD1306)

| OLED | ESP32 |
|------|-------|
| VCC | 3.3V |
| GND | GND |
| SDA | GPIO21 |
| SCL | GPIO22 |

---

## IR Receiver

| Receiver | ESP32 |
|----------|-------|
| VCC | 3.3V |
| GND | GND |
| OUT | GPIO26 |

---

## KY-005 IR Transmitter

| KY-005 | ESP32 |
|--------|-------|
| Signal | GPIO25 |
| GND | GND |

The IR LED module is powered directly by the ESP32 output pin.

---

## Analog Joystick

| Pin | ESP32 |
|-----|-------|
| VRx | GPIO34 |
| VRy | GPIO35 |
| SW | GPIO32 |
| VCC | 3.3V |
| GND | GND |

---

## Battery Monitor

A voltage divider is used.

Battery (+)

↓

100kΩ

↓

GPIO33

↓

100kΩ

↓

GND

This reduces battery voltage to a safe ADC level.

---

## LiPo Battery

Battery

↓

Power Switch

↓

ESP32 VIN

The charging module is connected directly to the battery.

---

## Charging Module

USB-C

↓

MCP73831

↓

LiPo Battery

The ESP32 is powered from the battery, while charging is handled independently by the charging circuit.

---

## Notes and WARNING

- All grounds must be connected together.
- OLED uses I2C.
- The IR transmitter and receiver operate independently.
- The battery monitor requires the two 100kΩ resistors.
- The firmware is compatible with both ESPDuino-32 and ESP32-WROOM boards without modification.
- this is the schematic its Aİ generated because the components are used in this project are hard to find and We couldn't find any free schematic drawing software that contains these cards That's why I don't recommend you do this project based on this photo, but if you are going to do it, please be careful and protect yourself against the risk of getting hit by electricty.<img width="1024" height="682" alt="image" src="https://github.com/user-attachments/assets/57d609f7-dfa3-4efe-9430-f0288db51aa2" />

