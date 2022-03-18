#include <Arduino.h>
#include "..\Math\Mathematics.h"
#include "..\Filter\KalmanFilter.h"
#include "..\Filter\MinFilter.h"

class MicrophoneSimple{
private:
    uint8_t pin;
    KalmanFilter mv = KalmanFilter(0.025f, 40);
    MinFilter minF = MinFilter(100);
    KalmanFilter output = KalmanFilter(0.2f, 5);
    float previousReading = 0.0f;
    long previousMillis = 0;

public:
    MicrophoneSimple(uint8_t pin){
        this->pin = pin;

        pinMode(pin, INPUT);
    }

    float Update(){
        float read = analogRead(pin);
        float change = read - previousReading;
        float dT = ((float)millis() - (float)previousMillis) / 1000.0f;
        float changeRate = change / dT;
        float amplitude = mv.Filter(fabs(changeRate));
        float minimum = minF.Filter(amplitude);
        float normalized = Mathematics::Constrain(amplitude - minimum - 150, 0.0f, 4000.0f);
        float truncate = normalized / 100.0f;
        
        previousReading = read;
        previousMillis = millis();

        return Mathematics::Constrain(truncate, 0.0f, 1.0f);
    }
};
