# DIY PLC Trainer - Arduino Uno - Phase 3 (Motor Integration)

This project simulates a basic industrial Programmable Logic Controller (PLC) system using an Arduino Uno.  
It models machine states (Stopped, Running, Fault) and now **controls a real motor** through a relay.

![PLC Trainer Setup](docs/plcTrainer_setup.jpg)

## 📽️ Demo Video

[![Watch the demo](https://img.youtube.com/vi/JHllzX9L-uM/0.jpg)](https://www.youtube.com/watch?v=JHllzX9L-uM)

▶️ [Watch on YouTube](https://www.youtube.com/watch?v=JHllzX9L-uM)


---

## Features

✅ **Start Button** (Hold 3 seconds to start motor)  
✅ **Stop Button** (Hold 3 seconds to stop motor)  
✅ **Fault Simulation Button** (Instantly trigger fault)  
✅ **Motor Relay Control** (Pin 12)  
✅ **Visual LED Feedback**  
✅ **Audible Buzzer Feedback**  
✅ **Fault Recovery via EEPROM**  
✅ **Non-blocking `millis()` timing for LED and buttons**  
✅ **Clean C++ classes for LED and buzzer handling**  

---

## System Behavior

| State | LED Feedback | Buzzer Feedback | Motor Relay |
|:-----|:-------------|:----------------|:------------|
| Stopped (OFF) | Solid Red | 2 beeps (stop success) | OFF |
| Running | Solid Green | 1 beep (start success) | ON |
| Holding Start/Stop | Flashing Yellow | None during hold | (Depends) |
| Fault Active | Fast Flashing Red | 3 quick beeps | OFF |
| Fault Clearing | Slow Flashing Red | 2 beeps when cleared | OFF |

---

## Hardware Requirements

| Component | Notes |
|:----------|:------|
| Arduino Uno | Standard AVR |
| Terminal Breakout Shield | For easier wiring |
| NeoPixel LED | Data pin 7 |
| Piezo Buzzer | Pin 8 |
| 4-Channel Relay Module | 5V type, triggered LOW |
| 12V DC Motor | Driven by Relay Channel 4 |
| 12V 10A Power Supply | Powers entire system |
| 3x Momentary Buttons | Start, Stop, Fault Sim |
| 3D-Printed Mounting Frame | Optional for neatness |

---

## Wiring Overview

| Arduino Pin | Connected To |
|:------------|:-------------|
| D2 | Fault Simulation Button |
| D3 | Stop Button |
| D4 | Start Button |
| D7 | NeoPixel LED (Signal) |
| D8 | Piezo Buzzer |
| D12 | Relay Channel 4 (Motor Control) |
| VIN/GND | Buck converter |

---

## Setup Instructions

1. Clone the repository:
    ```bash
    git clone https://github.com/Beedlebub/plcTrainer_Uno.git
    ```

2. Open project in **VSCode + PlatformIO**.

3. Verify `platformio.ini` settings:
    ```ini
    [env:uno]
    platform = atmelavr
    board = uno
    framework = arduino
    lib_deps = 
      adafruit/Adafruit NeoPixel@^1.12.5
    monitor_speed = 115200
    ```

4. Connect hardware as per wiring diagram.

5. Upload firmware:
    - Press PlatformIO "Upload" button or use `pio run --target upload`.

6. Open Serial Monitor (115200 baud) to watch debug output.

---

## Versioning

- `Phase 3.0.4`  
- Code includes helper classes, clean state management, and motor relay integration.
- Added return after transitioning to FAULT to avoid "released early" print.
- Improved early-release handling and comment clarity.


Future Roadmap:
- Add some analog sensors to the circuit: light and temp
- Port this functionality to OpenPLC
- Expand system to higher voltages (12V and eventually 24V).

---

## License

MIT License

---

**Build smart. Build safe. Build awesome. And above all — have fun! 🚀**
