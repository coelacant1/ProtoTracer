#pragma once

#include "..\Render\Object3D.h"
#include "..\Materials\SimpleMaterial.h"

class DVD{
private:
	Vector3D basisVertices[42] = {Vector3D(6.2089f,68.0156f,0.0000f),Vector3D(4.7978f,62.3711f,0.0000f),Vector3D(22.3035f,62.2405f,0.0000f),Vector3D(43.1800f,68.0156f,0.0000f),Vector3D(35.8422f,62.3711f,0.0000f),Vector3D(24.5533f,58.4859f,0.0000f),Vector3D(27.4284f,44.2819f,0.0000f),Vector3D(12.0129f,48.2600f,0.0000f),Vector3D(0.2822f,42.6156f,0.0000f),Vector3D(4.7978f,59.8311f,0.0000f),Vector3D(14.1111f,59.8311f,0.0000f),Vector3D(44.2680f,37.6562f,0.0000f),Vector3D(48.5422f,51.3644f,0.0000f),Vector3D(47.2478f,37.6971f,0.0000f),Vector3D(66.6044f,62.3711f,0.0000f),Vector3D(60.6778f,68.0156f,0.0000f),Vector3D(84.6667f,68.0156f,0.0000f),Vector3D(83.9427f,62.3691f,0.0000f),Vector3D(96.2378f,62.9356f,0.0000f),Vector3D(88.0533f,58.1378f,0.0000f),Vector3D(89.2350f,43.9997f,0.0000f),Vector3D(73.3778f,48.2600f,0.0000f),Vector3D(62.3711f,42.6156f,0.0000f),Vector3D(66.8867f,59.8311f,0.0000f),Vector3D(75.9178f,59.8311f,0.0000f),Vector3D(0.0000f,30.7622f,0.0000f),Vector3D(4.7978f,27.0933f,0.0000f),Vector3D(8.6552f,35.1920f,0.0000f),Vector3D(19.8314f,24.0298f,0.0000f),Vector3D(22.2956f,36.6889f,0.0000f),Vector3D(37.8178f,22.8600f,0.0000f),Vector3D(34.3982f,31.0425f,0.0000f),Vector3D(46.7651f,32.8195f,0.0000f),Vector3D(58.0231f,31.0444f,0.0000f),Vector3D(46.3432f,28.5842f,0.0000f),Vector3D(53.3400f,22.8600f,0.0000f),Vector3D(55.3156f,37.8178f,0.0000f),Vector3D(72.5311f,36.9711f,0.0000f),Vector3D(89.2680f,34.2287f,0.0000f),Vector3D(96.4033f,30.2367f,0.0000f),Vector3D(89.2422f,26.3225f,0.0000f),Vector3D(71.9667f,23.4244f,0.0000f)};
	IndexGroup basisIndexes[41] = {IndexGroup(2,3,1),IndexGroup(3,4,1),IndexGroup(5,4,3),IndexGroup(6,5,3),IndexGroup(6,7,5),IndexGroup(8,7,6),IndexGroup(8,9,7),IndexGroup(8,10,9),IndexGroup(10,8,11),IndexGroup(12,13,5),IndexGroup(4,5,13),IndexGroup(14,13,12),IndexGroup(15,13,14),IndexGroup(15,16,13),IndexGroup(15,17,16),IndexGroup(18,17,15),IndexGroup(18,19,17),IndexGroup(20,19,18),IndexGroup(20,21,19),IndexGroup(22,21,20),IndexGroup(22,23,21),IndexGroup(24,23,22),IndexGroup(25,24,22),IndexGroup(27,28,26),IndexGroup(27,29,28),IndexGroup(29,30,28),IndexGroup(31,32,29),IndexGroup(30,29,32),IndexGroup(32,12,30),IndexGroup(33,12,32),IndexGroup(14,12,33),IndexGroup(34,14,33),IndexGroup(35,32,31),IndexGroup(36,35,31),IndexGroup(37,14,34),IndexGroup(34,38,37),IndexGroup(34,39,38),IndexGroup(40,39,34),IndexGroup(40,34,41),IndexGroup(41,34,42),IndexGroup(42,35,36)};
	TriangleGroup triangleGroup = TriangleGroup(&basisVertices[0], &basisIndexes[0], 42, 41);
	SimpleMaterial simpleMaterial = SimpleMaterial(RGBColor(128, 128, 128));
	Object3D basisObj = Object3D(&triangleGroup, &simpleMaterial);

public:
	DVD(){}

	Object3D* GetObject(){
		return &basisObj;
	}
};
