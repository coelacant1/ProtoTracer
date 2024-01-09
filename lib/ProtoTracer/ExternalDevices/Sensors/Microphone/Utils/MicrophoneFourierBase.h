#pragma once

#include <Arduino.h>
#include "..\..\..\..\Utils\Filter\DerivativeFilter.h"
#include "..\..\..\..\Utils\Filter\FFTFilter.h"
#include "..\..\..\..\Utils\Time\TimeStep.h"
#include "..\..\..\..\Utils\Signals\FFT.h"

class MicrophoneFourierBase {
protected:
    static const uint16_t FFTSize = 256;
    static const uint16_t OutputBins = 128;
    static uint16_t sampleRate;
    static uint8_t pin;
    static float minDB;
    static float maxDB;
    static float threshold;
    static float currentValue;
    static bool isInitialized;
    static DerivativeFilter peakFilterRate;

    static float inputSamp[FFTSize * 2];
    static float inputStorage[FFTSize];
    static float outputMagn[FFTSize];
    static float outputData[OutputBins];
    static float outputDataFilt[OutputBins];
    static FFTFilter fftFilters[OutputBins];

    static FFT<FFTSize> fft;

public:
    static float AverageMagnitude(uint16_t binL, uint16_t binH);
    static bool IsInitialized();
    static float GetSampleRate();
    static float* GetSamples();
    static float* GetFourier();
    static float* GetFourierFiltered();
    static float GetCurrentMagnitude();
};

