#pragma once

#include "../../../Scene/Materials/Static/SimpleMaterial.h"
#include "../../../Scene/Objects/Object3D.h"

class LEDStripBackground{
private:
	Vector3D basisVertices[4] = {Vector3D(600.0000f,-100.0000f,0.0000f),Vector3D(600.0000f,100.0000f,0.0000f),Vector3D(400.0000f,100.0000f,0.0000f),Vector3D(400.0000f,-100.0000f,0.0000f)};
	IndexGroup basisIndexes[2] = {IndexGroup(0, 1, 2), IndexGroup(0, 2, 3)};
	TriangleGroup triangleGroup = TriangleGroup(&basisVertices[0], &basisIndexes[0], 4, 2);
	SimpleMaterial simpleMaterial = SimpleMaterial(RGBColor(128, 128, 128));
	Object3D basisObj = Object3D(&triangleGroup, &simpleMaterial);

public:
	LEDStripBackground(){}

	Object3D* GetObject(){
		return &basisObj;
	}
};
