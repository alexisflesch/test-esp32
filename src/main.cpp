#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include "wifi/WiFiConfig.h"
#include "display/Display.h"
#include "API/APIEndPoints.h"

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32
#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3C

// Create an AsyncWebServer object
AsyncWebServer server(80);

// Create an instance of the display
Display display(SCREEN_WIDTH, SCREEN_HEIGHT, OLED_RESET, SCREEN_ADDRESS);

void setup()
{
    // Initialize serial communication
    Serial.begin(115200);

    // Initialize the display
    display.begin();

    // Connect to Wi-Fi
    connectToWiFi();

    // Display the IP address
    display.showWiFiStatus(WiFi.localIP().toString());

    // Set up API endpoints
    setupApiEndpoints(server);

    // Start the server
    server.begin();
}

void loop()
{
    // Check for inactivity and blank the screen if necessary
    display.checkForInactivity();
}
