#pragma once

#include "..\..\..\Scene\Materials\Static\SimpleMaterial.h"
#include "..\..\..\Scene\Materials\Static\UVMap.h"
#include "..\..\..\Scene\Objects\Object3D.h"
#include "..\..\..\Renderer\Utils\IndexGroup.h"

class Cursor {
private:
	Vector3D basisVertices[4] = {Vector3D(0.0000f,-9.0000f,0.0000f),Vector3D(27.0000f,-8.9962f,0.0000f),Vector3D(27.0000f,-4.5038f,0.0000f),Vector3D(0.0000f,-4.5038f,0.0000f)};
	IndexGroup basisIndexes[2] = {IndexGroup(2,1,0),IndexGroup(3,2,0)};
	TriangleGroup triangleGroup = TriangleGroup(&basisVertices[0], &basisIndexes[0], 4, 2);
	SimpleMaterial simpleMaterial = SimpleMaterial(RGBColor(128, 128, 128));
	Object3D basisObj = Object3D(&triangleGroup, &simpleMaterial);

public:
	Cursor(){}

	Object3D* GetObject(){
		return &basisObj;
	}
};
