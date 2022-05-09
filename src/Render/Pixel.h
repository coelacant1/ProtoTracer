#pragma once

#include "..\Materials\RGBColor.h"

class Pixel {
	Vector2D* position;

public:
  	RGBColor Color;

	Pixel() {}

	Pixel(Vector2D* position)
		: position(position) {}

	Vector2D GetPosition(){
		return *position;
	}

};
