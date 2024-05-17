#pragma once

#include <stdint.h>

#include "Controller.h"
#include "SmartMatrixHUB75.h"
#include "../Camera/CameraManager/CameraManager.h"
#include "../Camera/Pixels/PixelGroup.h"

class HUB75ControllerSplit : public Controller {
public:
    HUB75ControllerSplit(CameraManager* cameras, uint8_t maxBrightness, uint8_t maxAccentBrightness);

    void Initialize() override;

    void Display() override;
    
    void SetBrightness(uint8_t maxBrightness);

    void SetAccentBrightness(uint8_t maxAccentBrightness);

};
