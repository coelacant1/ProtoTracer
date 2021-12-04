#include <Arduino.h>
#include "..\Math\Mathematics.h"
#include "..\Filter\KalmanFilter.h"

class MicrophoneSimple{
private:
    uint8_t pin;
    KalmanFilter dc = KalmanFilter(0.01f, 100);
    KalmanFilter mv = KalmanFilter(0.1f, 10);

public:
    MicrophoneSimple(uint8_t pin){
        this->pin = pin;

        pinMode(pin, INPUT);
    }

    float Update(){
        float read = analogRead(pin);
        float dcBias = dc.Filter(read);
        float change = fabs(dcBias - read);

        float filter = Mathematics::Constrain(mv.Filter(change) / 25.0f, 0.0f, 1.0f);

        return filter;
    }
};
