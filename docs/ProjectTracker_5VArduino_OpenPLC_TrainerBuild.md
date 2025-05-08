# 🔹 ProjectTracker_5VArduino_OpenPLC_TrainerBuild

## 🔢 Hardware Setup
- [ ] Mount Arduino Uno/Nano Every on base panel
- [ ] Install breadboard (for LEDs and button wiring)
- [ ] Wire Green Start Button (5V, INPUT_PULLUP)
- [ ] Wire Red Stop Button (5V, INPUT_PULLUP)
- [ ] Wire optional Fault Button (5V, INPUT_PULLUP)
- [ ] Install and wire Green, Red, Yellow LEDs with 220Ω resistors
- [ ] Connect 5V and GND rails cleanly (shared power)

## 🔢 OpenPLC Software Setup
- [ ] Flash OpenPLC firmware to Arduino
- [ ] Confirm OpenPLC runtime can detect Arduino board
- [ ] Create simple Ladder Logic program (Start/Stop latch)
- [ ] Test button functionality inside OpenPLC Editor
- [ ] Verify LED outputs toggle based on Ladder Logic

## 🔢 Testing and Verification
- [ ] Power cycle test (board restarts safely)
- [ ] Manual button press test (physical and OpenPLC input response)
- [ ] LED feedback test (correct LED for each state)
- [ ] Safety/Fault testing (if optional fault button wired)

---

# 🔹 Project Tracker: 12V M5Stack StamPLC Industrial Trainer Build

## 🔢 Hardware Setup
- [ ] Mount StamPLC on trainer base panel
- [ ] Wire 12V input power correctly (common ground for devices)
- [ ] Install 22mm Green Start Button (NO contact)
- [ ] Install 22mm Red Stop Button (NO contact)
- [ ] Install 22mm Red Emergency Stop Button (NC contact preferred)
- [ ] Wire 12V IR beam breaker sensors (future phase)
- [ ] Mount relay control field (motor light control etc.)
- [ ] Setup I2C GPIO expander (optional)

## 🔢 Arduino/PlatformIO Software Setup
- [ ] Setup PlatformIO project or Arduino IDE sketch for StamPLC
- [ ] Confirm basic digital input reading (Start/Stop/E-Stop)
- [ ] Confirm relay outputs activate correctly
- [ ] Implement basic control logic (Start/Stop Motor, Light Control)
- [ ] Plan future RS485 communication wiring

## 🔢 Testing and Verification
- [ ] Full power-up test (12V bus operational, safe GND sharing)
- [ ] Button and LED response verification
- [ ] Relay output verification (switching 12V loads)
- [ ] Safety lockout testing (Emergency Stop triggers output shutdown)

---

# ✅ Final Notes
- Progress milestones allow methodical development.
- Clean wiring and GND management at each step.
- Avoid mixing 5V and 12V systems during build/testing.
- Expand modularly: add RS485, sensors, and advanced functions later.

---

