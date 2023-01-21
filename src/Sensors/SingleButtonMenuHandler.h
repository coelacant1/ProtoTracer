#pragma once

#include <Arduino.h>
#include <EEPROM.h>
#include <IntervalTimer.h>

template<uint8_t menuCount>
class MenuHandler{
private:
    static IntervalTimer menuChangeTimer;
    static long previousMillisHold;
    static uint16_t holdingTime;
    static uint8_t currentMenu;
    static uint8_t currentValue[menuCount];
    static uint8_t maxValue[menuCount];
    static uint8_t pin;
    static bool holdingState;
    static bool previousState;

    static void UpdateState(){
        long currentTime = millis();
        bool pinState = digitalRead(pin);
        long timeOn = 0;
        
        if(pinState && !previousState){//pin not pressed, not triggered -> reset time
            previousMillisHold = currentTime;
        }
        else if (pinState && previousState){//pin not pressed, was triggered -> measure time
            timeOn = currentTime - previousMillisHold;

            previousState = false;
        }
        else if (!pinState){//pin is pressed,
            previousState = true;
        }
        
        if(timeOn > holdingTime && pinState){
            previousMillisHold = currentTime;

            WriteEEPROM(currentMenu, currentValue[currentMenu]);

            currentMenu += 1;
            if (currentMenu >= menuCount) currentMenu = 0;
        } else if(timeOn > 50 && pinState){
            previousMillisHold = currentTime;

            currentValue[currentMenu] += 1;
            if (currentValue[currentMenu] >= maxValue[currentMenu]) currentValue[currentMenu] = 0;
        }
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
    static void Begin(){
        menuChangeTimer.begin(UpdateState, 1000);
    }

    static bool Initialize(uint8_t pin, uint16_t holdingTime){//if true, eeprom needs set
        MenuHandler::holdingState = true;

        MenuHandler::previousState = false;

        pinMode(pin, INPUT_PULLUP);

        MenuHandler::pin = pin;
        MenuHandler::holdingTime = holdingTime;

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
IntervalTimer MenuHandler<menuCount>::menuChangeTimer;
template<uint8_t menuCount>
long MenuHandler<menuCount>::previousMillisHold;
template<uint8_t menuCount>
uint16_t MenuHandler<menuCount>::holdingTime;
template<uint8_t menuCount>
uint8_t MenuHandler<menuCount>::currentMenu;
template<uint8_t menuCount>
uint8_t MenuHandler<menuCount>::currentValue[];
template<uint8_t menuCount>
uint8_t MenuHandler<menuCount>::maxValue[menuCount];
template<uint8_t menuCount>
uint8_t MenuHandler<menuCount>::pin;
template<uint8_t menuCount>
bool MenuHandler<menuCount>::holdingState = true;
template<uint8_t menuCount>
bool MenuHandler<menuCount>::previousState = false;