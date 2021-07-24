#pragma once

#include "..\Materials\RGBColor.h"

typedef struct Pixel {
public:
	float X = 0;
	float Y = 0;
  	RGBColor Color;

	Pixel() {}
	Pixel(float X, float Y) : X(X), Y(Y){}

} Pixel;
