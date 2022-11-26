//Sharp GP2Y0A02YK
//Polynomial curve from: https://lucidar.me/en/arduino/arduino-accurate-distance-measurement-sharp-GP2Y0A02YK/
#pragma once

#include <Arduino.h>

class SHARPGP2Y{
private:
    float distance = 0.0f;
    uint8_t pin;

    float ReadingToDistance(uint8_t reading){
        float value = float(reading);
        float value2 = value * value;

        return 2583.711122992086f
            - 20.19789785547f * value + 0.071746539329f * value2
            - 0.000115854182f * value2 * value + 0.000000068590f * value2 * value2;
    }

public:
    SHARPGP2Y(uint8_t pin): pin(pin){
        pinMode(pin, INPUT);
    }

    float GetDistance(){
        return distance;
    }
    
    float Update(){
        distance = ReadingToDistance(analogRead(pin));

        return distance;
    }


};
