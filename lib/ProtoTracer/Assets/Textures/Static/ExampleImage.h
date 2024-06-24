#pragma once

#include "../../Materials/Image.h"

class ExampleImage : public Image{
private:
	static const uint8_t rgbMemory[];
	static const uint8_t rgbColors[];

public:
	ExampleImage(Vector2D size, Vector2D offset) : Image(rgbMemory, rgbColors, 2, 1, 2) {
		SetSize(size);
		SetPosition(size);
	}
};

const uint8_t ExampleImage::rgbMemory[] PROGMEM = { 0, 1 };
const uint8_t ExampleImage::rgbColors[] PROGMEM = { 206, 8, 108, 206, 8, 108};