# PLC Trainer Hardware Setup

This directory contains supporting documentation and images for the PLC Trainer Uno project.

---

## Hardware Overview

The current setup includes:
- Arduino Uno (or compatible)
- 3x momentary buttons (Start, Stop, Fault)
- 1x NeoPixel LED (single pixel strip)
- 1x Piezo buzzer
- 1x Buck converter module (for regulated 5V output)
- 1x 4-Channel 5V relay module
- 1x 12V 600W Power Supply (up to 10A output)
- 3D-printed mounting frame
- Arduino Uno Terminal Breakout shield

## Power System

- Primary 12V supply powers the motor.
- Buck converter steps down 12V to 5V for the relay module and other low-voltage components.
- Arduino powered separately or optionally through VIN (buck-converted).
- All devices share a common ground for reliable operation.

> ⚡ Future versions will transition to fully native 12V (and later 24V) relay modules for higher voltage robustness.

## Wiring Overview

_(Diagram to be added later.)_

| Pin | Purpose                      |
|-----|-------------------------------|
| D2  | Fault button input            |
| D3  | Stop button input             |
| D4  | Start button input            |
| D7  | NeoPixel LED data line         |
| D8  | Piezo buzzer                  |
| VIN | Optional: External 12V input to Arduino (via buck converter) |
| GND | Common ground for all modules  |

## Photos

![PLC Trainer Setup](plcTrainer_setup.jpg)

---

_This hardware documentation will expand as new features like motor control, analog sensors, and networking are added in later phases._

