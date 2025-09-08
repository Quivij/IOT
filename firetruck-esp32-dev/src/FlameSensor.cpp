#include "FlameSensor.h"

void flameSetup() {
  // Analog input (có thể bỏ, nhưng thêm cho rõ ràng)
  pinMode(FLAME1_AO, INPUT);
  pinMode(FLAME2_AO, INPUT);
}

// Trả về true nếu phát hiện lửa (AO < threshold)
bool isFlameDetected(int sensor, int threshold) {
  int value = readFlameAnalog(sensor);
  if (value < 0) return false; // nhập sai sensor

  // Debug giá trị để dễ điều chỉnh ngưỡng
  Serial.printf("🔥 FlameSensor %d analog = %d\n", sensor, value);

  return (value < threshold);
}

// Đọc giá trị analog từ cảm biến
int readFlameAnalog(int sensor) {
  if (sensor == 1) {
    return analogRead(FLAME1_AO);
  } else if (sensor == 2) {
    return analogRead(FLAME2_AO);
  }
  return -1; // nếu nhập sai sensor
}
