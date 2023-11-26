#pragma once

#include <Arduino.h>

class ButtonHandler {
private:
    static long previousMillisISR;
    static long previousMillisHold;
    static uint16_t holdingToggle;
    static uint8_t currentValue;
    static uint8_t maxValue;
    static uint8_t pin;
    static bool holdingState;

    static void isr();

public:
    static void Initialize(uint8_t pin, uint8_t maxValue, uint16_t holdingToggle);
    static bool GetHoldingState();
    static uint8_t GetValue();
};

