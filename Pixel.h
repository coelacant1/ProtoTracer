#pragma once

typedef struct Pixel {
public:
	float X = 0;
	float Y = 0;
	Vector3D RGB;

	Pixel() {}
	Pixel(float X, float Y) : X(X), Y(Y){}

} Pixel;
