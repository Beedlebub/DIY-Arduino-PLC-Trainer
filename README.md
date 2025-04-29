# plcTrainer_Uno
## Trainer Setup

The photo below shows the Phase 2 trainer hardware in its current state.

It includes an Arduino Uno, labeled Start/Stop/Fault buttons, NeoPixel LED, piezo buzzer for state feedback, a buck converter module, and a 4-channel relay board — all mounted to a 3D-printed frame.

This modular hardware layout will support future phases as new features like motor control, analog sensors, and networking are added.

![PLC Trainer Setup](docs/plcTrainer_setup.jpg)



**Phase 2 Final Release**

---

## Overview

This project simulates a basic industrial motor control system using an Arduino Uno.
It uses physical buttons, a NeoPixel LED, and a piezo buzzer to represent machine states like **Stopped**, **Running**, and **Fault**.

User input requires **button holds** to validate intent, mimicking real-world industrial safety logic.
The project is designed using **simple C++ classes** for LED and Buzzer management, while keeping the main logic easily understandable.

---

## Features

- **3 Buttons**:
  - **Start Motor** Button
  - **Stop Motor** Button
  - **Fault Simulation** Button

- **NeoPixel LED Visual Feedback**:
  - Solid Red: Machine Stopped
  - Solid Green: Machine Running
  - Flashing Yellow: Holding Start/Stop
  - Fast Flashing Red: Active Fault
  - Slow Flashing Red: Clearing Fault

- **Piezo Buzzer Audio Feedback**:
  - 1 beep = Start Motor success
  - 2 beeps = Stop Motor or Fault Cleared
  - 3 beeps = Fault Detected (also after restart if fault persists)

- **EEPROM Fault Recovery**:
  - If the device is powered off during a fault, the fault state is recovered on reboot.

- **Non-blocking millis()-based Timing**:
  - For button debounce and blinking, no delay()-based blocking.

- **Simple Modular Classes**:
  - `LedController`
  - `BuzzerController`

---

## Hardware Requirements

| Component                     | Details                          |
| ------------------------------ | -------------------------------- |
| Arduino Uno or compatible      | Standard AVR board               |
| Single NeoPixel LED            | Connected to Pin 7               |
| Piezo Buzzer                   | Connected to Pin 8               |
| 3x Momentary Push Buttons      | Connected to Pins 2, 3, 4        |
| 3x (Optional) 10K Pull-up Resistors | Internal pullups enabled in code |
| Common Ground                  | Across all devices               |

---

## Pinout

| Pin | Purpose                      |
| --- | ----------------------------- |
| D2  | Fault Simulation Button       |
| D3  | Stop Motor Button             |
| D4  | Start Motor Button            |
| D7  | NeoPixel LED Data Line        |
| D8  | Piezo Buzzer                  |


---

## How to Build and Upload

### Recommended Toolchain:
- Visual Studio Code + PlatformIO Extension

### Quick Start
```bash
# Clone the repository
https://github.com/yourusername/plcTrainer_Uno.git

# Open the project in VS Code with PlatformIO

# Ensure `platformio.ini` looks like:

[env:uno]
platform = atmelavr
board = uno
framework = arduino
lib_deps =
  adafruit/Adafruit NeoPixel@^1.12.5

monitor_speed = 115200

# Then simply:
- Click "Build"
- Click "Upload"
- Open Serial Monitor
```

---

## Development Notes

- Code organized with simple helper classes for LED and Buzzer management.
- Phase 2 finalizes the "motor logic" portion without physical motor attached.
- PlatformIO used instead of Arduino IDE for better project management.

Future enhancements in Phase 3+ will add:
- Real motor control via relay/motor driver
- Better motor fault detection (stall, overcurrent, etc.)
- Expanded buzzer/LED patterns for more states
- Diagnostic serial logging improvements

---

## License

This project is licensed under the **MIT License**.

---

## Credits

- Developed by **Beedlebub** (Brand Inman)
- Technical guidance and development refinement supported by **OpenAI ChatGPT**

---

_"Build safe. Build smart. Build better. And always, build fun things!!"_

---

