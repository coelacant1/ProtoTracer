#pragma once

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

Adafruit_SSD1306 display(128, 64, &Wire, -1);

class SSD1306{
public:
    SSD1306(){}

    void Initialize(){
        if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C )) {
            Serial.println(F("SSD1306 allocation failed"));
        }

        display.setRotation(2);
    }

    void Display(){
        display.clearDisplay();

        display.setTextSize(1);
        display.setTextColor(SSD1306_WHITE);
        display.setTextWrap(false);
        display.setCursor(10, 0);
        display.println(F("Reading EEPROM..."));
        display.setCursor(10, 10);
        display.println(F("Configuring..."));
        display.setCursor(10, 20);
        display.println(F("Ready for user..."));
        display.setCursor(10, 30);
        display.println(F("Waiting for input..."));
        display.display();

        display.startscrollright(0x00, 0x0F);
    }
};
