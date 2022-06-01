//Configured for 60dB gain

#define ARM_MATH_CM4

#include <Arduino.h>
#include <arm_math.h>
#include <IntervalTimer.h>
#include "..\Math\Mathematics.h"
#include "MicrophoneSimple_MAX9814.h"
#include "..\Filter\DerivativeFilter.h"
#include "..\Filter\FFTFilter.h"
#include "..\Filter\PeakDetection.h"

class MicrophoneFourier{
private:
    static IntervalTimer sampleTimer;

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
    static bool samplesReady;
    static PeakDetection<OutputBins> peakDetection;
    static DerivativeFilter peakFilterRate;

    static uint16_t frequencyBins[OutputBins];
    static float inputSamp[FFTSize * 2];
    static float inputStorage[FFTSize];
    static float outputMagn[FFTSize];
    static float outputAR[OutputBins];
    static float outputData[OutputBins];
    static float peaks[OutputBins];
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
        inputSamp[samples++] = (float)analogRead(pin);
        inputSamp[samples++] = 0.0f;

        inputStorage[samplesStorage++] = inputSamp[samples - 2];

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
    static void Initialize(uint8_t pin, uint16_t sampleRate, float minDB, float maxDB){
        MicrophoneFourier::minDB = minDB;
        MicrophoneFourier::maxDB = maxDB;
        MicrophoneFourier::pin = pin;

        pinMode(pin, INPUT);
        analogReadResolution(12);
        //analogReadAveraging(8);

        MicrophoneFourier::sampleRate = sampleRate;
        MicrophoneFourier::samples = 0;
        MicrophoneFourier::samplesReady = false;

        float windowRange = float(sampleRate) / 2.0f / float(OutputBins);

        for (uint8_t i = 0; i < OutputBins; i++){
            float frequency = (float(i) * windowRange);
            frequencyBins[i] = uint16_t(frequency / float(sampleRate / FFTSize));
        }

        StartSampler();
    }

    static float* GetFourier(uint8_t &bins){
        bins = OutputBins - 1;

        return outputData;
    }

    static float GetCurrentMagnitude(){
        return threshold;
    }
    
    static void Update(){
        if(!samplesReady) return;

        arm_cfft_radix4_init_f32(&RadixFFT, FFTSize, 0, 1);
        arm_cfft_radix4_f32(&RadixFFT, inputSamp);
        arm_cmplx_mag_f32(inputSamp, outputMagn, FFTSize);
        
        

        float averageMagnitude = 0.0f;
        
        for (uint8_t i = 0; i < OutputBins - 1; i++){
            float intensity = 20.0f * log10f(AverageMagnitude(i, i + 1));

            intensity = map(intensity, minDB, maxDB, 0.0f, 1.0f);

            fftFilters[i].Filter(intensity);

            outputData[i] = intensity;
            if (i % 12 == 0) averageMagnitude = peakFilterRate.Filter(inputStorage[i] / 4096.0f);

            if (i > 5){
                float average = 0.0f;

                for (uint8_t j = i - 5; j < i; j++){
                    average += fftFilters[j].GetOutput();
                }

                outputAR[i] = powf(average / 5.0f, 2.0f);
            }
        }

        averageMagnitude *= 10.0f;
        threshold = powf(averageMagnitude, 2.0f);
        threshold = threshold > 0.2f ? (threshold * 5.0f > 1.0f ? 1.0f : threshold * 5.0f) : 0.0f;

        if (threshold > 0.2f){
            peakDetection.Calculate(outputAR, peaks);
        }
        else{
            for (uint8_t i = 0; i < OutputBins; i++) peaks[i] = 0;
        }
        /*
        Serial.print(inputStorage[0] / 4096.0f);
        Serial.print(',');
        Serial.print(averageMagnitude);
        Serial.print(',');
        Serial.println(threshold * 10.0f);
        */
        
        Serial.print(10);
        Serial.print(',');
        Serial.println(10);

        for (uint8_t i = 0; i < OutputBins - 5; i++){
            for (uint8_t j = 0; j < 2; j++){
                Serial.print(peaks[i] * 6.0f);
                Serial.print(',');
                Serial.println(outputAR[i] * 10.0f);
            }
        }

        for (uint16_t i = 0; i < 128; i++){
            Serial.print(0);
            Serial.print(',');
            Serial.println(0);
        }
        
        StartSampler();
    }
};

IntervalTimer MicrophoneFourier::sampleTimer;

const uint16_t MicrophoneFourier::FFTSize;
const uint8_t MicrophoneFourier::OutputBins;
uint16_t MicrophoneFourier::sampleRate;
uint16_t MicrophoneFourier::samples;
uint16_t MicrophoneFourier::samplesStorage;
uint8_t MicrophoneFourier::pin;
float MicrophoneFourier::minDB;
float MicrophoneFourier::maxDB;
float MicrophoneFourier::threshold;
bool MicrophoneFourier::samplesReady;
PeakDetection<MicrophoneFourier::OutputBins> MicrophoneFourier::peakDetection;
DerivativeFilter MicrophoneFourier::peakFilterRate;

uint16_t MicrophoneFourier::frequencyBins[];
float MicrophoneFourier::inputSamp[];
float MicrophoneFourier::inputStorage[];
float MicrophoneFourier::outputMagn[];
float MicrophoneFourier::outputData[];
float MicrophoneFourier::outputAR[];
float MicrophoneFourier::peaks[];
FFTFilter MicrophoneFourier::fftFilters[];

arm_cfft_radix4_instance_f32 MicrophoneFourier::RadixFFT;
