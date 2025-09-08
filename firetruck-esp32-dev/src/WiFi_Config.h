#ifndef WIFI_CONFIG_H
#define WIFI_CONFIG_H

#include <WiFi.h>

// Cấu hình WiFi
extern const char* STA_SSID;
extern const char* STA_PASS;
extern const char* AP_SSID;
extern const char* AP_PASS;

// Khởi tạo WiFi Station (kết nối router), trả về true nếu OK
bool startWiFiSTA();

// Khởi tạo WiFi Access Point
void startWiFiAP();

#endif
