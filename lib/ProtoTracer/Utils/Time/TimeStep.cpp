#include "TimeStep.h"

TimeStep::TimeStep(float frequency) {
    SetFrequency(frequency);
}

void TimeStep::SetFrequency(float frequency) {
    this->updateInterval = uint16_t((1.0f / frequency) * 1000.0f); // time in milliseconds
}

bool TimeStep::IsReady() {
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= updateInterval) {
        previousMillis = currentMillis;
        return true;
    } else {
        return false;
    }
}
