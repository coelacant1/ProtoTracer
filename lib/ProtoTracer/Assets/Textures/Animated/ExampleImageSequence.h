#pragma once

#include "../../Animation/ImageSequence.h"

class SpryoSequence : public ImageSequence{
private:
    static const uint8_t spyro0001[];
    static const uint8_t spyro0002[];

    static const uint8_t* sequence[2];

	static const uint8_t rgbColors[];

    Image image;

public:
    SpryoSequence(Vector2D size, Vector2D offset, float fps) : image(spyro0001, rgbColors, 128, 72, 2), ImageSequence(&image, sequence, (unsigned int)2, fps){
        image.SetSize(size);
        image.SetPosition(offset);
    }
};

const uint8_t SpryoSequence::spyro0001[] PROGMEM = {};
const uint8_t SpryoSequence::spyro0002[] PROGMEM = {};

const uint8_t* SpryoSequence::sequence[] = {spyro0001, spyro0002};

const uint8_t SpryoSequence::rgbColors[] PROGMEM = { 206, 8, 108, 206, 8, 108};