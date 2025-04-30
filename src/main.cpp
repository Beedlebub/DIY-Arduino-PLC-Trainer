// Phase 3.0.4: Fixed double-print on fault press
// ------------------------------------------------------------
// - Added return after transitioning to FAULT to avoid "released early" print

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
const int buzzerPin = 8;
const int motorRelayPin = 12;

// --------- EEPROM Address ---------
const int stateEEPROMAddress = 0;

// --------- Timing Constants ---------
const unsigned long slowBlinkInterval = 500;
const unsigned long fastBlinkInterval = 100;
const unsigned long faultClearDuration = 5000;
const unsigned long holdDuration = 3000;
const unsigned long debounceDelay = 50;

// --------- System State Enum ---------
enum SystemState {
  OFF,
  RUNNING,
  FAULT
};
SystemState currentState = OFF;

// --------- LED and Buzzer Controllers ---------
class LedController {
  private:
    Adafruit_NeoPixel strip;
  public:
    LedController(int pin, int count) : strip(count, pin, NEO_RGB + NEO_KHZ800) {}
    void begin() { strip.begin(); delay(10); strip.clear(); strip.show(); strip.setBrightness(ledBrightness); }
    void setColor(uint8_t r, uint8_t g, uint8_t b) { strip.setPixelColor(0, strip.Color(r, g, b)); strip.show(); }
    void clear() { strip.clear(); strip.show(); }
};

class BuzzerController {
  private:
    int pin;
  public:
    BuzzerController(int p) : pin(p) {}
    void begin() { pinMode(pin, OUTPUT); }
    void beep(int times, int durationMs, int gapMs) {
      for (int i = 0; i < times; i++) {
        tone(pin, 2000);
        delay(durationMs);
        noTone(pin);
        if (i < times - 1) delay(gapMs);
      }
    }
};

// --------- Button Handler Class ---------
class ButtonHandler {
  private:
    int pin;
    bool lastRawState = HIGH;
    unsigned long lastDebounceTime = 0;
    bool debouncedPressed = false;
    unsigned long holdStartTime = 0;
    bool holdActive = false;
    bool releasedEarly = false;

  public:
    ButtonHandler(int p) : pin(p) {}

    void begin() { pinMode(pin, INPUT_PULLUP); }

    void update() {
      bool rawState = digitalRead(pin);
      if (rawState != lastRawState) lastDebounceTime = millis();
      if ((millis() - lastDebounceTime) > debounceDelay) debouncedPressed = (rawState == LOW);
      lastRawState = rawState;
    }

    bool isPressed() { return debouncedPressed; }

    bool startHold(unsigned long durationMs) {
      if (debouncedPressed) {
        if (!holdActive) {
          holdStartTime = millis();
          holdActive = true;
        } else if (millis() - holdStartTime >= durationMs) {
          holdActive = false;
          return true;
        }
      } else {
        if (holdActive && (millis() - holdStartTime < durationMs)) {
          releasedEarly = true;
        }
        holdActive = false;
      }
      return false;
    }

    bool isHolding() { return debouncedPressed && holdActive; }

    bool wasReleasedEarly(unsigned long durationMs) {
      if (releasedEarly) {
        releasedEarly = false;
        return true;
      }
      return false;
    }
};

// --------- Instances ---------
LedController led(ledPin, ledCount);
BuzzerController buzzer(buzzerPin);
ButtonHandler startBtn(startMotorButtonPin);
ButtonHandler stopBtn(stopMotorButtonPin);
ButtonHandler faultBtn(faultSimButtonPin);

// --------- Blink State ---------
bool ledState = false;
unsigned long lastBlinkTime = 0;
unsigned long activeBlinkInterval = slowBlinkInterval;
bool startBlinkActive = false;
bool stopBlinkActive = false;
bool faultClearing = false;

// --------- Function Declarations ---------
void setSystemOff();
void handleOffState();
void handleRunningState();
void handleFaultState();
void handleBlink();
void saveFaultToEEPROM();
void clearFaultInEEPROM();

// --------- Setup Function ---------
void setup() {
  Serial.begin(115200);
  pinMode(motorRelayPin, OUTPUT);
  led.begin();
  buzzer.begin();
  startBtn.begin();
  stopBtn.begin();
  faultBtn.begin();

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
  startBtn.update();
  stopBtn.update();
  faultBtn.update();

  switch (currentState) {
    case OFF: handleOffState(); break;
    case RUNNING: handleRunningState(); break;
    case FAULT: handleFaultState(); break;
  }

  handleBlink();
  delay(10);
}

// --------- Core Functions ---------
void setSystemOff() {
  currentState = OFF;
  digitalWrite(motorRelayPin, LOW);
  led.setColor(255, 0, 0);
  Serial.println("System Initialized: OFF state");
}

void handleOffState() {
  if (startBtn.startHold(holdDuration)) {
    buzzer.beep(1, 100, 100);
    Serial.println("Start button held 3 sec - Transition to RUNNING");
    currentState = RUNNING;
    digitalWrite(motorRelayPin, HIGH);
    led.setColor(0, 255, 0);
    startBlinkActive = false;
  } else {
    startBlinkActive = startBtn.isHolding();
    if (startBtn.wasReleasedEarly(holdDuration)) {
      Serial.println("Start button released early - Cancel Start");
    }
    if (!startBtn.isPressed()) led.setColor(255, 0, 0);
  }
}

void handleRunningState() {
  if (stopBtn.startHold(holdDuration)) {
    buzzer.beep(2, 100, 100);
    Serial.println("Stop button held 3 sec - Transition to OFF");
    setSystemOff();
    stopBlinkActive = false;
  } else {
    stopBlinkActive = stopBtn.isHolding();
    if (stopBtn.wasReleasedEarly(holdDuration)) {
      Serial.println("Stop button released early - Cancel Stop");
    }
    if (!stopBtn.isPressed()) led.setColor(0, 255, 0);
  }

  if (faultBtn.isPressed()) {
    buzzer.beep(3, 75, 75);
    Serial.println("Fault button pressed - Immediate FAULT");
    saveFaultToEEPROM();
    currentState = FAULT;
    activeBlinkInterval = fastBlinkInterval;
    lastBlinkTime = millis();
    ledState = false;
    faultClearing = false;
    digitalWrite(motorRelayPin, LOW);
    return;
  }
}

void handleFaultState() {
  if (faultBtn.startHold(faultClearDuration)) {
    buzzer.beep(2, 100, 100);
    Serial.println("Fault button held 5 sec - FAULT CLEARED");
    clearFaultInEEPROM();
    setSystemOff();
    faultClearing = false;
  } else {
    faultClearing = faultBtn.isHolding();
    if (faultBtn.wasReleasedEarly(faultClearDuration)) {
      Serial.println("Fault button released early - Reset canceled");
    }
    activeBlinkInterval = faultClearing ? slowBlinkInterval : fastBlinkInterval;
  }
}

void handleBlink() {
  unsigned long currentMillis = millis();
  bool shouldBlink = (currentState == FAULT) || (currentState == OFF && startBlinkActive) || (currentState == RUNNING && stopBlinkActive);
  if (!shouldBlink && !faultClearing) return;

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

void saveFaultToEEPROM() { EEPROM.write(stateEEPROMAddress, 1); }
void clearFaultInEEPROM() { EEPROM.write(stateEEPROMAddress, 0); }
