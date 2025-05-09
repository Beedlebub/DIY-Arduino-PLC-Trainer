# 🧠 OpenPLC Trainer — Phase 4 (Structured Text)

## 📦 Overview
This phase represents a transition from Arduino sketches (Phase 3) to a fully Structured Text (ST)-driven control system using the OpenPLC platform. The target hardware is an Arduino Uno R3.

## 🚦 Trainer Hardware Summary

| Component        | Description                |
|------------------|----------------------------|
| Controller       | Arduino Uno R3             |
| Inputs           | 2x Pushbuttons             |
| Outputs          | 3x LEDs (Green, Yellow, Red), 1x Relay, 1x Piezo buzzer |
| Power            | 5V logic, powered via USB  |

## 🧭 Pin Mapping Summary

See `docs/Pin info for OpenPLC.md` for full I/O mapping.

| Function       | Pin | OpenPLC Address |
|----------------|-----|-----------------|
| Start Button   | D2  | `%IX0.0`        |
| Stop Button    | D3  | `%IX0.1`        |
| Green LED      | D7  | `%QX0.0`        |
| Yellow LED     | D8  | `%QX0.1`        |
| Red LED        | D12 | `%QX0.2`        |
| Relay          | D13 | `%QX0.3`        |
| Piezo Buzzer   | D9  | `%QW0`          |

## 📂 Project Structure

phase4_dev/
├── logic/ # Structured Text files (.st)
├── mappings/ # OpenPLC CSV pin map
├── docs/ # Hardware, overview, and setup info
├── media/ # Photos or video demos
├── README.md # This document
└── RELEASE_NOTES.md # Version history


## 🛠 Setup Instructions

1. Flash the OpenPLC runtime to the Arduino Uno
2. Open OpenPLC Editor and load the `.st` logic from `logic/`
3. Load pin mapping from `mappings/pin_mapping.csv`
4. Compile, upload, and run your logic

## 🔭 Project Goals (for Phase 4)

- [ ] Recreate all trainer logic from Phase 3 in ST
- [ ] Test basic LED and relay functionality
- [ ] Add piezo tone control using analog output
- [ ] Document and share stable OpenPLC logic examples

## 📸 Media

- 📷 `media/trainer_phase4_front.jpg`
- 🎞 Demo video coming soon

## 📜 License & Attribution

MIT License. Hardware wiring and ST logic are shared to assist educators, hobbyists, and automation developers.

