/*

Easy DIY OpenPLC Trainer running on an Arduino Uno
Phase 2 (Final Version with BuzzerController and LedController Classes)
-----------------------------------------------------------------------------------------------

- 3 buttons: START (Start button), STOP (Stop button), FAULT (Fault simulation button)
- 1 Neopixel LED to indicate machine state
- Piezo buzzer for sound feedback
- Non-blocking timing using millis()
- Proper button debouncing
- START and STOP require holding button for 3 continuous seconds
- FAULT clearing requires holding Fault button for 5 continuous seconds
- EEPROM saves FAULT state across power loss
- Clear modular structure with Buzzer and LED Controllers
*/

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include <EEPROM.h>

// --------- Pin Assignments ---------
const int startMotorButtonPin = 4;
const int stopMotorButtonPin = 3;
const int faultSimButtonPin = 2;
const int ledPin = 7;
const int ledCount = 1;
const int ledBrightness = 50;
const int buzzerPin = 8;  // Piezo connected here

// --------- EEPROM Address ---------
const int stateEEPROMAddress = 0;

// --------- Timing Constants ---------
const unsigned long slowBlinkInterval = 500;
const unsigned long fastBlinkInterval = 100;
const unsigned long faultClearDuration = 5000;
const unsigned long holdDuration = 3000;
const unsigned long debounceDelay = 50;

// --------- State Variables ---------
bool ledState = false;
unsigned long lastBlinkTime = 0;
unsigned long faultHoldStartTime = 0;
unsigned long startHoldStartTime = 0;
unsigned long stopHoldStartTime = 0;

bool startHoldInProgress = false;
bool stopHoldInProgress = false;
bool faultClearing = false;
bool startBlinkActive = false;
bool stopBlinkActive = false;

unsigned long activeBlinkInterval = slowBlinkInterval;

bool debouncedStartPressed = false;
bool debouncedStopPressed = false;
bool debouncedFaultPressed = false;

bool lastStartRawRead = HIGH;
bool lastStopRawRead = HIGH;
bool lastFaultRawRead = HIGH;

unsigned long lastStartDebounceTime = 0;
unsigned long lastStopDebounceTime = 0;
unsigned long lastFaultDebounceTime = 0;

// --------- System State Enum ---------
enum SystemState {
  OFF,
  RUNNING,
  FAULT
};
SystemState currentState = OFF;

// --------- LedController Class ---------
class LedController {
  private:
    Adafruit_NeoPixel strip;

  public:
    LedController(int pin, int count) : strip(count, pin, NEO_RGB + NEO_KHZ800) {}

    void begin() {
      strip.begin();
      delay(10);
      strip.clear();
      strip.show();
      strip.setBrightness(ledBrightness);
    }

    void setColor(uint8_t r, uint8_t g, uint8_t b) {
      strip.setPixelColor(0, strip.Color(r, g, b));
      strip.show();
    }

    void clear() {
      strip.clear();
      strip.show();
    }
};

// --------- BuzzerController Class ---------
class BuzzerController {
  private:
    int pin;

  public:
    BuzzerController(int p) : pin(p) {}

    void begin() {
      pinMode(pin, OUTPUT);
    }

    void beep(int times, int durationMs, int gapMs) {
      for (int i = 0; i < times; i++) {
        tone(pin, 2000);
        delay(durationMs);
        noTone(pin);
        if (i < times - 1) {
          delay(gapMs);
        }
      }
    }
};

// --------- Controller Instances ---------
LedController led(ledPin, ledCount);
BuzzerController buzzer(buzzerPin);

// --------- Function Declarations ---------
void setSystemOff();
void readButtons();
void handleOffState();
void handleRunningState();
void handleFaultState();
void handleBlink();
void saveFaultToEEPROM();
void clearFaultInEEPROM();

// --------- Setup Function ---------
void setup() {
  Serial.begin(115200);

  pinMode(startMotorButtonPin, INPUT_PULLUP);
  pinMode(stopMotorButtonPin, INPUT_PULLUP);
  pinMode(faultSimButtonPin, INPUT_PULLUP);

  led.begin();
  buzzer.begin();

  byte savedState = EEPROM.read(stateEEPROMAddress);
  if (savedState == 1) {
    Serial.println("Recovered FAULT from EEPROM");
    buzzer.beep(3, 75, 75);
    currentState = FAULT;
    activeBlinkInterval = fastBlinkInterval;
    lastBlinkTime = millis();
    ledState = false;
    faultClearing = false;
  } else {
    setSystemOff();
  }
}

// --------- Main Loop ---------
void loop() {
  readButtons();

  switch (currentState) {
    case OFF:
      handleOffState();
      break;
    case RUNNING:
      handleRunningState();
      break;
    case FAULT:
      handleFaultState();
      break;
  }

  handleBlink();
  delay(10);
}

// --------- Helper Functions ---------
void readButtons() {
  bool readingStart = (digitalRead(startMotorButtonPin) == LOW);
  bool readingStop = (digitalRead(stopMotorButtonPin) == LOW);
  bool readingFault = (digitalRead(faultSimButtonPin) == LOW);

  if (readingStart != lastStartRawRead) lastStartDebounceTime = millis();
  if (readingStop != lastStopRawRead) lastStopDebounceTime = millis();
  if (readingFault != lastFaultRawRead) lastFaultDebounceTime = millis();

  if ((millis() - lastStartDebounceTime) > debounceDelay) debouncedStartPressed = readingStart;
  if ((millis() - lastStopDebounceTime) > debounceDelay) debouncedStopPressed = readingStop;
  if ((millis() - lastFaultDebounceTime) > debounceDelay) debouncedFaultPressed = readingFault;

  lastStartRawRead = readingStart;
  lastStopRawRead = readingStop;
  lastFaultRawRead = readingFault;
}

void handleBlink() {
  unsigned long currentMillis = millis();

  bool shouldBlink = (currentState == FAULT) ||
                     (currentState == OFF && startBlinkActive) ||
                     (currentState == RUNNING && stopBlinkActive);

  if (!shouldBlink && !faultClearing) {
    return;
  }

  if (currentMillis - lastBlinkTime >= activeBlinkInterval) {
    lastBlinkTime = currentMillis;

    if (ledState) {
      led.clear();
    } else {
      if (currentState == FAULT) {
        led.setColor(255, 0, 0);
      } else {
        led.setColor(255, 255, 0);
      }
    }

    ledState = !ledState;
  }
}

void saveFaultToEEPROM() {
  EEPROM.write(stateEEPROMAddress, 1);
}

void clearFaultInEEPROM() {
  EEPROM.write(stateEEPROMAddress, 0);
}

// --------- State Handlers ---------
void setSystemOff() {
  currentState = OFF;
  led.setColor(255, 0, 0);
  Serial.println("System Initialized: OFF state");
}

void handleOffState() {
  unsigned long currentMillis = millis();

  if (debouncedStartPressed) {
    if (!startHoldInProgress) {
      startHoldInProgress = true;
      startHoldStartTime = currentMillis;
      startBlinkActive = true;
    } else {
      if (currentMillis - startHoldStartTime >= holdDuration) {
        buzzer.beep(1, 100, 100);
        Serial.println("Start Button Held 3 sec - Transition to RUNNING");
        currentState = RUNNING;
        led.setColor(0, 255, 0);
        startHoldInProgress = false;
        startBlinkActive = false;
      }
    }
  } else {
    if (startHoldInProgress) {
      Serial.println("Start Button Released Early - Cancel Start");
    }
    startHoldInProgress = false;
    startBlinkActive = false;
    led.setColor(255, 0, 0);
  }
}

void handleRunningState() {
  unsigned long currentMillis = millis();

  if (debouncedStopPressed) {
    if (!stopHoldInProgress) {
      stopHoldInProgress = true;
      stopHoldStartTime = currentMillis;
      stopBlinkActive = true;
    } else {
      if (currentMillis - stopHoldStartTime >= holdDuration) {
        buzzer.beep(2, 100, 100);
        Serial.println("Stop Button Held 3 sec - Transition to OFF");
        setSystemOff();
        stopHoldInProgress = false;
        stopBlinkActive = false;
      }
    }
  } else {
    if (stopHoldInProgress) {
      Serial.println("Stop Button Released Early - Cancel Stop");
    }
    stopHoldInProgress = false;
    stopBlinkActive = false;
    led.setColor(0, 255, 0);
  }

  if (debouncedFaultPressed) {
    buzzer.beep(3, 75, 75);
    Serial.println("Fault Button Pressed - Immediate FAULT");
    saveFaultToEEPROM();
    currentState = FAULT;
    activeBlinkInterval = fastBlinkInterval;
    lastBlinkTime = millis();
    ledState = false;
    faultClearing = false;
  }
}

void handleFaultState() {
  unsigned long currentMillis = millis();

  if (debouncedFaultPressed) {
    if (!faultClearing) {
      faultClearing = true;
      faultHoldStartTime = currentMillis;
      activeBlinkInterval = slowBlinkInterval;
    } else {
      if (currentMillis - faultHoldStartTime >= faultClearDuration) {
        buzzer.beep(2, 100, 100);
        Serial.println("Fault Button Held 5 sec - Clear FAULT");
        clearFaultInEEPROM();
        setSystemOff();
        faultClearing = false;
      }
    }
  } else {
    if (faultClearing) {
      Serial.println("Fault Button Released Early - Cancel Fault Clear");
    }
    faultClearing = false;
    activeBlinkInterval = fastBlinkInterval;
  }
}
