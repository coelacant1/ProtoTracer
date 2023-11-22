#pragma once

#include <stdint.h>

#include "Controller.h"
#include "SmartMatrixHUB75.h"
#include "..\Camera\CameraManager\CameraManager.h"
#include "..\Camera\Pixels\PixelGroup.h"

class HUB75Controller : public Controller {
public:
    HUB75Controller(CameraManager* cameras, uint8_t maxBrightness, uint8_t maxAccentBrightness);

    void Initialize() override;

    void Display() override;
    
    void SetBrightness(uint8_t maxBrightness) override;

    void SetAccentBrightness(uint8_t maxAccentBrightness) override;

};
