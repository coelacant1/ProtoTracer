#include "Wait.h"


Wait::Wait(unsigned long millisToWait) {
    this->millisToWait = millisToWait;
}

void Wait::Reset() {
    previousMillis = millis();
}

bool Wait::IsFinished() {
    return millis() - previousMillis >= millisToWait;
}
