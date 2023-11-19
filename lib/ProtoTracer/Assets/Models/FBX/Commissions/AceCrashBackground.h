#pragma once

#include "Arduino.h"
#include "..\..\Math\Rotation.h"
#include "..\Morph.h"
#include "..\..\Materials\SimpleMaterial.h"
#include "..\..\Render\IndexGroup.h"
#include "..\..\Render\Object3D.h"

class AceCrashBackground{
public:
    Vector3D basisVertices[36] = {Vector3D(-165.5322f,0.0000f,-85.9751f),Vector3D(-144.2645f,0.0000f,-108.3784f),Vector3D(-136.0053f,0.0000f,-108.5849f),Vector3D(-10.6706f,0.0000f,-60.0616f),Vector3D(-10.6707f,0.0000f,-43.0269f),Vector3D(-29.3573f,0.0000f,-5.8601f),Vector3D(-67.3500f,0.0000f,-5.9633f),Vector3D(-71.5829f,0.0000f,-12.8805f),Vector3D(-82.9394f,0.0000f,-13.0870f),Vector3D(-95.6711f,0.0000f,-6.0666f),Vector3D(-133.3210f,0.0000f,-6.2731f),Vector3D(-165.4290f,0.0000f,-74.8251f),Vector3D(-207.3247f,0.0000f,-109.9052f),Vector3D(-173.8626f,0.0000f,-145.1540f),Vector3D(-160.8676f,0.0000f,-145.4789f),Vector3D(36.3311f,0.0000f,-69.1334f),Vector3D(36.3310f,0.0000f,-42.3313f),Vector3D(6.9299f,0.0000f,16.1461f),Vector3D(-52.8469f,0.0000f,15.9836f),Vector3D(-59.5069f,0.0000f,5.1003f),Vector3D(-83.7100f,0.0000f,4.9379f),Vector3D(-89.3953f,0.0000f,15.8212f),Vector3D(-156.6443f,0.0000f,15.4963f),Vector3D(-207.1622f,0.0000f,-92.3620f),Vector3D(-98.6711f,0.0000f,-95.1227f),Vector3D(-103.7941f,0.0000f,-85.1492f),Vector3D(-106.4783f,0.0000f,-78.1227f),Vector3D(-123.6163f,0.0000f,-78.1227f),Vector3D(-123.6711f,0.0000f,-33.1227f),Vector3D(-107.3043f,0.0000f,-33.1227f),Vector3D(-102.1422f,0.0000f,-18.1458f),Vector3D(-89.9598f,0.0000f,-27.7472f),Vector3D(-92.8505f,0.0000f,-44.3690f),Vector3D(-92.1278f,0.0000f,-63.9848f),Vector3D(-89.6711f,0.0000f,-80.1227f),Vector3D(-85.3139f,0.0000f,-89.8983f)};
    IndexGroup basisIndexes[38] = {IndexGroup(10,21,22),IndexGroup(10,22,11),IndexGroup(22,23,11),IndexGroup(11,23,0),IndexGroup(23,12,0),IndexGroup(13,0,12),IndexGroup(0,13,1),IndexGroup(13,14,1),IndexGroup(1,14,2),IndexGroup(14,15,2),IndexGroup(4,3,15),IndexGroup(15,16,4),IndexGroup(17,4,16),IndexGroup(4,17,5),IndexGroup(17,18,5),IndexGroup(19,5,18),IndexGroup(5,19,6),IndexGroup(19,20,6),IndexGroup(6,20,7),IndexGroup(2,15,24),IndexGroup(10,9,20),IndexGroup(20,21,10),IndexGroup(15,3,35),IndexGroup(24,15,35),IndexGroup(25,24,35),IndexGroup(35,34,25),IndexGroup(34,33,25),IndexGroup(25,33,26),IndexGroup(27,26,33),IndexGroup(28,27,33),IndexGroup(29,28,33),IndexGroup(33,32,29),IndexGroup(29,32,30),IndexGroup(32,31,30),IndexGroup(30,31,9),IndexGroup(31,8,9),IndexGroup(9,8,20),IndexGroup(20,8,7)};
    TriangleGroup triangleGroup = TriangleGroup(&basisVertices[0], &basisIndexes[0], 36, 38);
    SimpleMaterial simpleMaterial = SimpleMaterial(RGBColor(128, 128, 128));
    Object3D basisObj = Object3D(&triangleGroup, &simpleMaterial);

    static const byte morphCount = 0;

public:
    AceCrashBackground(){}

    Object3D* GetObject(){
        return &basisObj;
    }
    
    void Reset(){}

    void Update(){
        basisObj.ResetVertices();
    }
};
