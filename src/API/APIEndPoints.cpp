// src/ApiEndpoints.cpp
#include "ApiEndpoints.h"
#include <WiFi.h>
#include "Display.h"

extern Display display; // Declare display as extern

void setupApiEndpoints(AsyncWebServer &server)
{
    server.on("/wifi", HTTP_GET, [](AsyncWebServerRequest *request)
              {
        display.showWiFiStatus(WiFi.localIP().toString());
        Serial.println("wifi endpoint called");
        request->send(200, "text/plain", "Look at the screen !"); });

    server.on("/blank", HTTP_GET, [](AsyncWebServerRequest *request)
              {
        display.blank();
        Serial.println("blank endpoint called");
        request->send(200, "text/plain", "Screen is blank now"); });

    server.on("/message", HTTP_GET, [](AsyncWebServerRequest *request)
              {
        Serial.println("message endpoint called");
        if (request->hasParam("message")) {
            String message = request->getParam("message")->value();
            display.showMessage(message);
            request->send(200, "text/plain", "Message set to: " + message);
        } else {
            request->send(400, "text/plain", "Missing message parameter");
        } });
}
