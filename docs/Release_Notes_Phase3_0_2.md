# 📦 Release: v3.0.2 - Motor Control Integration (Phase 3)

### Summary
- Phase 3 brings the first integration of hardware output control: a motor relay is now tied directly to the RUNNING and OFF states.
- The motor no longer spins immediately at boot — correct relay logic is applied based on state transitions.

### Changes
✅ Added `motorRelayPin` (D12) setup and management  
✅ Turn ON motor relay when system transitions to RUNNING  
✅ Turn OFF motor relay during OFF or FAULT transitions  
✅ Re-synced all helper functions (readButtons, handleBlink, etc.) to working state  
✅ Improved and cleaned up code comments for OpenPLC compatibility (future-proofing)  
✅ Maintained full EEPROM fault recovery functionality

### Compatibility
- Designed for Arduino Uno
- Wiring layout and I/O mapping is compatible with OpenPLC standard pins
- No external libraries added beyond Adafruit NeoPixel

---
