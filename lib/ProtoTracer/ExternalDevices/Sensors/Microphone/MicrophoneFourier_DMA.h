#pragma once

#define ARM_MATH_CM4

#include <Arduino.h>
#include <ADC.h>
#include <DMAChannel.h>
#include <AnalogBufferDMA.h>
#include "Utils\MicrophoneFourierBase.h"

class MicrophoneFourier : public MicrophoneFourierBase {
private:
    static const int16_t Hanning256[];

    static bool microphoneGain_50db;
    static uint8_t gain_pin;

    static void window_raw_fft_data(void* buffer, const void* window);
    static void SamplerCallback(AnalogBufferDMA* dma_buffer_instance, int8_t adc_num);

public:
    static void Initialize(uint8_t pin, uint32_t sampleRate, float minDB, float maxDB);
    static void Initialize(uint8_t pin, uint8_t gain_pin, uint32_t sampleRate, float minDB, float maxDB, bool microphoneGain_50db);

    static void setSamplingRate(uint32_t sampleRate);
    static void setMicGain(bool is50db);
    static void UpdateDMA();
};
