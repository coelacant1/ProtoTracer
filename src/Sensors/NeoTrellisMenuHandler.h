#pragma once

#include <Arduino.h>
#include <EEPROM.h>
#include "Adafruit_NeoTrellis.h"

Adafruit_NeoTrellis trellis;

template<uint8_t menuCount>
class MenuHandler{
private:
    static uint8_t currentMenu;
    static uint8_t currentSetting;
    static uint8_t currentValue[menuCount];
    static uint8_t maxValue[menuCount];
    static uint8_t faceChoices;
    static bool menuActive;
    static bool isReady;

    static uint32_t Wheel(byte WheelPos){
        WheelPos = 255 - WheelPos;
        if(WheelPos < 85){
            return trellis.pixels.Color(255 - WheelPos * 3, 0, WheelPos * 3);
        }
        else if(WheelPos < 170){
            WheelPos -= 85;
            return trellis.pixels.Color(0, WheelPos * 3, 255 - WheelPos * 3);
        }
        else {
            WheelPos -= 170;
            return trellis.pixels.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
        }
    }

    static TrellisCallback blink(keyEvent evt){
        if (evt.bit.EDGE == SEESAW_KEYPAD_EDGE_RISING) {
            trellis.pixels.setPixelColor(evt.bit.NUM, Wheel(map(uint16_t(evt.bit.NUM), uint16_t(0), trellis.pixels.numPixels(), uint16_t(0), uint16_t(255))));
            if (evt.bit.NUM < 8){//Set face on current page
                currentMenu = 0;
                currentValue[0] = evt.bit.NUM + 8 * faceChoices;
            }
            else if(evt.bit.NUM >= 8 && evt.bit.NUM < 12){//Set face page
                currentMenu = 0;
                faceChoices = evt.bit.NUM - 8;
            }
            else if(evt.bit.NUM == 12){
                menuActive = !menuActive;

                if(menuActive){
                    currentSetting = currentSetting == 0 ? 1 : currentSetting;
                    currentMenu = currentSetting;
                }
                else{
                    WriteEEPROM(currentMenu, currentValue[currentSetting]);
                    
                    currentMenu = 0;
                }
            }
            else if(evt.bit.NUM == 13){//Change current menu forward
                WriteEEPROM(currentMenu, currentValue[currentSetting]);

                currentSetting = currentSetting + 1 > menuCount ? menuCount : currentSetting + 1;
                currentMenu = currentSetting;
            }
            else if(evt.bit.NUM == 14){//Change current menu backward
                WriteEEPROM(currentMenu, currentValue[currentSetting]);

                currentSetting = currentSetting - 1 == 0 ? 1 : currentSetting - 1;
                currentMenu = currentSetting;
            }
            else if(evt.bit.NUM == 15){
                currentValue[currentSetting] += 1;
                if (currentValue[currentSetting] >= maxValue[currentSetting]) currentValue[currentSetting] = 0;
            }
        } else if (evt.bit.EDGE == SEESAW_KEYPAD_EDGE_FALLING) {
            trellis.pixels.setPixelColor(evt.bit.NUM, 0);
        }

        trellis.pixels.show();
        
        return 0;
    }

    //READ SETTINGS FROM EEPROM
    static uint8_t ReadEEPROM(uint16_t index){
        return EEPROM.read(index);
    }

    //WRITE SETTINGS TO EEPROM
    static void WriteEEPROM(uint16_t index, uint8_t value){
        EEPROM.write(index, value);
    }

public:
    static void Update(){
        if(isReady){
            trellis.read();
        }
    }

    static bool Initialize(){//if true, eeprom needs set
        Wire.setClock(100000);

        if (!trellis.begin()) {
            Serial.println("Could not start Trellis, check wiring?");
        }
        else {
            //activate all keys and set callbacks
            for(int i=0; i<NEO_TRELLIS_NUM_KEYS; i++){
                trellis.activateKey(i, SEESAW_KEYPAD_EDGE_RISING);
                trellis.activateKey(i, SEESAW_KEYPAD_EDGE_FALLING);
                trellis.registerCallback(i, blink);
            }

            isReady = true;

            Serial.println("NeoPixel Trellis started");
        }

        for (uint8_t i = 0; i < menuCount; i++){
            currentValue[i] = ReadEEPROM(i);
        }

        return ReadEEPROM(menuCount + 1) != 255;
    }

    static void SetDefaultValue(uint16_t menu, uint8_t value){
        if(menu >= menuCount) return;

        currentValue[menu] = value;

        WriteEEPROM(menu, value);
    }

    static void SetInitialized(){
        WriteEEPROM(menuCount + 1, 0);
    }

    static void SetMenuMax(uint8_t menu, uint8_t maxValue){
        if(menu >= menuCount) return;

        MenuHandler::maxValue[menu] = maxValue;
    }

    static uint8_t GetMenuValue(uint8_t menu){
        return currentValue[menu];
    }
    
    static uint8_t GetCurrentMenu(){
        return currentMenu;
    }
    
};

template<uint8_t menuCount>
uint8_t MenuHandler<menuCount>::currentMenu;
template<uint8_t menuCount>
uint8_t MenuHandler<menuCount>::currentSetting = 0;
template<uint8_t menuCount>
uint8_t MenuHandler<menuCount>::currentValue[];
template<uint8_t menuCount>
uint8_t MenuHandler<menuCount>::maxValue[menuCount];
template<uint8_t menuCount>
uint8_t MenuHandler<menuCount>::faceChoices = 0;
template<uint8_t menuCount>
bool MenuHandler<menuCount>::menuActive = false;
template<uint8_t menuCount>
bool MenuHandler<menuCount>::isReady = false;
