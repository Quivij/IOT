#include "PumpControl.h"

static bool s_isOn = false;
static bool s_timed = false;
static uint32_t s_start = 0;
static uint32_t s_duration = 0;

static inline void writePump(bool on) {
  if (PUMP_ACTIVE_LOW) {
    digitalWrite(PUMP_PIN, on ? LOW : HIGH);
  } else {
    digitalWrite(PUMP_PIN, on ? HIGH : LOW);
  }
  s_isOn = on;
}

void pumpSetup() {
  pinMode(PUMP_PIN, OUTPUT);

  // 🚨 Đảm bảo relay luôn tắt khi khởi động
  if (PUMP_ACTIVE_LOW) {
    digitalWrite(PUMP_PIN, HIGH);  
  } else {
    digitalWrite(PUMP_PIN, LOW);   
  }

  s_isOn = false;
  s_timed = false;
}

void pumpOn() {
  s_timed = false;
  writePump(true);
}

void pumpOff() {
  s_timed = false;
  writePump(false);
}

bool pumpIsOn() {
  return s_isOn;
}

void pumpRunFor(uint32_t duration_ms) {
  s_duration = duration_ms;
  s_start = millis();
  s_timed = true;
  writePump(true);
}

void pumpTick() {
  if (s_timed) {
    uint32_t now = millis();
    if ((uint32_t)(now - s_start) >= s_duration) {
      writePump(false);
      s_timed = false;
    }
  }
}
