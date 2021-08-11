#pragma once

#include "..\..\Animation\ImageSequence.h"

class SpyroImage : public Image{
public:
    SpyroImage(Vector2D size, Vector2D offset) : Image(Image::RGB, 128, 72) {
		SetSize(size);
		SetPosition(offset);
	}
};

class SpryoSequence : public ImageSequence{
private:
    static const uint8_t spyro0001[];
    static const uint8_t spyro0002[];

    static const uint8_t* sequence[2];

    SpyroImage spyroImage;

public:
    SpryoSequence(Vector2D size, Vector2D offset, float fps) : spyroImage(size, offset), ImageSequence(&spyroImage, sequence, (unsigned int)2, fps){

    }
};

const uint8_t SpryoSequence::spyro0001[] PROGMEM = {};
const uint8_t SpryoSequence::spyro0002[] PROGMEM = {};

const uint8_t* SpryoSequence::sequence[] = {spyro0001, spyro0002};