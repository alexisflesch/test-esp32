// Icons : https://xod.io/libs/xod/graphics/

#include "Display.h"
#include <Wire.h>

// Constructor to initialize display parameters
Display::Display(int width, int height, int resetPin, int address)
    : _oled(width, height, &Wire, resetPin), _width(width), _height(height), _resetPin(resetPin), _address(address) {}

// Initialize the display
void Display::begin()
{
    if (!_oled.begin(SSD1306_SWITCHCAPVCC, _address))
    {
        Serial.println(F("SSD1306 allocation failed"));
        for (;;)
            ; // Infinite loop to halt execution if display fails to initialize
    }
    _oled.clearDisplay();      // Clear the display buffer
    _oled.setTextSize(1);      // Set text size
    _oled.setTextColor(WHITE); // Set text color
}

// To keep track of the last activity time
void Display::updateScreen()
{
    _oled.display();
    _lastActivityTime = millis(); // Update last activity time
}

const uint8_t iconWifiFourBar[] PROGMEM = {
    0b00000000, 0b00000000, //
    0b00000111, 0b11100000, //      ######
    0b00011111, 0b11111000, //    ##########
    0b00111111, 0b11111100, //   ############
    0b01110000, 0b00001110, //  ###        ###
    0b01100111, 0b11100110, //  ##  ######  ##
    0b00001111, 0b11110000, //     ########
    0b00011000, 0b00011000, //    ##      ##
    0b00000011, 0b11000000, //       ####
    0b00000111, 0b11100000, //      ######
    0b00000100, 0b00100000, //      #    #
    0b00000001, 0b10000000, //        ##
    0b00000001, 0b10000000, //        ##
    0b00000000, 0b00000000, //
    0b00000000, 0b00000000, //
    0b00000000, 0b00000000, //
};

const uint8_t warning[] PROGMEM = {
    0b00000000, 0b10000000, //         #
    0b00000001, 0b11000000, //        ###
    0b00000001, 0b11000000, //        ###
    0b00000011, 0b11100000, //       #####
    0b00000011, 0b01100000, //       ## ##
    0b00000111, 0b01110000, //      ### ###
    0b00000110, 0b00110000, //      ##   ##
    0b00001110, 0b10111000, //     ### # ###
    0b00001100, 0b10011000, //     ##  #  ##
    0b00011100, 0b10011100, //    ###  #  ###
    0b00011000, 0b10001100, //    ##   #   ##
    0b00111000, 0b00001110, //   ###       ###
    0b00110000, 0b10000110, //   ##    #    ##
    0b01111111, 0b11111111, //  ###############
    0b01111111, 0b11111111, //  ###############
    0b00000000, 0b00000000, //
};

const uint8_t heart[] PROGMEM = {
    0b00000000, 0b00000000, //
    0b00000000, 0b00000000, //
    0b00111100, 0b01111000, //   ####   ####
    0b01111110, 0b11111100, //  ###### ######
    0b11111111, 0b11111110, // ###############
    0b11111111, 0b11111110, // ###############
    0b11111111, 0b11111110, // ###############
    0b11111111, 0b11111110, // ###############
    0b01111111, 0b11111100, //  #############
    0b01111111, 0b11111100, //  #############
    0b00111111, 0b11111000, //   ###########
    0b00011111, 0b11110000, //    #########
    0b00001111, 0b11100000, //     #######
    0b00000111, 0b11000000, //      #####
    0b00000011, 0b10000000, //       ###
    0b00000001, 0b00000000, //    	  #

};

// Draw the WiFi icon on the display
void Display::drawWiFiIcon()
{
    _oled.drawBitmap(0, 0, iconWifiFourBar, 16, 16, WHITE);
}

// Draw wifi icon along with ip address
void Display::showWiFiStatus(const String &ip)
{
    _oled.clearDisplay();
    drawWiFiIcon();
    _oled.setTextSize(1);
    _oled.setCursor(25, 4);
    _oled.println(ip);
    updateScreen();
}

// Blank the display
void Display::blank()
{
    _oled.clearDisplay();
    _oled.display();
}

// Show an initializing message on the display
void Display::showInitializing()
{
    showMessage("Initializing...");
}

// Show a custom message on the display
void Display::showMessage(const String &message)
{
    Serial.println(message); // Print the message to the serial monitor
    _oled.clearDisplay();    // Clear the display
    _oled.setCursor(0, 10);  // Set cursor position
    _oled.println(message);  // Display the message
    updateScreen();          // Update the display
}

// Turn off screen after inactivity
void Display::checkForInactivity()
{
    // Turn off the display after timeout
    if (millis() - _lastActivityTime > _timeout)
    {
        _oled.ssd1306_command(SSD1306_DISPLAYOFF);
    }
    else
    {
        _oled.ssd1306_command(SSD1306_DISPLAYON);
    }
}