#pragma once

#include "..\Materials\RGBColor.h"

typedef struct Pixel {
	Vector2D* position;

public:
  	RGBColor Color;

	Pixel() {}

	Pixel(Vector2D* position){
		this->position = position;
	}

	Vector2D GetPosition(){
		return *position;
	}

} Pixel;
