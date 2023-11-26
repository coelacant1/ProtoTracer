#include "MicrophoneSimple_MAX9814.h"

MicrophoneSimple::MicrophoneSimple() {
    startMillis = millis();
}

MicrophoneSimple::MicrophoneSimple(uint8_t pin, float gain, float clipping) {
    this->pin = pin;
    this->gain = gain;

    analogReadRes(12);
    analogReadAveraging(32);

    pinMode(pin, INPUT);

    startMillis = millis();
}

float MicrophoneSimple::GetCurrentValue() {
    return currentValue;
}

float MicrophoneSimple::Update() {
    float read = analogRead(pin) * gain;
    float change = read - previousReading;
    float dT = ((float)millis() - (float)previousMillis) / 1000.0f;
    float changeRate = change / dT;
    float amplitude = mv.Filter(fabs(changeRate));
    float minimum = minF.Filter(amplitude);
    float normalized = Mathematics::Constrain(amplitude - minimum - 20000, 0.0f, 40000.0f);
    float truncate = output.Filter(normalized / 100.0f / clipping);

    previousReading = read;
    previousMillis = millis();

    currentValue = Mathematics::Constrain(truncate, 0.0f, 1.0f);

    return currentValue;
}

float MicrophoneSimple::Update(float read) {
    float change = read - previousReading;
    float dT = ((float)millis() - (float)previousMillis) / 1000.0f;
    float changeRate = change / dT;
    float amplitude = mv.Filter(fabs(changeRate));
    float minimum = minF.Filter(amplitude);
    float normalized = Mathematics::Constrain(amplitude - minimum - 40000, 0.0f, 40000.0f);
    float truncate = output.Filter(normalized / 100.0f / clipping);

    previousReading = read;
    previousMillis = millis();

    currentValue = Mathematics::Constrain(truncate, 0.0f, 1.0f);

    return currentValue;
}
