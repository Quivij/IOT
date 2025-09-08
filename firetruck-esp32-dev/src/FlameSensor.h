#ifndef FLAMESENSOR_H
#define FLAMESENSOR_H

#include <Arduino.h>

// Định nghĩa chân cảm biến lửa (AO = Analog Output)
#define FLAME1_AO 34   // Cảm biến lửa bên trái
#define FLAME2_AO 35   // Cảm biến lửa bên phải
// ⚠️ Nếu muốn dùng GPIO36 thì đổi ở đây thành 36

// Khởi tạo cảm biến lửa
void flameSetup();

// Kiểm tra có lửa hay không (dựa trên ngưỡng analog)
bool isFlameDetected(int sensor, int threshold = 2000);

// Đọc giá trị analog từ cảm biến
int readFlameAnalog(int sensor);

#endif
