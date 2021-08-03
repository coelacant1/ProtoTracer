#pragma once

#include "..\Render\Object3D.h"
#include "..\Materials\SimpleMaterial.h"

class Cube{
private:
	Vector3D basisVertices[33] = {Vector3D(-100.0000f,-100.0000f,-100.0000f),Vector3D(-100.0000f,100.0000f,-100.0000f),Vector3D(100.0000f,-100.0000f,-100.0000f),Vector3D(100.0000f,100.0000f,-100.0000f),Vector3D(100.0000f,-100.0000f,100.0000f),Vector3D(100.0000f,100.0000f,100.0000f),Vector3D(-100.0000f,-100.0000f,100.0000f),Vector3D(-100.0000f,100.0000f,100.0000f),Vector3D(75.0000f,-100.0000f,-75.0000f),Vector3D(75.0000f,75.0000f,-100.0000f),Vector3D(-100.0000f,-75.0000f,75.0000f),Vector3D(-75.0000f,-75.0000f,-100.0000f),Vector3D(100.0000f,75.0000f,75.0000f),Vector3D(-100.0000f,75.0000f,-75.0000f),Vector3D(100.0000f,-75.0000f,-75.0000f),Vector3D(75.0000f,100.0000f,75.0000f),Vector3D(-75.0000f,75.0000f,100.0000f),Vector3D(75.0000f,-75.0000f,100.0000f),Vector3D(-75.0000f,100.0000f,-75.0000f),Vector3D(-75.0000f,-100.0000f,75.0000f),Vector3D(-75.0000f,75.0000f,-100.0000f),Vector3D(100.0000f,45.0000f,-75.0000f),Vector3D(-100.0000f,75.0000f,75.0000f),Vector3D(100.0000f,75.0000f,-75.0000f),Vector3D(75.0000f,-75.0000f,-100.0000f),Vector3D(75.0000f,75.0000f,100.0000f),Vector3D(-100.0000f,-75.0000f,-75.0000f),Vector3D(75.0000f,100.0000f,-75.0000f),Vector3D(100.0000f,-75.0000f,75.0000f),Vector3D(-75.0000f,-75.0000f,100.0000f),Vector3D(-75.0000f,100.0000f,75.0000f),Vector3D(75.0000f,-100.0000f,75.0000f),Vector3D(-75.0000f,-100.0000f,-75.0000f)};
	IndexGroup basisIndexes[49] = {IndexGroup(20,11,0),IndexGroup(19,31,4),IndexGroup(18,27,3),IndexGroup(26,13,1),IndexGroup(5,4,28),IndexGroup(29,16,7),IndexGroup(2,3,21),IndexGroup(18,3,1),IndexGroup(17,29,6),IndexGroup(30,1,7),IndexGroup(19,4,6),IndexGroup(22,6,7),IndexGroup(2,21,14),IndexGroup(24,3,2),IndexGroup(9,20,1),IndexGroup(13,22,7),IndexGroup(8,32,0),IndexGroup(25,17,4),IndexGroup(29,7,6),IndexGroup(32,6,0),IndexGroup(17,6,4),IndexGroup(32,19,6),IndexGroup(13,7,1),IndexGroup(16,5,7),IndexGroup(15,7,5),IndexGroup(9,1,3),IndexGroup(26,1,0),IndexGroup(30,18,1),IndexGroup(27,5,3),IndexGroup(22,10,6),IndexGroup(15,30,7),IndexGroup(23,21,3),IndexGroup(31,2,4),IndexGroup(3,5,12),IndexGroup(10,0,6),IndexGroup(3,12,23),IndexGroup(8,0,2),IndexGroup(24,9,3),IndexGroup(2,14,28),IndexGroup(31,8,2),IndexGroup(16,25,5),IndexGroup(5,28,12),IndexGroup(11,2,0),IndexGroup(25,4,5),IndexGroup(11,24,2),IndexGroup(2,28,4),IndexGroup(20,0,1),IndexGroup(10,26,0),IndexGroup(27,15,5)};
	TriangleGroup triangleGroup = TriangleGroup(&basisVertices[0], &basisIndexes[0], 33, 49);
	SimpleMaterial simpleMaterial = SimpleMaterial(RGBColor(128, 128, 128));
	Object3D basisObj = Object3D(&triangleGroup, &simpleMaterial);

public:
	Cube(){}

	Object3D* GetObject(){
		return &basisObj;
	}
};
