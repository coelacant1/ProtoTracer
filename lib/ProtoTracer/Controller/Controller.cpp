#include "Controller.h"

Controller::Controller(CameraManager* cameras, uint8_t maxBrightness, uint8_t maxAccentBrightness) {
    this->cameras = cameras;
    this->maxBrightness = maxBrightness;
    this->maxAccentBrightness = maxAccentBrightness;
}

void Controller::UpdateBrightness() {
    if (!startTime) {
        startTime = true;
        previousTime = micros();
    }

    if (!isOn && micros() < softStart + previousTime) {
        brightness = Mathematics::Map(micros(), previousTime, softStart + previousTime, uint32_t(0), uint32_t(maxBrightness));
        accentBrightness = Mathematics::Map(micros(), previousTime, softStart + previousTime, uint32_t(0), uint32_t(maxAccentBrightness));
    } else if (!isOn) {
        brightness = maxBrightness;
        accentBrightness = maxAccentBrightness;
        isOn = true;
    }
}

uint8_t Controller::GetBrightness() {
    return brightness;
}

uint8_t Controller::GetAccentBrightness() {
    return accentBrightness;
}

