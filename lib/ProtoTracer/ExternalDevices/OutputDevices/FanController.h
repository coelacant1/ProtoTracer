#pragma once

#include <Arduino.h>
#include "../../Utils/Math/Mathematics.h"

class FanController {
private:
    uint8_t pin;
    uint8_t pwm;

public:
    FanController(uint8_t pin);

    void Initialize();
    void SetPWM(uint8_t pwm);
    void SetSpeed(float ratio);
    uint8_t GetPWM();
};
