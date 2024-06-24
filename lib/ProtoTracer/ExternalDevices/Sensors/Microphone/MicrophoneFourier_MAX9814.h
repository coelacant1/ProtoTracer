#pragma once

#include <Arduino.h>
#include "../../../Utils/Filter/DerivativeFilter.h"
#include "../../../Utils/Filter/FFTFilter.h"
#include "../../../Utils/Time/TimeStep.h"
#include "Utils/MicrophoneFourierBase.h"

class MicrophoneFourier : public MicrophoneFourierBase {
private:
    static IntervalTimer sampleTimer;
    static TimeStep timeStep;

    static uint16_t samples;
    static uint16_t samplesStorage;
    static float refreshRate;
    static bool samplesReady;

    static uint16_t frequencyBins[OutputBins];

    static void SamplerCallback();
    static void StartSampler();

public:
    static void Initialize(uint8_t pin, uint16_t sampleRate, float minDB, float maxDB, float refreshRate = 60.0f);
    static void Reset();
    static void Update();
};
