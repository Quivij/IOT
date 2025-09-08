#ifndef ULTRASONIC_H
#define ULTRASONIC_H

#include <Arduino.h>

// Định nghĩa chân cảm biến
#define TRIG_PIN 12
#define ECHO_PIN 13

void ultrasonicSetup();      // Khởi tạo chân
long getDistanceCM();        // Đo khoảng cách cm

#endif
