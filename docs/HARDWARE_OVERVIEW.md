# HARDWARE OVERVIEW

This document describes the hardware layout for the OpenPLC Trainer project.

## 📦 Components

- Arduino Nano RP2040 Connect (OpenPLC runtime)
- Breadboard (half-size)
- Fault Simulation Button
- Start and Stop Buttons
- NeoPixel LED (status indicator)
- Piezo Buzzer (alarm or alert sound)
- Relay Module (Channel 4 used for motor control)
- Buck Converter (provides regulated power)

## 🛠 Pin Mapping

| Pin | Function                        |
|-----|---------------------------------|
| D2  | Fault Simulation Button         |
| D3  | Stop Button                     |
| D4  | Start Button                    |
| D7  | NeoPixel LED (Signal Indicator) |
| D8  | Piezo Buzzer (Signal Output)    |
| D12 | Relay Channel 4 (Motor Control) |
| VIN/GND | Power input from Buck Converter |

### Notes:
- The motor is controlled by Relay Channel 4, mapped to **D12** (digital output).
- The buck converter supplies regulated voltage to the board through VIN and GND.
- The NeoPixel LED requires a single data line on **D7** for signaling.
- All buttons are active-low and use pull-down or pull-up resistors as needed.

## 📍 Expansion Areas (Future)

- Analog sensor integration (light, temperature, etc.)
- Modbus communication expansion (e.g., Raspberry Pi Pico W sensor bridge)
- PWM control of external devices through analog outputs (planned)

---

**License**: MIT  
**Author**: Beedlebub (Brand Inman) 
