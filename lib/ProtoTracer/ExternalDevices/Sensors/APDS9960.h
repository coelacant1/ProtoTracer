#pragma once

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_APDS9960.h>
#include "../../Utils/Filter/MinFilter.h"
#include "../../Utils/Time/TimeStep.h"

class APDS9960 {
private:
    static Adafruit_APDS9960 apds;
    static uint16_t proximity;
    static uint16_t threshold;
    static MinFilter<10> minF;
    static TimeStep timeStep;
    static float minimum;
    static bool didBegin;
    static bool isBright;
    static bool isProx;

public:
    static bool Initialize(uint8_t threshold);
    static bool isBooped();
    static void ResetI2CBus();
    static uint8_t GetValue();
    static uint16_t GetBrightness();
};
