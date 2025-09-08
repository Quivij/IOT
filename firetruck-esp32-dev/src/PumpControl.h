#ifndef PUMP_CONTROL_H
#define PUMP_CONTROL_H

#include <Arduino.h>

// Chân điều khiển relay bơm
#ifndef PUMP_PIN
#define PUMP_PIN 23
#endif

// Nếu relay là loại LOW = bật thì để true, nếu HIGH = bật thì để false
#ifndef PUMP_ACTIVE_LOW
#define PUMP_ACTIVE_LOW true
#endif

void pumpSetup();          // gọi trong setup()
void pumpOn();             // bật bơm
void pumpOff();            // tắt bơm
bool pumpIsOn();           // kiểm tra trạng thái

// Bật bơm trong 1 khoảng thời gian (ms) không chặn chương trình
void pumpRunFor(uint32_t duration_ms);
void pumpTick();           // gọi trong loop()

#endif
