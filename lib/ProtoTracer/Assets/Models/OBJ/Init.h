#pragma once

#include "../../../Scene/Materials/Static/SimpleMaterial.h"
#include "../../../Scene/Materials/Static/UVMap.h"
#include "../../../Scene/Objects/Object3D.h"
#include "../../../Renderer/Utils/IndexGroup.h"

class Init {
private:
	Vector3D basisVertices[64] = {Vector3D(9.0000f,36.0000f,0.0000f),Vector3D(9.0038f,4.4962f,0.0000f),Vector3D(0.0037f,4.4962f,0.0000f),Vector3D(0.0037f,0.0037f,0.0000f),Vector3D(26.9962f,0.0037f,0.0000f),Vector3D(26.9962f,4.4962f,0.0000f),Vector3D(17.9962f,4.4962f,0.0000f),Vector3D(17.9962f,36.0037f,0.0000f),Vector3D(26.9962f,36.0037f,0.0000f),Vector3D(26.9962f,40.4963f,0.0000f),Vector3D(0.0037f,40.4963f,0.0000f),Vector3D(0.0037f,36.0037f,0.0000f),Vector3D(40.4400f,27.0000f,0.0000f),Vector3D(49.5037f,27.0038f,0.0000f),Vector3D(49.5037f,0.0037f,0.0000f),Vector3D(58.4963f,0.0037f,0.0000f),Vector3D(58.4963f,27.0038f,0.0000f),Vector3D(54.0000f,27.0038f,0.0000f),Vector3D(54.0000f,31.4962f,0.0000f),Vector3D(31.5038f,31.4962f,0.0000f),Vector3D(31.5038f,0.0037f,0.0000f),Vector3D(40.4963f,0.0037f,0.0000f),Vector3D(72.0000f,27.0000f,0.0000f),Vector3D(72.0037f,4.4962f,0.0000f),Vector3D(63.0037f,4.4962f,0.0000f),Vector3D(63.0037f,0.0037f,0.0000f),Vector3D(89.9963f,0.0037f,0.0000f),Vector3D(89.9963f,4.4962f,0.0000f),Vector3D(80.9963f,4.4962f,0.0000f),Vector3D(80.9963f,31.4962f,0.0000f),Vector3D(63.0037f,31.4962f,0.0000f),Vector3D(63.0037f,27.0038f,0.0000f),Vector3D(80.9400f,44.9400f,0.0000f),Vector3D(72.0037f,44.9963f,0.0000f),Vector3D(72.0037f,36.0037f,0.0000f),Vector3D(80.9963f,36.0037f,0.0000f),Vector3D(94.5000f,27.0000f,0.0000f),Vector3D(103.5037f,27.0038f,0.0000f),Vector3D(103.5037f,4.4962f,0.0000f),Vector3D(108.0000f,4.4962f,0.0000f),Vector3D(108.0000f,0.0037f,0.0000f),Vector3D(121.4963f,0.0037f,0.0000f),Vector3D(121.4963f,4.4962f,0.0000f),Vector3D(112.4963f,4.4962f,0.0000f),Vector3D(112.4963f,27.0038f,0.0000f),Vector3D(121.4963f,27.0038f,0.0000f),Vector3D(121.4963f,31.4962f,0.0000f),Vector3D(112.4963f,31.4962f,0.0000f),Vector3D(112.4963f,40.4963f,0.0000f),Vector3D(103.5037f,40.4963f,0.0000f),Vector3D(103.5037f,31.4962f,0.0000f),Vector3D(94.5037f,31.4962f,0.0000f),Vector3D(134.9400f,0.0000f,0.0000f),Vector3D(134.9963f,8.9962f,0.0000f),Vector3D(126.0037f,8.9962f,0.0000f),Vector3D(126.0037f,0.0037f,0.0000f),Vector3D(148.4400f,0.0000f,0.0000f),Vector3D(148.4963f,8.9962f,0.0000f),Vector3D(139.5037f,8.9962f,0.0000f),Vector3D(139.5037f,0.0037f,0.0000f),Vector3D(161.9400f,0.0000f,0.0000f),Vector3D(161.9963f,8.9962f,0.0000f),Vector3D(153.0037f,8.9962f,0.0000f),Vector3D(153.0037f,0.0037f,0.0000f)};
	IndexGroup basisIndexes[48] = {IndexGroup(6,1,0),IndexGroup(18,13,12),IndexGroup(28,23,22),IndexGroup(51,50,37),IndexGroup(34,33,32),IndexGroup(54,53,52),IndexGroup(58,57,56),IndexGroup(62,61,60),IndexGroup(35,34,32),IndexGroup(55,54,52),IndexGroup(59,58,56),IndexGroup(63,62,60),IndexGroup(3,2,1),IndexGroup(1,6,4),IndexGroup(6,5,4),IndexGroup(9,8,7),IndexGroup(7,0,10),IndexGroup(0,11,10),IndexGroup(13,18,17),IndexGroup(15,14,17),IndexGroup(20,19,12),IndexGroup(25,24,23),IndexGroup(25,23,28),IndexGroup(28,27,26),IndexGroup(30,29,22),IndexGroup(39,38,37),IndexGroup(43,40,39),IndexGroup(41,40,43),IndexGroup(39,37,44),IndexGroup(45,44,47),IndexGroup(47,50,49),IndexGroup(44,37,50),IndexGroup(3,1,4),IndexGroup(9,7,10),IndexGroup(14,13,17),IndexGroup(16,15,17),IndexGroup(21,20,12),IndexGroup(26,25,28),IndexGroup(31,30,22),IndexGroup(42,41,43),IndexGroup(43,39,44),IndexGroup(46,45,47),IndexGroup(48,47,49),IndexGroup(47,44,50),IndexGroup(7,6,0),IndexGroup(19,18,12),IndexGroup(29,28,22),IndexGroup(36,51,37)};
	TriangleGroup triangleGroup = TriangleGroup(&basisVertices[0], &basisIndexes[0], 64, 48);
	SimpleMaterial simpleMaterial = SimpleMaterial(RGBColor(128, 128, 128));
	Object3D basisObj = Object3D(&triangleGroup, &simpleMaterial);

public:
	Init(){}

	Object3D* GetObject(){
		return &basisObj;
	}
};
