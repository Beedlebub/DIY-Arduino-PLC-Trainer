# PLC Trainer (Arduino Uno) (Currently @ Phase 2 Final)
🛠 Built with PlatformIO
🎯 Target platform: Arduino Uno

Overview:
This project simulates a basic industrial motor controller using an Arduino Uno. It can be programmed in C++, but better yet, use OpenPLC!!

It uses:
- Physical buttons
- A NeoPixel LED
- A piezo buzzer
...to represent machine states: Stopped, Running, and Fault.

Button holds are required for confirmation — not just taps — to better simulate real-world machine control systems.


Features:
✅ 3 Buttons for User Control:
- Start button → Begin motor (after 3s hold)
- Stop button → Stop motor (after 3s hold)
- Fault simulation button → Trigger immediate FAULT

✅ NeoPixel LED Visual Feedback:
- Solid Red → Machine Stopped
- Solid Green → Machine Running
- Flashing Yellow → During Start/Stop hold
- Fast Flashing Red → Active Fault
- Slow Flashing Red → Fault Clear in Progress

✅ Piezo Buzzer Audio Feedback:
- 1 beep → Start successful
- 2 beeps → Stop successful or Fault cleared
- 3 quick beeps → Fault triggered or recovered on power-up

✅ EEPROM Fault Recovery:
- Fault state is saved and restored after a power cycle.

✅ Debounced, Non-blocking Button Handling:
- Millis()-based, no delay() blocking.

✅ Modular Code Design:
- LedController class
- BuzzerController class


Hardware Requirements:
Component                               | Notes
Arduino Uno (or compatible)             | Standard AVR board
NeoPixel LED (single)                   | Data line to pin D7
Piezo buzzer                            | Connected to D8
3x Momentary buttons                    | Start (D4), Stop (D3), Fault (D2)
3x 10K Ohm pull-up resistors (optional) | Internal pull-ups enabled in software
Common ground across all components     | Essential


Wiring Diagram:
| Pin | Purpose          |
|-----|------------------|
| D2  | Fault Button      |
| D3  | Stop Button       |
| D4  | Start Button      |
| D7  | NeoPixel Data     |
| D8  | Piezo Buzzer      |
| 5V  | Shared Power      |
| GND | Shared Ground     |

+5V  ----+--------------------+
        |                    |
      (Button)             (Button)
    [Start] Pin D4      [Stop] Pin D3
        |                    |
        GND                  GND

    (Button)
  [Fault] Pin D2
      |
      GND

      +----------------+
      | NeoPixel (1x LED)
      |  Data In -> D7
      |  Power -> 5V
      |  GND -> GND
      +----------------+

      +----------------+
      | Piezo Buzzer
      |  + -> D8
      |  - -> GND
      +----------------+

(All components share a common ground.)



Quick Demo Instructions:
- Hold Start Button (D4) for 3 seconds → Motor "starts" (Solid Green LED + 1 beep).
- Hold Stop Button (D3) for 3 seconds → Motor "stops" (Solid Red LED + 2 beeps).
- Press Fault Button (D2) once → Immediate Fault (Fast Red Flash + 3 quick beeps).
- Hold Fault Button (D2) for 5 seconds → Clear Fault (Slow Red Flash during hold, 2 beeps after success).


Credits
- Developed by Beedlebub
- Technical architecture and code refinement support by OpenAI ChatGPT


