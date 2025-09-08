#include <Arduino.h>
#include <ESPmDNS.h>

#include "WiFi_Config.h"
#include "MotorControl.h"
#include "WebHandlers.h"
#include "FlameSensor.h"
#include "PumpControl.h"
#include "Buzzer.h"
#include "Ultrasonic.h"
#include "PTZControl.h"   // Thêm PTZ control

const char* MDNS_NAME = "firetruck";

// --- Biến trạng thái ---
unsigned long lastPumpTime = 0;
bool pumping = false;

void setup() {
  Serial.begin(115200);

  // 🚗 Khởi tạo phần cứng
  motorSetup();
  flameSetup();
  pumpSetup();
  buzzerSetup();
  ultrasonicSetup();
  ptzSetup();   // ⚙️ Khởi tạo servo pan/tilt

  // 📶 Kết nối WiFi
  bool sta = startWiFiSTA();
  if (sta) {
    Serial.print("✅ WiFi STA OK, IP: ");
    Serial.println(WiFi.localIP());
    if (MDNS.begin(MDNS_NAME)) {
      MDNS.addService("http", "tcp", 80);
      Serial.printf("🌐 mDNS: http://%s.local/\n", MDNS_NAME);
    }
  } else {
    startWiFiAP();
    Serial.printf("📡 WiFi AP: %s  IP: %s\n", AP_SSID, WiFi.softAPIP().toString().c_str());
  }

  // 🌍 Web routes
  server.on("/", handleRoot);
  server.on("/f", handleForward);
  server.on("/b", handleBackward);
  server.on("/l", handleLeft);
  server.on("/r", handleRight);
  server.on("/s", handleStop);
  server.on("/speed", handleSpeed);

  // 📌 Web API điều khiển PTZ
  server.on("/servo/left", []() {
    setPan(70);  // quay trái
    server.send(200, "text/plain", "Servo Pan Left");
  });
  server.on("/servo/right", []() {
    setPan(110); // quay phải
    server.send(200, "text/plain", "Servo Pan Right");
  });
  server.on("/servo/up", []() {
    setTilt(110); // ngẩng lên
    server.send(200, "text/plain", "Servo Tilt Up");
  });
  server.on("/servo/down", []() {
    setTilt(70);  // hạ xuống
    server.send(200, "text/plain", "Servo Tilt Down");
  });

  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("🚀 Web server started!");
}

void loop() {
  server.handleClient();

  // 🚧 Kiểm tra vật cản
  long distance = getDistanceCM();
  if (distance > 0 && distance < 20) {
    Serial.printf("🚧 Vật cản! Khoảng cách: %ld cm\n", distance);
    stopAll();
    buzzerOn();
    delay(200);
    buzzerOff();
  }

  // 🔥 Kiểm tra lửa từ 2 cảm biến
  int val1 = readFlameAnalog(1);
  int val2 = readFlameAnalog(2);
  bool flame1 = (val1 < 2000);
  bool flame2 = (val2 < 2000);

  Serial.printf("Flame1=%d  Flame2=%d\n", val1, val2);

  if (flame1 || flame2) {
    Serial.println("🔥 PHÁT HIỆN LỬA!");
    stopAll();
    buzzerOn();

    if (!pumping) {
      pumpOn();
      pumping = true;
      lastPumpTime = millis();
    }

    // 🚿 Điều khiển PTZ theo cảm biến
    if (flame1) { 
      setPan(70); 
      setTilt(100);
    }
    if (flame2) { 
      setPan(110); 
      setTilt(100);
    }
  } 
  else {
    buzzerOff();
    setPan(90);
    setTilt(90);
  }

  // ⏱️ Tự tắt bơm sau 3 giây
  if (pumping && millis() - lastPumpTime > 3000) {
    pumpOff();
    pumping = false;
  }
}
