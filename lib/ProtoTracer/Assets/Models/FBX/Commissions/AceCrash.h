#pragma once

#include "Arduino.h"
#include "..\..\Math\Rotation.h"
#include "..\Morph.h"
#include "..\..\Materials\SimpleMaterial.h"
#include "..\..\Render\IndexGroup.h"
#include "..\..\Render\Object3D.h"

class AceCrash{
public:
    Vector3D basisVertices[22] = {Vector3D(-119.6711f,0.0000f,-74.1227f),Vector3D(-119.6711f,0.0000f,-64.1227f),Vector3D(-109.6711f,0.0000f,-64.1227f),Vector3D(-109.6711f,0.0000f,-74.1227f),Vector3D(-119.6711f,0.0000f,-48.1227f),Vector3D(-119.6711f,0.0000f,-38.1227f),Vector3D(-109.6711f,0.0000f,-38.1227f),Vector3D(-109.6711f,0.0000f,-48.1227f),Vector3D(-92.7473f,0.0000f,-96.7122f),Vector3D(-98.1158f,0.0000f,-87.4205f),Vector3D(-101.7292f,0.0000f,-74.7219f),Vector3D(-102.8649f,0.0000f,-59.1227f),Vector3D(-102.5552f,0.0000f,-42.3042f),Vector3D(-99.8709f,0.0000f,-27.0245f),Vector3D(-93.8799f,0.0000f,-12.3855f),Vector3D(-91.1629f,0.0596f,-88.0086f),Vector3D(-94.2060f,0.0596f,-80.7136f),Vector3D(-96.2542f,0.0596f,-70.7439f),Vector3D(-96.8979f,0.0596f,-59.1227f),Vector3D(-96.7224f,0.0596f,-45.2926f),Vector3D(-95.2008f,0.0596f,-33.2965f),Vector3D(-91.4622f,0.0596f,-21.8598f)};
    IndexGroup basisIndexes[16] = {IndexGroup(15,8,9),IndexGroup(15,9,16),IndexGroup(9,10,16),IndexGroup(16,10,17),IndexGroup(10,11,17),IndexGroup(17,11,18),IndexGroup(11,12,18),IndexGroup(18,12,19),IndexGroup(12,13,19),IndexGroup(19,13,20),IndexGroup(13,14,20),IndexGroup(20,14,21),IndexGroup(5,6,4),IndexGroup(6,7,4),IndexGroup(1,2,0),IndexGroup(2,3,0)};
    TriangleGroup triangleGroup = TriangleGroup(&basisVertices[0], &basisIndexes[0], 22, 16);
    SimpleMaterial simpleMaterial = SimpleMaterial(RGBColor(128, 128, 128));
    Object3D basisObj = Object3D(&triangleGroup, &simpleMaterial);

    static const byte morphCount = 0;

public:
    AceCrash(){}

    Object3D* GetObject(){
        return &basisObj;
    }

    void Reset(){}

    void Update(){
        basisObj.ResetVertices();
    }
};
