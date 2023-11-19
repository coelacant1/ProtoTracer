#pragma once

#include "Arduino.h"
#include "..\..\Math\Rotation.h"
#include "..\Morph.h"
#include "..\..\Materials\SimpleMaterial.h"
#include "..\..\Render\IndexGroup.h"
#include "..\..\Render\Object3D.h"

class StrawberryStinky{
public:
    Vector3D basisVertices[23] = {Vector3D(4988.0377f,0.0000f,534.3175f),Vector3D(5447.9901f,0.0000f,534.3175f),Vector3D(4528.0862f,0.0000f,74.3659f),Vector3D(4988.0377f,0.0000f,74.3659f),Vector3D(5447.9901f,0.0000f,74.3659f),Vector3D(5907.9413f,0.0000f,74.3659f),Vector3D(4528.0862f,0.0000f,-385.5856f),Vector3D(4988.0377f,0.0000f,-385.5856f),Vector3D(5447.9901f,0.0000f,-385.5856f),Vector3D(5907.9413f,0.0000f,-385.5856f),Vector3D(4528.0862f,0.0000f,-845.5372f),Vector3D(4988.0377f,0.0000f,-845.5372f),Vector3D(5447.9901f,0.0000f,-845.5372f),Vector3D(5907.9413f,0.0000f,-845.5372f),Vector3D(4528.0862f,0.0000f,-1305.4889f),Vector3D(4988.0377f,0.0000f,-1305.4889f),Vector3D(5447.9901f,0.0000f,-1305.4889f),Vector3D(5907.9413f,0.0000f,-1305.4889f),Vector3D(4528.0862f,0.0000f,-1765.4404f),Vector3D(4988.0377f,0.0000f,-1765.4404f),Vector3D(5447.9901f,0.0000f,-1765.4404f),Vector3D(4528.0862f,0.0000f,-2225.3922f),Vector3D(4988.0377f,0.0000f,-2225.3922f)};
    IndexGroup basisIndexes[16] = {IndexGroup(10,11,14),IndexGroup(15,14,11),IndexGroup(15,16,19),IndexGroup(20,19,16),IndexGroup(22,19,21),IndexGroup(18,21,19),IndexGroup(12,13,16),IndexGroup(17,16,13),IndexGroup(12,11,8),IndexGroup(7,8,11),IndexGroup(7,6,3),IndexGroup(2,3,6),IndexGroup(4,5,8),IndexGroup(9,8,5),IndexGroup(4,3,1),IndexGroup(3,0,1)};
    TriangleGroup triangleGroup = TriangleGroup(&basisVertices[0], &basisIndexes[0], 23, 16);
    SimpleMaterial simpleMaterial = SimpleMaterial(RGBColor(128, 128, 128));
    Object3D basisObj = Object3D(&triangleGroup, &simpleMaterial);
public:
    StrawberryStinky(){}

    Object3D* GetObject(){
        return &basisObj;
    }
    
    void Update(){
        basisObj.ResetVertices();
    }
};
