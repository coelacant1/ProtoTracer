#pragma once

#include "Arduino.h"
#include "..\..\Math\Rotation.h"
#include "..\Morph.h"
#include "..\..\Materials\SimpleMaterial.h"
#include "..\..\Render\IndexGroup.h"
#include "..\..\Render\Object3D.h"

class StrawberryTears{
public:
    Vector3D basisVertices[12] = {Vector3D(-543.3240f,0.0000f,50.2576f),Vector3D(-478.6906f,0.0000f,513.4919f),Vector3D(74.3263f,0.0000f,760.3535f),Vector3D(560.1522f,0.0000f,523.4137f),Vector3D(657.1061f,0.0000f,12.2462f),Vector3D(3.0509f,0.0000f,-1058.5879f),Vector3D(-2465.9792f,0.0000f,-1456.0265f),Vector3D(-2401.3457f,0.0000f,-992.7921f),Vector3D(-1848.3289f,0.0000f,-745.9306f),Vector3D(-1362.5027f,0.0000f,-982.8703f),Vector3D(-1265.5489f,0.0000f,-1494.0378f),Vector3D(-1919.6042f,0.0000f,-2564.8718f)};
    IndexGroup basisIndexes[8] = {IndexGroup(4,0,1),IndexGroup(3,4,1),IndexGroup(3,1,2),IndexGroup(4,5,0),IndexGroup(10,6,7),IndexGroup(9,10,7),IndexGroup(9,7,8),IndexGroup(10,11,6)};
    TriangleGroup triangleGroup = TriangleGroup(&basisVertices[0], &basisIndexes[0], 12, 8);
    SimpleMaterial simpleMaterial = SimpleMaterial(RGBColor(128, 128, 128));
    Object3D basisObj = Object3D(&triangleGroup, &simpleMaterial);

public:
    StrawberryTears(){}

    Object3D* GetObject(){
        return &basisObj;
    }
    
    void Update(){
        basisObj.ResetVertices();
    }
};
