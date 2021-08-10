#pragma once

#include "..\..\Materials\Image.h"

class ExampleImage : public Image{
private:
	static const uint8_t rgbMemory[];

public:
	ExampleImage(Vector2D size, Vector2D offset) : Image(Image::RGB, rgbMemory, 2, 1) {
		SetSize(size);
		SetPosition(size);
	}
};

const uint8_t ExampleImage::rgbMemory[] PROGMEM = {206,8,108,206,8,108};