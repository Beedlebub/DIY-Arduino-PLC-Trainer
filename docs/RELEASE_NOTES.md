# Release Notes

## Version 3.0.5 - [2025-05-01]

### 🎯 Overview
This release finalizes the Arduino Uno version of the PLC Trainer project.  
It focuses primarily on documentation updates to fully reflect the current hardware wiring and system layout.

### ✨ Changes

- Updated `HARDWARE_OVERVIEW.md`:
  - Added 12V DC Motor entry to hardware requirements
  - Documented Relay Channel 4 (D12) controlling the motor
  - Specified Buck Converter supplying power via VIN/GND
  - Clarified NeoPixel and Piezo functions

- General documentation cleanup for better clarity and maintainability
- Confirmed Arduino Uno pin mappings are complete and accurate
- Minor wording improvements in existing documentation files

### 📦 Impact
- No code logic changes were made
- Hardware and wiring documentation is now aligned with the current physical trainer
- This release locks in the Uno-based trainer as a known working baseline

### 🛠 Next Steps
- Create a new Git branch (`nano-rp2040-testing`) to migrate and expand the project to the Arduino Nano RP2040 Connect hardware
- Maintain the Uno version as the stable reference version moving forward

---

**Tag**: `v3.0.5`  
**Release Date**: 2025-05-01
