#pragma once

#include "../../../Scene/Materials/Static/SimpleMaterial.h"
#include "../../../Scene/Objects/Object3D.h"

class RectangularPrism{
private:
	Vector3D basisVertices[8] = {Vector3D(-50.0000f,-20.0000f,50.0000f),Vector3D(-50.0000f,20.0000f,50.0000f),Vector3D(50.0000f,-20.0000f,50.0000f),Vector3D(50.0000f,20.0000f,50.0000f),Vector3D(50.0000f,-20.0000f,-50.0000f),Vector3D(50.0000f,20.0000f,-50.0000f),Vector3D(-50.0000f,-20.0000f,-50.0000f),Vector3D(-50.0000f,20.0000f,-50.0000f)};
	IndexGroup basisIndexes[12] = {IndexGroup(3,1,0),IndexGroup(5,3,2),IndexGroup(7,5,4),IndexGroup(1,7,6),IndexGroup(5,7,1),IndexGroup(2,0,6),IndexGroup(2,3,0),IndexGroup(4,5,2),IndexGroup(6,7,4),IndexGroup(0,1,6),IndexGroup(3,5,1),IndexGroup(4,2,6)};
	StaticTriangleGroup<8,12> triangleGroup = StaticTriangleGroup<8,12>(&basisVertices[0], &basisIndexes[0]);
	TriangleGroup<8,12> triangleGroupMemory = TriangleGroup<8,12>(&triangleGroup);
	SimpleMaterial simpleMaterial = SimpleMaterial(RGBColor(128, 128, 128));
	Object3D basisObj = Object3D(&triangleGroup, &triangleGroupMemory, &simpleMaterial);

public:
	RectangularPrism(){}

	Object3D* GetObject(){
		return &basisObj;
	}
};
