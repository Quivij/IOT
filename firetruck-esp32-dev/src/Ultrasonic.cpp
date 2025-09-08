#include "Ultrasonic.h"

void ultrasonicSetup() {
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  digitalWrite(TRIG_PIN, LOW);
}

long getDistanceCM() {
  // Gửi xung 10µs
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // Đo độ rộng xung Echo
  long duration = pulseIn(ECHO_PIN, HIGH, 30000); // timeout 30ms ~ 5m

  // Tính khoảng cách (cm)
  long distance = duration * 0.0343 / 2;

  return distance; // trả về -1 nếu timeout
}
