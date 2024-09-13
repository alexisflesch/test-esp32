#ifndef DISPLAY_H
#define DISPLAY_H

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

class Display {
public:
    Display(int width, int height, int resetPin, int address);
    void begin();
    void showInitializing();
    void showWiFiStatus(const String& ip);
    void showMessage(const String& message);
    void drawWiFiIcon();
    void blank();
    void updateScreen(); // Updating both display and last activity time
    void checkForInactivity(); // Checking for inactivity

private:
    Adafruit_SSD1306 _oled;
    int _width;
    int _height;
    int _resetPin;
    int _address;
    unsigned long _lastActivityTime;
    const unsigned long _timeout = 15000; // Timeout in milliseconds
};

#endif // DISPLAY_H
