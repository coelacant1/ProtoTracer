#pragma once

#include <stdint.h>
#include <OctoWS2811.h>

#include "Controller.h"
#include "..\Camera\CameraManager\CameraManager.h"
#include "..\Camera\Pixels\PixelGroup.h"

const int ledsPerStrip = 346;
DMAMEM int displayMemory[346 * 6];
int drawingMemory[346 * 6];
const int config = WS2811_GRB | WS2811_800kHz;

OctoWS2811 leds(ledsPerStrip, displayMemory, drawingMemory, config);

class WS35Controller : public Controller {
public:
    WS35Controller(CameraManager* cameras, uint8_t maxBrightness);

    void Initialize() override;

    void Display() override;

    void SetPixels(uint8_t strip, uint16_t led, RGBColor rgb);
    
    void SetBrightness(uint8_t maxBrightness) override;

    void SetAccentBrightness(uint8_t maxAccentBrightness) override;

};
