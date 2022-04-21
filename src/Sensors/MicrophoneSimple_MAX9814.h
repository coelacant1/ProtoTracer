//Configured for 60dB gain

#include <Arduino.h>
#include "..\Math\Mathematics.h"
#include "..\Filter\KalmanFilter.h"
#include "..\Filter\MinFilter.h"

class MicrophoneSimple{
private:
    uint8_t pin;
    KalmanFilter mv = KalmanFilter(0.1f, 10);
    MinFilter minF = MinFilter(100);
    KalmanFilter output = KalmanFilter(0.1f, 10);
    float previousReading = 0.0f;
    long previousMillis = 0;
    long startMillis = 0;

public:
    MicrophoneSimple(uint8_t pin){
        this->pin = pin;

        analogReadRes(12);
        analogReadAveraging(32);

        pinMode(pin, INPUT);

        startMillis = millis();
    }

    float Update(){
        float read = analogRead(pin);
        float change = read - previousReading;
        float dT = ((float)millis() - (float)previousMillis) / 1000.0f;
        float changeRate = change / dT;
        float amplitude = mv.Filter(fabs(changeRate));
        float minimum = minF.Filter(amplitude);
        float normalized = Mathematics::Constrain(amplitude - minimum - 20000, 0.0f, 40000.0f);
        float truncate = output.Filter(normalized / 100.0f);

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
