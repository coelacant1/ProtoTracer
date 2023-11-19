//Configured for 60dB gain

#define ARM_MATH_CM4

#include <Arduino.h>
#include <arm_math.h>
#include <IntervalTimer.h>
#include "..\..\..\Utils\Math\Mathematics.h"
#include "..\..\..\Utils\Filter\DerivativeFilter.h"
#include "..\..\..\Utils\Filter\FFTFilter.h"
#include "..\..\..\Utils\Filter\PeakDetection.h"
#include "..\..\..\Utils\Time\TimeStep.h"

class MicrophoneFourier{
private:
    static IntervalTimer sampleTimer;
    static TimeStep timeStep;

    static const uint16_t FFTSize = 256;
    static const uint8_t OutputBins = 128;
    static uint16_t sampleRate;
    static uint16_t samples;
    static uint16_t samplesStorage;
    static uint8_t pin;
    static float minDB;
    static float maxDB;
    static float threshold;
    static float currentValue;
    static float refreshRate;
    static bool samplesReady;
    static bool isInitialized;
    static DerivativeFilter peakFilterRate;

    static uint16_t frequencyBins[OutputBins];
    static float inputSamp[FFTSize * 2];
    static float inputStorage[FFTSize];
    static float outputMagn[FFTSize];
    static float outputData[OutputBins];
    static float outputDataFilt[OutputBins];
    static FFTFilter fftFilters[OutputBins];
    
    static arm_cfft_radix4_instance_f32 RadixFFT;

    static float AverageMagnitude(uint16_t binL, uint16_t binH){
        float average = 0.0f;

        for (uint16_t i = 1; i < FFTSize / 2; i++){
            if (i >= binL && i <= binH) average += outputMagn[i];
        }

        return average / float(binH - binL + 1);
    }

    static void SamplerCallback(){
        int inputSample = analogRead(pin);

        inputSamp[samples++] = (float)inputSample;
        inputSamp[samples++] = 0.0f;

        inputStorage[samplesStorage++] = inputSample;

        if(samples >= FFTSize * 2){
            sampleTimer.end();
            samplesReady = true;
        }
    }

    static void StartSampler(){
        samplesReady = false;
        samples = 0;
        samplesStorage = 0;
        sampleTimer.begin(SamplerCallback, 1000000 / sampleRate);
    }

public:
    static void Initialize(uint8_t pin, uint16_t sampleRate, float minDB, float maxDB, float refreshRate = 60.0f){
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

        for (uint8_t i = 0; i < OutputBins; i++){
            float frequency = (float(i) * windowRange);
            frequencyBins[i] = uint16_t(frequency / float(sampleRate / FFTSize));
        }

        StartSampler();
        isInitialized = true;
    }

    static bool IsInitialized(){
        return isInitialized;
    }

    static float GetSampleRate(){
        return sampleRate;
    }

    static float* GetSamples(){
        return inputStorage;
    }

    static float* GetFourier(){
        return outputData;
    }

    static float* GetFourierFiltered(){
        return outputDataFilt;
    }

    static float GetCurrentMagnitude(){
        return threshold;
    }

    static void Reset(){
        for(int i = 0; i < FFTSize * 2; i++){
            inputSamp[i] = 0.0f;
        }
    }
    
    static void Update(){
        if(!samplesReady && timeStep.IsReady()) return;

        arm_cfft_radix4_init_f32(&RadixFFT, FFTSize, 0, 1);
        arm_cfft_radix4_f32(&RadixFFT, inputSamp);
        arm_cmplx_mag_f32(inputSamp, outputMagn, FFTSize);
        
        float averageMagnitude = 0.0f;

        for (uint8_t i = 0; i < OutputBins - 1; i++){
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
};

IntervalTimer MicrophoneFourier::sampleTimer;
TimeStep MicrophoneFourier::timeStep = TimeStep(60);

const uint16_t MicrophoneFourier::FFTSize;
const uint8_t MicrophoneFourier::OutputBins;
uint16_t MicrophoneFourier::sampleRate = 8000;
uint16_t MicrophoneFourier::samples = 0;
uint16_t MicrophoneFourier::samplesStorage = 0;
uint8_t MicrophoneFourier::pin = 0;
float MicrophoneFourier::minDB = 50.0f;
float MicrophoneFourier::maxDB = 120.0f;
float MicrophoneFourier::threshold = 400.0f;
float MicrophoneFourier::refreshRate = 60.0f;
bool MicrophoneFourier::samplesReady = false;
bool MicrophoneFourier::isInitialized = false;
DerivativeFilter MicrophoneFourier::peakFilterRate;

uint16_t MicrophoneFourier::frequencyBins[];
float MicrophoneFourier::inputSamp[];
float MicrophoneFourier::inputStorage[];
float MicrophoneFourier::outputMagn[];
float MicrophoneFourier::outputData[];
float MicrophoneFourier::outputDataFilt[];
FFTFilter MicrophoneFourier::fftFilters[];

arm_cfft_radix4_instance_f32 MicrophoneFourier::RadixFFT;
