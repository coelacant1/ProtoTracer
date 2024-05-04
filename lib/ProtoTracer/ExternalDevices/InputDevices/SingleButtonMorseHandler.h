#pragma once

#include <Arduino.h>
#include <EEPROM.h>

template <uint8_t menuCount>
class MenuHandler {
private:
    static bool previousState; 
    static long previousMillis;
    static uint8_t inputCount;
    static uint16_t inputStream[4];
    static uint8_t currentMenu;
    static uint8_t currentValue[menuCount];
    static uint8_t maxValue[menuCount];
    static uint8_t pin;

    static uint8_t ReadEEPROM(uint16_t index);
    static void WriteEEPROM(uint16_t index, uint8_t value);

public:
    static void Begin();
    static bool Initialize(uint8_t pin, uint16_t holdingTime);
    static void SetDefaultValue(uint16_t menu, uint8_t value);
    static void SetInitialized();
    static void SetMenuMax(uint8_t menu, uint8_t maxValue);
    static void Update();
    static uint8_t GetMenuValue(uint8_t menu);
    static uint8_t GetCurrentMenu();
};

#include "SingleButtonMorseHandler.tpp"