#ifndef BUZZER_H
#define BUZZER_H

#include <Arduino.h>

// Định nghĩa chân còi
#define BUZZER_PIN 4

// Khởi tạo chân còi
void buzzerSetup();

// Bật còi
void buzzerOn();

// Tắt còi
void buzzerOff();

#endif
