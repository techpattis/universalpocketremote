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


## How It Works

1. # Hardware Compatibility Note

## ESP32 WROOM 32 and ESPDuino-32 Selection

In the provided circuit diagram, the **ESP32 WROOM 32 development board** is used as the main controller representation.

This choice was made because ESPDuino-32 is currently not available as a standard component in many circuit design applications, including Fritzing. Therefore, ESP32 WROOM 32 was selected for the schematic to provide a clear and widely recognized representation of the ESP32 platform.

However, the actual recommended hardware for this project is the **ESPDuino-32 development board**.

The reason for this recommendation is that ESPDuino-32 provides the same core ESP32 functionality while being a more affordable and accessible option for this project. It offers the required GPIO pins, processing power, and compatibility needed for the Pocket Remote system.

## Code Compatibility

No code modifications are required when switching between ESPDuino-32 and ESP32 WROOM 32 development boards.

The same firmware can run on both boards because they are based on the same ESP32 architecture.

The following components and connections remain identical:

* IR Receiver connection
* IR Transmitter connection
* OLED display connection
* GPIO assignments
* Libraries and software configuration

Therefore, users can choose either:

* **ESPDuino-32** — Recommended option due to its lower cost and availability
* **ESP32 WROOM 32 Development Board** — Fully compatible alternative

Both boards can run the Pocket Remote firmware without changing the source code.

2. The ESP32 processes and stores the received IR data.
3. The joystick is used to navigate and control functions.


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

Created by techpattis
