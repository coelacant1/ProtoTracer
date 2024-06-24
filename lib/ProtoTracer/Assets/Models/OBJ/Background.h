#pragma once

#include "../../../Scene/Materials/Static/SimpleMaterial.h"
#include "../../../Scene/Objects/Object3D.h"

class Background{
private:
	Vector3D basisVertices[3] = {Vector3D(10000.0000f,-10000.0000f,1200.0000f),Vector3D(-10000.0000f,-10000.0000f,1200.0000f),Vector3D(0.0000f,10000.0000f,1200.0000f)};
	IndexGroup basisIndexes[1] = {IndexGroup(0,1,2)};
	StaticTriangleGroup<3,1> triangleGroup = StaticTriangleGroup<3,1>(&basisVertices[0], &basisIndexes[0]);
	TriangleGroup<3,1> triangleGroupMemory = TriangleGroup<3,1>(&triangleGroup);
	SimpleMaterial simpleMaterial = SimpleMaterial(RGBColor(128, 128, 128));
	Object3D basisObj = Object3D(&triangleGroup, &triangleGroupMemory, &simpleMaterial);

public:
	Background(){}

	Object3D* GetObject(){
		return &basisObj;
	}
};
