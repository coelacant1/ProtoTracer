#pragma once

#include "..\Materials\RGBColor.h"

typedef struct Pixel {
private:
	Vector2D* position;
	bool sorted = false;
	bool upExists = false;
	bool downExists = false;
	bool leftExists = false;
	bool rightExists = false;

	Pixel* up = nullptr;
	Pixel* down = nullptr;
	Pixel* left = nullptr;
	Pixel* right = nullptr;

public:
  	RGBColor* Color;
	
	Pixel() {}

	Pixel(Vector2D* position){
		this->position = position;
	}

	Vector2D GetPosition(){
		return *position;
	}

	void SetUpPixel(Pixel* pixel){
		this->up = pixel;
		this->upExists = true;
	}

	void SetDownPixel(Pixel* pixel){
		this->down = pixel;
		this->downExists = true;
	}

	void SetLeftPixel(Pixel* pixel){
		this->left = pixel;
		this->leftExists = true;
	}

	void SetRightPixel(Pixel* pixel){
		this->right = pixel;
		this->rightExists = true;
	}

	bool HasUpPixel(){ return upExists; }
	bool HasDownPixel(){ return downExists; }
	bool HasLeftPixel(){ return leftExists; }
	bool HasRightPixel(){ return rightExists; }

	Pixel* GetUpPixel(){ return up; }
	Pixel* GetDownPixel(){ return down; }
	Pixel* GetLeftPixel(){ return left; }
	Pixel* GetRightPixel(){ return right; }

} Pixel;
