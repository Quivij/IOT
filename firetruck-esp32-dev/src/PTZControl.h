#ifndef PTZCONTROL_H
#define PTZCONTROL_H

#include <Arduino.h>
#include <ESP32Servo.h>

// Chân servo
#define SERVO_PAN  16   // servo xoay ngang
#define SERVO_TILT 17   // servo xoay dọc

void ptzSetup();
void setPan(int angle);   // góc 0–180
void setTilt(int angle);  // góc 0–180

#endif
