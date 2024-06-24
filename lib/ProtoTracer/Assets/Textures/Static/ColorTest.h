#pragma once

#include "../../../Scene/Materials/Static/Image.h"

class ColorTest : public Image{
private:
	static const uint8_t rgbMemory[];
	static const uint8_t rgbColors[];

public:
	ColorTest(Vector2D size, Vector2D offset) : Image(rgbMemory, rgbColors, 128, 72, 16) {
		SetSize(size);
		SetPosition(offset);
	}
};
