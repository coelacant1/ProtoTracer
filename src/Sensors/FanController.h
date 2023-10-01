#pragma once

#include <Arduino.h>
#include "..\Math\Mathematics.h"

class FanController{
private:
    uint8_t pin;
    uint8_t pwm;

public:
    FanController(uint8_t pin){
        this->pin = pin;
    }

    void Initialize(){
        pinMode(pin, OUTPUT);
    }

    void SetPWM(uint8_t pwm){
        this->pwm = pwm;
        
        analogWrite(pin, pwm);
    }

    void SetSpeed(float ratio){
        uint8_t pwm = uint8_t(Mathematics::Map(ratio, 0.0f, 1.0f, 0.0f, 255.0f));

        SetPWM(pwm);
    }

    uint8_t GetPWM(){
        return pwm;
    }

};
