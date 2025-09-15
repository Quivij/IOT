#include "WiFi_Config.h"
#include"Env.cpp"

const char* STA_SSID = wifi;
const char* STA_PASS = pwd;
const char* AP_SSID  = "FIRETRUCK_AP";
const char* AP_PASS  = "12345678";

bool startWiFiSTA() {
    WiFi.mode(WIFI_STA);
    WiFi.begin(STA_SSID, STA_PASS);
    unsigned long start = millis();
    while (WiFi.status() != WL_CONNECTED && millis() - start < 8000) {
        delay(200);
    }
    return WiFi.status() == WL_CONNECTED;
}

void startWiFiAP() {
    WiFi.mode(WIFI_AP);
    WiFi.softAP(AP_SSID, AP_PASS);
}
