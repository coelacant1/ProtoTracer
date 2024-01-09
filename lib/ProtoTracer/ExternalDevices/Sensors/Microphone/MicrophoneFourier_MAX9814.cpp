#include "MicrophoneFourier_MAX9814.h"

IntervalTimer MicrophoneFourier::sampleTimer;
TimeStep MicrophoneFourier::timeStep = TimeStep(60);

uint16_t MicrophoneFourier::frequencyBins[];

uint16_t MicrophoneFourier::samples = 0;
uint16_t MicrophoneFourier::samplesStorage = 0;
float MicrophoneFourier::refreshRate = 60.0f;
bool MicrophoneFourier::samplesReady = false;


void MicrophoneFourier::SamplerCallback() {
    int inputSample = analogRead(pin);

    inputSamp[samples++] = (float)inputSample;
    inputSamp[samples++] = 0.0f;

    inputStorage[samplesStorage++] = inputSample;

    if (samples >= FFTSize * 2) {
        sampleTimer.end();
        samplesReady = true;
    }
}

void MicrophoneFourier::StartSampler() {
    samplesReady = false;
    samples = 0;
    samplesStorage = 0;
    sampleTimer.begin(SamplerCallback, 1000000 / sampleRate);
}

void MicrophoneFourier::Initialize(uint8_t pin, uint16_t sampleRate, float minDB, float maxDB, float refreshRate) {
    MicrophoneFourier::minDB = minDB;
    MicrophoneFourier::maxDB = maxDB;
    MicrophoneFourier::pin = pin;
    MicrophoneFourier::refreshRate = refreshRate;

    pinMode(pin, INPUT);
    analogReadResolution(12);

    MicrophoneFourier::sampleRate = sampleRate;
    MicrophoneFourier::samples = 0;
    MicrophoneFourier::samplesReady = false;

    float windowRange = float(sampleRate) / 2.0f / float(OutputBins);

    timeStep.SetFrequency(refreshRate);

    for (uint8_t i = 0; i < OutputBins; i++) {
        float frequency = (float(i) * windowRange);
        frequencyBins[i] = uint16_t(frequency / float(sampleRate / FFTSize));
    }

    StartSampler();
    isInitialized = true;
}

void MicrophoneFourier::Reset() {
    for (int i = 0; i < FFTSize * 2; i++) {
        inputSamp[i] = 0.0f;
    }
}

void MicrophoneFourier::Update() {
    if (!samplesReady && timeStep.IsReady()) return;

    fft.Radix2FFT(inputSamp);
    fft.ComplexMagnitude(inputSamp, outputMagn);

    float averageMagnitude = 0.0f;

    for (uint8_t i = 0; i < OutputBins - 1; i++) {
        float intensity = 20.0f * log10f(AverageMagnitude(i, i + 1));

        intensity = map(intensity, minDB, maxDB, 0.0f, 1.0f);

        outputData[i] = intensity;
        outputDataFilt[i] = fftFilters[i].Filter(intensity);
        if (i % 12 == 0) averageMagnitude = peakFilterRate.Filter(inputStorage[i] / 4096.0f);
    }

    averageMagnitude *= 10.0f;
    threshold = powf(averageMagnitude, 2.0f);
    threshold = threshold > 0.2f ? (threshold * 5.0f > 1.0f ? 1.0f : threshold * 5.0f) : 0.0f;

    Reset();
    StartSampler();
}
