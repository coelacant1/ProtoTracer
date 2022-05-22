//Configured for 60dB gain

#define ARM_MATH_CM4

#include <Arduino.h>
#include <arm_math.h>
#include <IntervalTimer.h>
#include "..\Math\Mathematics.h"

class MicrophoneFourier{
private:
    static IntervalTimer sampleTimer;

    static const uint16_t FFTSize = 256;
    static const uint8_t OutputBins = 64;
    static uint16_t sampleRate;
    static uint16_t samples;
    static uint8_t pin;
    static float minDB;
    static float maxDB;
    static bool samplesReady;

    static uint16_t frequencyBins[OutputBins];
    static float inputSamp[FFTSize * 2];
    static float outputMagn[FFTSize];
    static float outputData[OutputBins - 1];
    
    static arm_cfft_radix4_instance_f32 RadixFFT;

    static float AverageMagnitude(uint16_t binL, uint16_t binH){
        float average = 0.0f;

        for (uint16_t i = 1; i < FFTSize / 2; i++){
            if (i >= binL && i <= binH) average += outputMagn[i];
        }

        return average / float(binH - binL + 1);
    }

    static void SamplerCallback(){
        inputSamp[samples++] = (float32_t)analogRead(pin);
        inputSamp[samples++] = 0.0f;

        if(samples >= FFTSize * 2){
            sampleTimer.end();
            samplesReady = true;
        }
    }

    static void StartSampler(){
        samplesReady = false;
        samples = 0;
        sampleTimer.begin(SamplerCallback, 1000000 / sampleRate);
    }

public:
    static void Initialize(uint8_t pin, uint16_t sampleRate, float minDB, float maxDB){
        MicrophoneFourier::minDB = minDB;
        MicrophoneFourier::maxDB = maxDB;
        MicrophoneFourier::pin = pin;

        pinMode(pin, INPUT);
        //analogReadResolution(12);
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

    static void Update(){
        if(!samplesReady) return;

        arm_cfft_radix4_init_f32(&RadixFFT, FFTSize, 0, 1);
        arm_cfft_radix4_f32(&RadixFFT, inputSamp);
        arm_cmplx_mag_f32(inputSamp, outputMagn, FFTSize);
        
        //Serial.print("FFT: ");

        for (uint8_t i = 0; i < OutputBins - 1; i++){
            float intensity = 20.0f * log10f(AverageMagnitude(i, i + 1));

            intensity = map(intensity, minDB, maxDB, 0.0f, 1.0f);
            intensity = Mathematics::Constrain(intensity, 0.0f, 1.0f);

            outputData[i] = intensity;
            
            //Serial.print(intensity, 3);
            //Serial.print('\t');
        }

        //Serial.println();

        StartSampler();
    }
};

IntervalTimer MicrophoneFourier::sampleTimer;

const uint16_t MicrophoneFourier::FFTSize;
const uint8_t MicrophoneFourier::OutputBins;
uint16_t MicrophoneFourier::sampleRate;
uint16_t MicrophoneFourier::samples;
uint8_t MicrophoneFourier::pin;
float MicrophoneFourier::minDB;
float MicrophoneFourier::maxDB;
bool MicrophoneFourier::samplesReady;

uint16_t MicrophoneFourier::frequencyBins[];
float MicrophoneFourier::inputSamp[];
float MicrophoneFourier::outputMagn[];
float MicrophoneFourier::outputData[];

arm_cfft_radix4_instance_f32 MicrophoneFourier::RadixFFT;
