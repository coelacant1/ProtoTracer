#define ARM_MATH_CM4

#include <Arduino.h>
#include <arm_math.h>
#include <ADC.h>
#include <DMAChannel.h>
#include <AnalogBufferDMA.h>
#include "..\Math\Mathematics.h"
#include "MicrophoneSimple_MAX9814.h"
#include "..\Filter\DerivativeFilter.h"
#include "..\Filter\FFTFilter.h"
#include "..\Filter\PeakDetection.h"

ADC *adc = new ADC();

DMAMEM static volatile uint16_t __attribute__((aligned(32))) adc_buffer1[256];
DMAMEM static volatile uint16_t __attribute__((aligned(32))) adc_buffer2[256];
AnalogBufferDMA adc_dma_instance(adc_buffer1, 256, adc_buffer2, 256);

class MicrophoneFourier
{
private:
    static const uint16_t FFTSize = 256;
    static const uint8_t OutputBins = 128;
    static uint16_t sampleRate;
    static uint8_t pin;
    static float minDB;
    static float maxDB;
    static float threshold;
    static float currentValue;
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

    static float AverageMagnitude(uint16_t binL, uint16_t binH)
    {
        float average = 0.0f;

        for (uint16_t i = 1; i < FFTSize / 2; i++)
        {
            if (i >= binL && i <= binH)
                average += outputMagn[i];
        }

        return average / float(binH - binL + 1);
    }

    static void SamplerCallback(AnalogBufferDMA *dma_buffer_instance, int8_t adc_num)
    {
        uint16_t samplePos = 0;
        uint16_t samplesStoragePos = 0;
        volatile uint16_t *temp = dma_buffer_instance->bufferLastISRFilled();
        volatile uint16_t *buffer_end = temp + dma_buffer_instance->bufferCountLastISRFilled();
        if ((uint32_t)temp >= 0x20200000u)
            arm_dcache_delete((void *)temp, sizeof(adc_buffer1));

        while (temp < buffer_end)
        {
            inputSamp[samplePos++] = *temp;
            inputSamp[samplePos++] = 0.0f;

            inputStorage[samplesStoragePos++] = *temp;
            temp++;
        }
        dma_buffer_instance->clearInterrupt();
    }

public:
    static void Initialize(uint8_t pin, uint32_t sampleRate, float minDB, float maxDB)
    {
        MicrophoneFourier::minDB = minDB;
        MicrophoneFourier::maxDB = maxDB;
        MicrophoneFourier::pin = pin;
        MicrophoneFourier::sampleRate = sampleRate;

        pinMode(pin, INPUT);
        adc->adc1->setAveraging(32);
        adc->adc1->setResolution(16);
        
        adc_dma_instance.init(adc, ADC_1);

        adc->adc1->startSingleRead(pin);
        adc->adc1->startTimer(sampleRate);

        float windowRange = float(sampleRate) / 2.0f / float(OutputBins);

        for (uint8_t i = 0; i < OutputBins; i++)
        {
            float frequency = (float(i) * windowRange);
            frequencyBins[i] = uint16_t(frequency / float(sampleRate / FFTSize));
        }

        isInitialized = true;
    }

    static bool IsInitialized()
    {
        return isInitialized;
    }

    static float GetSampleRate()
    {
        return sampleRate;
    }

    static float *GetSamples()
    {
        return inputStorage;
    }

    static float *GetFourier()
    {
        return outputData;
    }

    static float *GetFourierFiltered()
    {
        return outputDataFilt;
    }

    static float GetCurrentMagnitude()
    {
        return threshold;
    }

    static void Update()
    {
        if (adc_dma_instance.interrupted())
        {
            SamplerCallback(&adc_dma_instance, ADC_1);

            arm_cfft_radix4_init_f32(&RadixFFT, FFTSize, 0, 1);
            arm_cfft_radix4_f32(&RadixFFT, inputSamp);
            arm_cmplx_mag_f32(inputSamp, outputMagn, FFTSize);

            float averageMagnitude = 0.0f;

            for (uint8_t i = 0; i < OutputBins - 1; i++)
            {
                float intensity = 20.0f * log10f(AverageMagnitude(i, i + 1));

                intensity = map(intensity, minDB, maxDB, 0.0f, 1.0f);

                outputData[i] = intensity;
                outputDataFilt[i] = fftFilters[i].Filter(intensity);
                if (i % 12 == 0)
                    averageMagnitude = peakFilterRate.Filter(inputStorage[i] / 4096.0f);
            }

            averageMagnitude *= 10.0f;
            threshold = powf(averageMagnitude, 2.0f);
            threshold = threshold > 0.2f ? (threshold * 5.0f > 1.0f ? 1.0f : threshold * 5.0f) : 0.0f;
        }
    }
};

const uint16_t MicrophoneFourier::FFTSize;
const uint8_t MicrophoneFourier::OutputBins;
uint16_t MicrophoneFourier::sampleRate = 8000;
uint8_t MicrophoneFourier::pin = 0;
float MicrophoneFourier::minDB = 50.0f;
float MicrophoneFourier::maxDB = 120.0f;
float MicrophoneFourier::threshold = 400.0f;
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
