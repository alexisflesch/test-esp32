# Home Automation with an ESP32

## Description

This is a work in progress. It will do two things:
- Send IR signals when a 433Mhz button is pressed
- Send IR signals when its API is called

Right now it only listen for API calls and updates a small OLED display.


## Licence
MIT except for the icons (see src/display/Display.cpp).

## Installation
If you want to give it a try, you will have to:
- Rename src/wifi/WiFiConfig-example.h to src/wifi/WiFiConfig.h and fill in your WiFi credentials.
- Plug your OLED screen to the ESP32 using the usual pins
