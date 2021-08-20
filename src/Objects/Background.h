#pragma once

#include "..\Render\Object3D.h"
#include "..\Materials\SimpleMaterial.h"

class Background{
private:
	Vector3D basisVertices[3] = {Vector3D(1000.0000f,-1000.0000f,0.0000f),Vector3D(-1000.0000f,-1000.0000f,0.0000f),Vector3D(0.0000f,1000.0000f,0.0000f)};
	IndexGroup basisIndexes[1] = {IndexGroup(0,1,2)};
	TriangleGroup triangleGroup = TriangleGroup(&basisVertices[0], &basisIndexes[0], 3, 1);
	SimpleMaterial simpleMaterial = SimpleMaterial(RGBColor(128, 128, 128));
	Object3D basisObj = Object3D(&triangleGroup, &simpleMaterial);

public:
	Background(){}

	Object3D* GetObject(){
		return &basisObj;
	}
};
