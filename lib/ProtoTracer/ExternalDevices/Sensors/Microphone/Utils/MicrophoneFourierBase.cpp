#include "MicrophoneFourierBase.h"

const uint16_t MicrophoneFourierBase::FFTSize;
const uint16_t MicrophoneFourierBase::OutputBins;
uint16_t MicrophoneFourierBase::sampleRate = 8000;
uint8_t MicrophoneFourierBase::pin = 0;
float MicrophoneFourierBase::minDB = 50.0f;
float MicrophoneFourierBase::maxDB = 120.0f;
float MicrophoneFourierBase::threshold = 400.0f;
float MicrophoneFourierBase::currentValue = 0.0f;
bool MicrophoneFourierBase::isInitialized = false;
DerivativeFilter MicrophoneFourierBase::peakFilterRate;

float MicrophoneFourierBase::inputSamp[];
float MicrophoneFourierBase::inputStorage[];
float MicrophoneFourierBase::outputMagn[];
float MicrophoneFourierBase::outputData[];
float MicrophoneFourierBase::outputDataFilt[];
FFTFilter MicrophoneFourierBase::fftFilters[];

FFT<MicrophoneFourierBase::FFTSize> MicrophoneFourierBase::fft;

float MicrophoneFourierBase::AverageMagnitude(uint16_t binL, uint16_t binH) {
    float average = 0.0f;

    for (uint16_t i = 1; i < FFTSize / 2; i++) {
        if (i >= binL && i <= binH)
            average += outputMagn[i];
    }

    return average / float(binH - binL + 1);
}

bool MicrophoneFourierBase::IsInitialized() {
    return isInitialized;
}

float MicrophoneFourierBase::GetSampleRate() {
    return sampleRate;
}

float* MicrophoneFourierBase::GetSamples() {
    return inputStorage;
}

float* MicrophoneFourierBase::GetFourier() {
    return outputData;
}

float* MicrophoneFourierBase::GetFourierFiltered() {
    return outputDataFilt;
}

float MicrophoneFourierBase::GetCurrentMagnitude() {
    return threshold;
}