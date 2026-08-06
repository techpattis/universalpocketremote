# PocketRemote

A portable ESP32-based universal infrared remote controller.

PocketRemote is a compact DIY remote control device that can capture, store, and transmit infrared (IR) signals using an ESP32 microcontroller. It is designed to control different IR-compatible devices in a small and portable form factor.

## Features

* ESP32-based control system
* Infrared signal receiving and transmitting
* Universal IR remote functionality
* 2-axis joystick control
* Portable LiPo battery powered design
* Built-in charging system
* Compact custom enclosure
* 3D printable case support

## Hardware

### Main Components

* ESPDuino-32 ESP32 WiFi & Bluetooth Development Board
* KY-005 IR Transmitter Module
* 38kHz IR Receiver Module
* 3.7V 950mAh LiPo Battery
* MCP73831T LiPo Charging Module
* 2-Axis Joystick Module
* Mini Illuminated Power Switch

### Passive Components

* 100KΩ 1/4W Resistor
* 1KΩ 2W Resistor

### Wiring Components

* Male-Male / Female-Female Jumper Wires
* Female-Male Jumper Wires

For the complete hardware list, see:

`Hardware/parts-list.md`

## Software

PocketRemote is programmed using:

* Arduino IDE
* ESP32 Arduino Core

## Project Structure


## How It Works

1. The IR receiver captures signals from existing remote controls.
2. The ESP32 processes and stores the received IR data.
3. The joystick is used to navigate and control functions.
4. The IR transmitter sends commands to compatible devices.

## Power

PocketRemote uses:

* 3.7V 1S LiPo battery
* MCP73831T charging circuit
* On/off power switch

The device can be charged through the built-in LiPo charging system.

## Future Improvements

Planned features:

* OLED display support
* Remote profile storage
* Better user interface
* More IR protocol support
* Custom PCB design
* Smaller enclosure design

## Gallery

(Add project photos here)

## License

This project is released under the MIT License.

You are free to use, modify, and share this project with proper credit.

## Author

Created by Hayat.
