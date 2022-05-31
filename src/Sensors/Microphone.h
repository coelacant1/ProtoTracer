#include <Arduino.h>
#include <arduinoFFT.h>

class Microphone {
private:
    static arduinoFFT FFT;
    static IntervalTimer readingTimer;
    static uint8_t pin;
    static const uint16_t samples = 64;
    static double vReal[samples];
    static double vImag[samples];
    static uint8_t exponent;

    static volatile double buffer[samples];
    static volatile double currentRead[samples];
    static int currentBuffer;

    static void CopyArray() {
        for (int i = 0; i < samples; i++) {
            vReal[i] = buffer[i];
        }
    }

    static void CopyBuffer() {
        for (int i = 0; i < samples; i++) {
            buffer[i] = currentRead[i];
        }
    }

    static void UpdateMicrophone() {
        if (currentBuffer < samples) {
            currentRead[currentBuffer++] = analogRead(pin);
        } else {
            CopyBuffer();
            currentBuffer = 0;
        }
    }

public:
    static void Initialize(const uint8_t pin) {
        Microphone::pin = pin;
        Microphone::currentBuffer = 0;

        FFT = arduinoFFT();
        exponent = FFT.Exponent(samples);

        readingTimer.begin(Microphone::UpdateMicrophone, 1000);
    }

    static void Update() {
        // update fft from current readings, disable interrupts
        noInterrupts();
        CopyArray(); // copy from memory to local value
        interrupts();

        FFT.Windowing(vReal, samples, FFT_WIN_TYP_HAMMING, FFT_FORWARD);
        FFT.Compute(vReal, vImag, samples, FFT_FORWARD);
        FFT.ComplexToMagnitude(vReal, vImag, samples);
        double peak = FFT.MajorPeak(vReal, samples, 1000);
    }
};

arduinoFFT Microphone::FFT;
IntervalTimer Microphone::readingTimer;
uint8_t Microphone::pin;
const uint16_t Microphone::samples;
double Microphone::vReal[Microphone::samples];
double Microphone::vImag[Microphone::samples];
uint8_t Microphone::exponent;

volatile double Microphone::buffer[Microphone::samples];
volatile double Microphone::currentRead[Microphone::samples];
int Microphone::currentBuffer;