#pragma once

#include <Arduino.h>

class Wait {
private:
    unsigned long previousMillis;
    unsigned long millisToWait;

public:
    Wait(unsigned long millisToWait);

    void Reset();
    bool IsFinished();
};
