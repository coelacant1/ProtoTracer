#pragma once

#include <stdint.h>
#include <OctoWS2811.h>

#include "Controller.h"
#include "../Camera/CameraManager/CameraManager.h"
#include "../Camera/Pixels/PixelGroup.h"

class WS35Controller : public Controller {
private:
    const int ledsPerStrip = 346;
    int drawingMemory[346 * 6];
    const int config = WS2811_GRB | WS2811_800kHz;
    OctoWS2811 leds;
public:

    WS35Controller(CameraManager* cameras, uint8_t maxBrightness);

    void Initialize() override;

    void Display() override;

    void SetPixels(uint8_t strip, uint16_t led, RGBColor rgb);
    
    void SetBrightness(uint8_t maxBrightness) override;

    void SetAccentBrightness(uint8_t maxAccentBrightness) override;

};
