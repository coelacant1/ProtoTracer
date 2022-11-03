#pragma once

#include <Arduino.h>

class TimeStep{
private:
    unsigned long previousMillis;
    uint16_t updateInterval = 1000;

public:
    TimeStep(float frequency){
        SetFrequency(frequency);
    }

    void SetFrequency(float frequency){
        this->updateInterval = uint16_t((1.0f / frequency) * 1000.0f);//time in milliseconds
    }

    bool IsReady(){
        if (millis() - updateInterval > previousMillis){
            previousMillis = millis();
            return true;
        }
        else {
            return false;
        }
    }
};
