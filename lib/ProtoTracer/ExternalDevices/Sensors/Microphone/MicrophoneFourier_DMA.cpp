#include "MicrophoneFourier_DMA.h"

ADC* adc = new ADC();

DMAMEM static volatile uint16_t __attribute__((aligned(32))) adc_buffer1[256];
DMAMEM static volatile uint16_t __attribute__((aligned(32))) adc_buffer2[256];

AnalogBufferDMA adc_dma_instance(adc_buffer1, 256, adc_buffer2, 256);
bool MicrophoneFourier::microphoneGain_50db = false;
uint8_t MicrophoneFourier::gain_pin = 0;

// Hanning Window LUT from the Teensy audio library
const int16_t MicrophoneFourier::Hanning256[] __attribute__((aligned(4))) = {
    0,
    5,
    20,
    45,
    80,
    124,
    179,
    243,
    317,
    401,
    495,
    598,
    711,
    833,
    965,
    1106,
    1257,
    1416,
    1585,
    1763,
    1949,
    2145,
    2349,
    2561,
    2782,
    3011,
    3249,
    3494,
    3747,
    4008,
    4276,
    4552,
    4834,
    5124,
    5421,
    5724,
    6034,
    6350,
    6672,
    7000,
    7334,
    7673,
    8018,
    8367,
    8722,
    9081,
    9445,
    9812,
    10184,
    10560,
    10939,
    11321,
    11707,
    12095,
    12486,
    12879,
    13274,
    13672,
    14070,
    14471,
    14872,
    15275,
    15678,
    16081,
    16485,
    16889,
    17292,
    17695,
    18097,
    18498,
    18897,
    19295,
    19692,
    20086,
    20478,
    20868,
    21255,
    21639,
    22019,
    22397,
    22770,
    23140,
    23506,
    23867,
    24224,
    24576,
    24923,
    25265,
    25602,
    25932,
    26258,
    26577,
    26890,
    27196,
    27496,
    27789,
    28076,
    28355,
    28627,
    28892,
    29148,
    29398,
    29639,
    29872,
    30097,
    30314,
    30522,
    30722,
    30913,
    31095,
    31268,
    31432,
    31588,
    31733,
    31870,
    31997,
    32115,
    32223,
    32321,
    32410,
    32489,
    32558,
    32618,
    32667,
    32707,
    32737,
    32757,
    32767,
    32767,
    32757,
    32737,
    32707,
    32667,
    32618,
    32558,
    32489,
    32410,
    32321,
    32223,
    32115,
    31997,
    31870,
    31733,
    31588,
    31432,
    31268,
    31095,
    30913,
    30722,
    30522,
    30314,
    30097,
    29872,
    29639,
    29398,
    29148,
    28892,
    28627,
    28355,
    28076,
    27789,
    27496,
    27196,
    26890,
    26577,
    26258,
    25932,
    25602,
    25265,
    24923,
    24576,
    24224,
    23867,
    23506,
    23140,
    22770,
    22397,
    22019,
    21639,
    21255,
    20868,
    20478,
    20086,
    19692,
    19295,
    18897,
    18498,
    18097,
    17695,
    17292,
    16889,
    16485,
    16081,
    15678,
    15275,
    14872,
    14471,
    14070,
    13672,
    13274,
    12879,
    12486,
    12095,
    11707,
    11321,
    10939,
    10560,
    10184,
    9812,
    9445,
    9081,
    8722,
    8367,
    8018,
    7673,
    7334,
    7000,
    6672,
    6350,
    6034,
    5724,
    5421,
    5124,
    4834,
    4552,
    4276,
    4008,
    3747,
    3494,
    3249,
    3011,
    2782,
    2561,
    2349,
    2145,
    1949,
    1763,
    1585,
    1416,
    1257,
    1106,
    965,
    833,
    711,
    598,
    495,
    401,
    317,
    243,
    179,
    124,
    80,
    45,
    20,
    5,
    0,
};

void MicrophoneFourier::window_raw_fft_data(void* buffer, const void* window) {
    int16_t* buf = (int16_t*)buffer;
    const int16_t* win = (int16_t*)window;

    for (int i = 0; i < 256; i++) {
        int32_t val = *buf * *win++;
        *buf = val >> 15;
        buf += 2;
    }
}


void MicrophoneFourier::SamplerCallback(AnalogBufferDMA* dma_buffer_instance, int8_t adc_num) {
    uint16_t samplePos = 0;
    uint16_t samplesStoragePos = 0;
    volatile uint16_t* data = dma_buffer_instance->bufferLastISRFilled();
    volatile uint16_t* data_end = data + dma_buffer_instance->bufferCountLastISRFilled();

    // Clear the Data cache so we know we're getting the most up-to-date data
    if ((uint32_t)data >= 0x20200000u)
        arm_dcache_delete((void*)data, sizeof(adc_buffer1));

    // Copy DMA Buffer into the storage buffer
    while (data < data_end) {
        inputStorage[samplesStoragePos++] = (float)*data;
        data++;
    }

    // Clear the QuadTimer Interrupt
    dma_buffer_instance->clearInterrupt();

    // Window the raw data
    window_raw_fft_data(inputStorage, Hanning256);

    // Interleave Real and Imaginary Numbers into a separate buffer for the FFT DSP
    samplePos = 0;
    for (int i = 0; i < 256; i++) {
        inputSamp[samplePos++] = inputStorage[i];
        inputSamp[samplePos++] = 0.0f;
    }
}

void MicrophoneFourier::Initialize(uint8_t pin, uint32_t sampleRate, float minDB, float maxDB) {
    MicrophoneFourier::minDB = minDB;
    MicrophoneFourier::maxDB = maxDB;
    MicrophoneFourier::pin = pin;
    MicrophoneFourier::sampleRate = sampleRate;

    pinMode(pin, INPUT);

    adc->adc1->setAveraging(32);
    adc->adc1->setResolution(16);
    adc->adc1->calibrate();
    adc->adc1->wait_for_cal();

    adc_dma_instance.init(adc, ADC_1);

    adc->adc1->startSingleRead(pin);
    adc->adc1->startTimer(sampleRate);

    isInitialized = true;
}

void MicrophoneFourier::Initialize(uint8_t pin, uint8_t gain_pin, uint32_t sampleRate, float minDB, float maxDB, bool microphoneGain_50db) {
    MicrophoneFourier::minDB = minDB;
    MicrophoneFourier::maxDB = maxDB;
    MicrophoneFourier::pin = pin;
    MicrophoneFourier::gain_pin = gain_pin;
    MicrophoneFourier::sampleRate = sampleRate;
    MicrophoneFourier::microphoneGain_50db = microphoneGain_50db;

    pinMode(pin, INPUT);
    pinMode(gain_pin, OUTPUT);

    (!MicrophoneFourier::microphoneGain_50db) ? digitalWrite(gain_pin, 0) : digitalWrite(gain_pin, 1);

    adc->adc1->setAveraging(32);
    adc->adc1->setResolution(16);
    adc->adc1->calibrate();
    adc->adc1->wait_for_cal();

    adc_dma_instance.init(adc, ADC_1);

    adc->adc1->startSingleRead(pin);
    adc->adc1->startTimer(sampleRate);

    isInitialized = true;
}

void MicrophoneFourier::setSamplingRate(uint32_t sampleRate) {
    adc->adc1->stopTimer();
    MicrophoneFourier::sampleRate = sampleRate;
    adc->adc1->startTimer(sampleRate);
}

void MicrophoneFourier::setMicGain(bool is50db) {
    MicrophoneFourier::microphoneGain_50db = is50db;
    (!MicrophoneFourier::microphoneGain_50db) ? digitalWrite(gain_pin, 0) : digitalWrite(gain_pin, 1);
}


void MicrophoneFourier::UpdateDMA() {
    if (adc_dma_instance.interrupted()) {
        SamplerCallback(&adc_dma_instance, ADC_1);
        
        fft.Radix2FFT(inputSamp);
        fft.ComplexMagnitude(inputSamp, outputMagn);

        float averageMagnitude = 0.0f;

        for (uint16_t i = 0; i < OutputBins - 1; i++) {
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
