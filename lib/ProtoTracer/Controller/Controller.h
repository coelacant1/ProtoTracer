#pragma once

#include <Arduino.h>
#include "../Utils/Math/Mathematics.h"
#include "../Camera/CameraManager/CameraManager.h"

class Controller {
private:
    const uint32_t softStart = 5000000; // microseconds
    uint32_t previousTime;

protected:
    CameraManager* cameras;
    uint8_t brightness;
    uint8_t accentBrightness;
    uint8_t maxBrightness;
    uint8_t maxAccentBrightness;
    bool isOn = false;
    bool startTime = false;

    Controller(CameraManager* cameras, uint8_t maxBrightness, uint8_t maxAccentBrightness);

    void UpdateBrightness();

public:
    virtual void Initialize() = 0;
    virtual void Display() = 0;
    uint8_t GetBrightness();
    uint8_t GetAccentBrightness();
    virtual void SetBrightness(uint8_t maxBrightness) = 0;
    virtual void SetAccentBrightness(uint8_t maxAccentBrightness) = 0;
};
