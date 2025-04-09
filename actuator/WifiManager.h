#pragma once
#include <WiFi.h>
class WifiManager
{
private:
    const char *ssid;
    const char *password;

public:
    WifiManager(const char *ssid, const char *password)
        : ssid(ssid), password(password) {}
    void connect()
    {
        WiFi.begin(ssid, password);
        Serial.print("Conectando a WiFi...");
        while (WiFi.status() != WL_CONNECTED)
        {
            delay(500);
            Serial.print(".");
            // builtinLed.setState(Led::STATE_OFF);
        }
        Serial.println("Conectado");
        // builtinLed.setState(Led::STATE_ON);
    }
};