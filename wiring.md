# PocketRemote Wiring Guide

## ESP32 Pin Configuration

| Module                 | Pin    | ESP32 GPIO |
| ---------------------- | ------ | ---------- |
| OLED Display           | SDA    | GPIO 21    |
| OLED Display           | SCL    | GPIO 22    |
| KY-005 IR Transmitter  | Signal | GPIO 25    |
| 38kHz IR Receiver      | OUT    | GPIO 26    |
| Joystick X Axis        | VRx    | GPIO 34    |
| Joystick Y Axis        | VRy    | GPIO 35    |
| Joystick Button        | SW     | GPIO 32    |
| Battery Voltage Sensor | ADC    | GPIO 33    |

---

# OLED Display

SSD1306 128x64 I2C OLED:

```
OLED VCC → ESP32 3.3V
OLED GND → ESP32 GND
OLED SDA → GPIO 21
OLED SCL → GPIO 22
```

---

# IR Transmitter

KY-005:

```
KY-005 VCC → ESP32 3.3V
KY-005 GND → ESP32 GND
KY-005 SIG → GPIO 25
```

---

# IR Receiver

38kHz IR Receiver:

```
Receiver VCC → ESP32 3.3V
Receiver GND → ESP32 GND
Receiver OUT → GPIO 26
```

---

# Joystick Module

2-Axis Joystick:

```
Joystick VCC → ESP32 3.3V
Joystick GND → ESP32 GND

VRx → GPIO 34
VRy → GPIO 35
SW  → GPIO 32
```

---

# Battery Voltage Measurement

The battery voltage is measured using a resistor divider:

```
Battery +
    |
   100KΩ
    |
    +------ GPIO 33
    |
   100KΩ
    |
   GND
```

This allows the ESP32 ADC to safely measure the LiPo battery voltage.

---

## Notes

* Use 3.3V logic levels with ESP32 GPIO pins.
* Do not connect LiPo battery directly to ESP32 3.3V pin.
* Check polarity before connecting the battery.
