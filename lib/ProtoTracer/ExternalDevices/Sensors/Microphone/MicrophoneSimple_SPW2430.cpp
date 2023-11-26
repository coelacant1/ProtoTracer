#include "MicrophoneSimple_SPW2430.h"

MicrophoneSimple::MicrophoneSimple(uint8_t pin) {
    this->pin = pin;

    analogReadRes(12);
    analogReadAveraging(32);

    pinMode(pin, INPUT);

    startMillis = millis();
}

float MicrophoneSimple::Update() {
    float read = analogRead(pin);
    float change = read - previousReading;
    float dT = ((float)millis() - (float)previousMillis) / 1000.0f;
    float changeRate = change / dT;
    float amplitude = mv.Filter(fabs(changeRate));
    float minimum = minF.Filter(amplitude);
    float normalized = Mathematics::Constrain(amplitude - minimum - 250, 0.0f, 4000.0f);
    float truncate = output.Filter(normalized / 100.0f);
    
    previousReading = read;
    previousMillis = millis();

    return Mathematics::Constrain(truncate, 0.0f, 1.0f);
}
