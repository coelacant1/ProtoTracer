//Configured for 60dB gain

#include <Arduino.h>
#include "..\Math\Mathematics.h"
#include "..\Filter\KalmanFilter.h"
#include "..\Filter\MinFilter.h"

class MicrophoneSimple{
private:
    uint8_t pin;
    KalmanFilter<5> mv = KalmanFilter<5>(0.2f);
    MinFilter<100> minF = MinFilter<100>();
    KalmanFilter<5> output = KalmanFilter<5>(0.2f);
    float previousReading = 0.0f;
    float gain = 1.0f;
    float clipping = 1.0f;
    long previousMillis = 0;
    long startMillis = 0;

public:
    MicrophoneSimple(){
        startMillis = millis();
    }

    MicrophoneSimple(uint8_t pin, float gain = 1.0f, float clipping = 1.0f){
        this->pin = pin;
        this->gain = gain;

        analogReadRes(12);
        analogReadAveraging(32);

        pinMode(pin, INPUT);

        startMillis = millis();
    }

    float Update(){
        float read = analogRead(pin) * gain;
        float change = read - previousReading;
        float dT = ((float)millis() - (float)previousMillis) / 1000.0f;
        float changeRate = change / dT;
        float amplitude = mv.Filter(fabs(changeRate));
        float minimum = minF.Filter(amplitude);
        float normalized = Mathematics::Constrain(amplitude - minimum - 20000, 0.0f, 40000.0f);
        float truncate = output.Filter(normalized / 100.0f / clipping);

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

    float Update(float read){
        float change = read - previousReading;
        float dT = ((float)millis() - (float)previousMillis) / 1000.0f;
        float changeRate = change / dT;
        float amplitude = mv.Filter(fabs(changeRate));
        float minimum = minF.Filter(amplitude);
        float normalized = Mathematics::Constrain(amplitude - minimum - 40000, 0.0f, 40000.0f);
        float truncate = output.Filter(normalized / 100.0f / clipping);
        
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
