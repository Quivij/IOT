#ifndef MOTORCONTROL_H
#define MOTORCONTROL_H

#include <Arduino.h>

// Chân L298N
#define ENA 25
#define IN1 26
#define IN2 27
#define ENB 32
#define IN3 33






#define IN4 14

// PWM
const int PWM_CH_LEFT  = 0;
const int PWM_CH_RIGHT = 1;
const int PWM_FREQ     = 1000; 
const int PWM_RES_BIT  = 8;    

extern int speedValue;

void motorSetup();
void applySpeed();
void stopAll();
void forward();
void backward();
void left();
void right();

#endif
