#pragma once

#include <Arduino.h>
#include <EEPROM.h>
#include "Adafruit_NeoTrellis.h"

Adafruit_NeoTrellis trellis;

template <uint8_t menuCount>
class MenuHandler {
private:
    static uint8_t currentMenu;
    static uint8_t currentSetting;
    static uint8_t currentValue[menuCount];
    static uint8_t maxValue[menuCount];
    static uint8_t faceChoices;
    static bool menuActive;
    static bool isReady;
    static bool didBegin;

    static uint32_t Wheel(byte WheelPos);
    static TrellisCallback blink(keyEvent evt);
    static uint8_t ReadEEPROM(uint16_t index);
    static void WriteEEPROM(uint16_t index, uint8_t value);
    static void ResetI2CBus();

public:
    static void Update();
    static bool Initialize();
    static void SetDefaultValue(uint16_t menu, uint8_t value);
    static void SetInitialized();
    static void SetMenuMax(uint8_t menu, uint8_t maxValue);
    static uint8_t GetMenuValue(uint8_t menu);
    static uint8_t GetCurrentMenu();
};

#include "NeoTrellisMenuHandler.tpp"