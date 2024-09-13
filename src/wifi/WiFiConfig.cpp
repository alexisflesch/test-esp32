// WiFiConfig.cpp
#include <WiFi.h>
#include "WiFiConfig.h"
#include "Display.h"

extern Display display; // Declare display as extern

void connectToWiFi()
{
    Serial.print("Connecting to ");
    Serial.print(WIFI_SSID);
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

    int attempts = 0;
    int mod = 0;
    while (WiFi.status() != WL_CONNECTED && attempts < 30)
    {
        mod = attempts % 4;
        String message = "Connecting to WiFi";
        for (int i = 0; i < mod; i++)
        {
            message += ".";
        }
        display.showMessage(message);
        delay(500);
        Serial.print(".");
        attempts++;
    }

    if (WiFi.status() == WL_CONNECTED)
    {
        Serial.println("Connected!");
        Serial.print("IP Address: ");
        Serial.println(WiFi.localIP());
    }
    else
    {
        Serial.println("Failed to connect.");
    }
}
