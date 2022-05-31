#include "..\Filter\KalmanFilter.h"
#include "..\Filter\MinFilter.h"
#include "..\Math\Mathematics.h"
#include <Arduino.h>

class MicrophoneSimple {
private:
    uint8_t pin;
    KalmanFilter<40> mv = KalmanFilter<40>(0.075f);
    MinFilter<100> minF = MinFilter<100>();
    KalmanFilter<10> output = KalmanFilter<10>(0.1f);
    float previousReading = 0.0f;
    long previousMillis = 0;
    long startMillis = 0;

public:
    MicrophoneSimple(const uint8_t pin)
        : pin(pin),
          previousMillis(millis()), // Set the value to something other than zero
          startMillis(previousMillis) {
        analogReadRes(12);
        analogReadAveraging(32);

        pinMode(pin, INPUT);
    }

    float Update() {
        const float read = analogRead(pin);
        const float change = read - previousReading;
        const float dT = ((float)millis() - (float)previousMillis) * 1e-3f; // / 1000.0f
        const float changeRate = change / dT;
        const float amplitude = mv.Filter(fabs(changeRate));
        const float minimum = minF.Filter(amplitude);
        const float normalized = Mathematics::Constrain(amplitude - minimum - 250, 0.0f, 4000.0f);
        const float truncate = output.Filter(normalized * 1e-2f); // / 100.0f

        /*
        Serial.print(read);
        Serial.print('\t');
        Serial.print(amplitude);
        Serial.print('\t');
        Serial.print(normalized);
        Serial.print('\t');
        Serial.print(minimum);
        Serial.print('\t');
        Serial.println(truncate * 100.0f);
        */

        previousReading = read;
        previousMillis = millis();

        return Mathematics::Constrain(truncate, 0.0f, 1.0f);
    }
};
