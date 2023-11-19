#pragma once

#include "Arduino.h"
#include "..\..\Math\Rotation.h"
#include "..\Morph.h"
#include "..\..\Materials\SimpleMaterial.h"
#include "..\..\Render\IndexGroup.h"
#include "..\..\Render\Object3D.h"

class XenraxZZZ{
public:
    Vector3D basisVertices[24] = {Vector3D(130.1996f,0.0000f,-46.5875f),Vector3D(139.5820f,0.0000f,-59.4288f),Vector3D(126.2867f,0.0000f,-59.4288f),Vector3D(126.2867f,0.0000f,-57.5264f),Vector3D(135.6691f,0.0000f,-57.5264f),Vector3D(126.2867f,0.0000f,-44.6852f),Vector3D(138.9982f,0.0000f,-44.6852f),Vector3D(138.9982f,0.0000f,-46.5875f),Vector3D(150.4181f,0.0000f,-62.7268f),Vector3D(159.8004f,0.0000f,-75.5681f),Vector3D(146.5052f,0.0000f,-75.5681f),Vector3D(146.5052f,0.0000f,-73.6657f),Vector3D(155.8875f,0.0000f,-73.6657f),Vector3D(146.5052f,0.0000f,-60.8245f),Vector3D(159.2167f,0.0000f,-60.8245f),Vector3D(159.2167f,0.0000f,-62.7268f),Vector3D(155.5614f,0.0000f,-40.0254f),Vector3D(164.9437f,0.0000f,-52.8666f),Vector3D(151.6485f,0.0000f,-52.8666f),Vector3D(151.6485f,0.0000f,-50.9643f),Vector3D(161.0308f,0.0000f,-50.9643f),Vector3D(151.6485f,0.0000f,-38.1230f),Vector3D(164.3600f,0.0000f,-38.1230f),Vector3D(164.3600f,0.0000f,-40.0254f)};
    IndexGroup basisIndexes[18] = {IndexGroup(7,5,6),IndexGroup(7,0,5),IndexGroup(0,4,5),IndexGroup(1,4,0),IndexGroup(1,3,4),IndexGroup(1,2,3),IndexGroup(15,13,14),IndexGroup(15,8,13),IndexGroup(8,12,13),IndexGroup(9,12,8),IndexGroup(9,11,12),IndexGroup(9,10,11),IndexGroup(23,21,22),IndexGroup(23,16,21),IndexGroup(16,20,21),IndexGroup(17,20,16),IndexGroup(17,19,20),IndexGroup(17,18,19)};
    TriangleGroup triangleGroup = TriangleGroup(&basisVertices[0], &basisIndexes[0], 24, 18);
    SimpleMaterial simpleMaterial = SimpleMaterial(RGBColor(128, 128, 128));
    Object3D basisObj = Object3D(&triangleGroup, &simpleMaterial);

    static const byte morphCount = 0;


public:
    XenraxZZZ(){}

    Object3D* GetObject(){
        return &basisObj;
    }

    void Reset(){ }

    void Update(){
        basisObj.ResetVertices();
    }
};
