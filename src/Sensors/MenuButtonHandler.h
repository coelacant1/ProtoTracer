#pragma once

#include <Arduino.h>
#include <EEPROM.h>
#include <IntervalTimer.h>

class MenuButtonHandler{
private:
    static const uint8_t toggleCount = 5;
    static IntervalTimer menuChangeTimer;
    static long previousMillisHold;
    static uint16_t holdingTime;
    static uint8_t currentMenu;
    static uint8_t currentValue[toggleCount];
    static uint8_t maxValue[toggleCount];
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
            
            //write current value to eeprom
            switch (currentMenu){
                case 1:
                    SetEEPOMBrightness(currentValue[currentMenu]);
                    break;
                case 2:
                    SetEEPOMMicrophone(currentValue[currentMenu]);
                    break;
                case 3:
                    SetEEPOMBoopSensor(currentValue[currentMenu]);
                    break;
                case 4:
                    SetEEPOMSpectrum(currentValue[currentMenu]);
                    break;
                default:
                    break;
            }

            currentMenu += 1;
            if (currentMenu >= toggleCount) currentMenu = 0;
        } else if(timeOn > 50 && pinState){
            previousMillisHold = currentTime;

            currentValue[currentMenu] += 1;
            if (currentValue[currentMenu] >= maxValue[currentMenu]) currentValue[currentMenu] = 0;
        }
    }

    //READ SETTINGS FROM EEPROM
    static uint8_t ReadEEPOMBrightness(){
        return EEPROM.read(0);
    }

    static uint8_t ReadEEPOMMicrophone(){
        return EEPROM.read(1);
    }
    
    static uint8_t ReadEEPOMBoopSensor(){
        return EEPROM.read(2);
    }
    
    static uint8_t ReadEEPOMSpectrum(){
        return EEPROM.read(3);
    }

    static uint8_t ReadEEPROMInitialize(){
        return EEPROM.read(50);
    }

    //WRITE SETTINGS TO EEPROM
    static void SetEEPOMBrightness(uint8_t value){
        EEPROM.write(0, value);
    }

    static void SetEEPOMMicrophone(uint8_t value){
        EEPROM.write(1, value);
    }
    
    static void SetEEPOMBoopSensor(uint8_t value){
        EEPROM.write(2, value);
    }
    
    static void SetEEPOMSpectrum(uint8_t value){
        EEPROM.write(3, value);
    }

    static void SetEEPOMInitialize(uint8_t value){
        EEPROM.write(50, value);
    }

public:
    static void Initialize(uint8_t pin, uint8_t maxFaces, uint16_t holdingTime) {
        pinMode(pin, INPUT_PULLUP);

        menuChangeTimer.begin(UpdateState, 1000);
        
        MenuButtonHandler::pin = pin;
        MenuButtonHandler::holdingTime = holdingTime;

        MenuButtonHandler::maxValue[0] = maxFaces;//number of faces to switch through
        MenuButtonHandler::maxValue[1] = 5;//number of brightness intervals
        MenuButtonHandler::maxValue[2] = 2;//microphone on or off
        MenuButtonHandler::maxValue[3] = 2;//boop sensor on or off
        MenuButtonHandler::maxValue[4] = 2;//spectrum analyzer mode

        if(ReadEEPROMInitialize() == 255){//will default to 255, if was previously set will equal 1
            SetEEPOMBrightness(1);
            SetEEPOMMicrophone(1);
            SetEEPOMBoopSensor(1);
            SetEEPOMSpectrum(1);
            SetEEPOMInitialize(1);
        }

        //initialize values from eeprom
        MenuButtonHandler::currentValue[0] = 0;//set to first face
        MenuButtonHandler::currentValue[1] = ReadEEPOMBrightness();//initialize brightness from eeprom
        MenuButtonHandler::currentValue[2] = ReadEEPOMMicrophone();//initialize microphone state from eeprom
        MenuButtonHandler::currentValue[3] = ReadEEPOMBoopSensor();//initialize boop sensor state from eeprom
        MenuButtonHandler::currentValue[4] = ReadEEPOMSpectrum();//initialize spectrum state from eeprom
    }

    static uint8_t GetBrightness(){
        return (currentValue[1] + 1) * 50;
    }

    static bool UseMicrophone(){
        return currentValue[2];
    }

    static bool UseBoopSensor(){
        return currentValue[3];
    }
    
    static bool MirrorSpectrumAnalyzer(){
        return currentValue[4];
    }

    static uint8_t GetFaceState(){
        return currentValue[0];
    }
};

const uint8_t MenuButtonHandler::toggleCount;
IntervalTimer MenuButtonHandler::menuChangeTimer;
long MenuButtonHandler::previousMillisHold;
uint16_t MenuButtonHandler::holdingTime;
uint8_t MenuButtonHandler::currentMenu;
uint8_t MenuButtonHandler::currentValue[toggleCount];
uint8_t MenuButtonHandler::maxValue[toggleCount];
uint8_t MenuButtonHandler::pin;
bool MenuButtonHandler::holdingState = true;

bool MenuButtonHandler::previousState = false;