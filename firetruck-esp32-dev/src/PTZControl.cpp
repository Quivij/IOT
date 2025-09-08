#include "PTZControl.h"

Servo servoPan;
Servo servoTilt;

void ptzSetup() {
  servoPan.attach(SERVO_PAN);
  servoTilt.attach(SERVO_TILT);

  // Về vị trí trung tâm
  setPan(90);
  setTilt(90);
}

void setPan(int angle) {
  angle = constrain(angle, 0, 180);
  servoPan.write(angle);
}

void setTilt(int angle) {
  angle = constrain(angle, 0, 180);
  servoTilt.write(angle);
}
