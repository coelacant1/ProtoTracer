#pragma once

#include "Arduino.h"
#include "..\..\Math\Rotation.h"
#include "..\Morph.h"
#include "..\..\Materials\SimpleMaterial.h"
#include "..\..\Render\IndexGroup.h"
#include "..\..\Render\Object3D.h"

class XenraxHearts{
public:
    Vector3D basisVertices[40] = {Vector3D(67.2999f,0.0000f,-62.5925f),Vector3D(67.9705f,0.0000f,-63.9210f),Vector3D(70.4875f,0.0000f,-64.5360f),Vector3D(72.4616f,0.0000f,-62.2031f),Vector3D(71.1099f,0.0000f,-57.7166f),Vector3D(67.2999f,0.0000f,-55.4267f),Vector3D(66.6292f,0.0000f,-63.9210f),Vector3D(64.1122f,0.0000f,-64.5360f),Vector3D(62.1381f,0.0000f,-62.2031f),Vector3D(63.4898f,0.0000f,-57.7166f),Vector3D(64.4801f,0.0000f,-85.0635f),Vector3D(65.3985f,0.0000f,-86.8828f),Vector3D(68.8454f,0.0000f,-87.7249f),Vector3D(71.5487f,0.0000f,-84.5302f),Vector3D(69.6977f,0.0000f,-78.3862f),Vector3D(64.4801f,0.0000f,-75.2504f),Vector3D(63.5616f,0.0000f,-86.8828f),Vector3D(60.1148f,0.0000f,-87.7249f),Vector3D(57.4115f,0.0000f,-84.5302f),Vector3D(59.2625f,0.0000f,-78.3862f),Vector3D(134.0936f,0.0000f,-63.9429f),Vector3D(134.9227f,0.0000f,-65.5854f),Vector3D(138.0346f,0.0000f,-66.3456f),Vector3D(140.4752f,0.0000f,-63.4615f),Vector3D(138.8041f,0.0000f,-57.9146f),Vector3D(134.0936f,0.0000f,-55.0835f),Vector3D(133.2644f,0.0000f,-65.5854f),Vector3D(130.1525f,0.0000f,-66.3456f),Vector3D(127.7120f,0.0000f,-63.4615f),Vector3D(129.3831f,0.0000f,-57.9146f),Vector3D(145.9014f,0.0000f,-84.9379f),Vector3D(146.5324f,0.0000f,-86.1878f),Vector3D(148.9004f,0.0000f,-86.7663f),Vector3D(150.7576f,0.0000f,-84.5716f),Vector3D(149.4859f,0.0000f,-80.3507f),Vector3D(145.9014f,0.0000f,-78.1964f),Vector3D(145.2705f,0.0000f,-86.1878f),Vector3D(142.9025f,0.0000f,-86.7663f),Vector3D(141.0454f,0.0000f,-84.5716f),Vector3D(142.3170f,0.0000f,-80.3507f)};
    IndexGroup basisIndexes[32] = {IndexGroup(1,2,0),IndexGroup(0,2,3),IndexGroup(3,4,0),IndexGroup(4,5,9),IndexGroup(4,9,0),IndexGroup(9,8,0),IndexGroup(0,8,7),IndexGroup(7,6,0),IndexGroup(11,12,10),IndexGroup(10,12,13),IndexGroup(13,14,10),IndexGroup(14,15,19),IndexGroup(14,19,10),IndexGroup(19,18,10),IndexGroup(10,18,17),IndexGroup(17,16,10),IndexGroup(21,22,20),IndexGroup(20,22,23),IndexGroup(23,24,20),IndexGroup(24,25,29),IndexGroup(24,29,20),IndexGroup(29,28,20),IndexGroup(20,28,27),IndexGroup(27,26,20),IndexGroup(31,32,30),IndexGroup(30,32,33),IndexGroup(33,34,30),IndexGroup(34,35,39),IndexGroup(34,39,30),IndexGroup(39,38,30),IndexGroup(30,38,37),IndexGroup(37,36,30)};
    TriangleGroup triangleGroup = TriangleGroup(&basisVertices[0], &basisIndexes[0], 40, 32);
    SimpleMaterial simpleMaterial = SimpleMaterial(RGBColor(128, 128, 128));
    Object3D basisObj = Object3D(&triangleGroup, &simpleMaterial);

    static const byte morphCount = 0;

public:
    XenraxHearts(){}

    Object3D* GetObject(){
        return &basisObj;
    }

    void Reset(){}

    void Update(){
        basisObj.ResetVertices();
    }
};
