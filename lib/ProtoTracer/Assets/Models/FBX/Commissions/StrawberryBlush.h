#pragma once

#include "Arduino.h"
#include "..\..\Math\Rotation.h"
#include "..\Morph.h"
#include "..\..\Materials\SimpleMaterial.h"
#include "..\..\Render\IndexGroup.h"
#include "..\..\Render\Object3D.h"

class StrawberryBlush{
public:
    Vector3D basisVertices[77] = {Vector3D(455.6034f,0.0000f,2307.3390f),Vector3D(915.5548f,0.0000f,2307.3390f),Vector3D(1375.5066f,0.0000f,2307.3390f),Vector3D(1835.4582f,0.0000f,2307.3390f),Vector3D(-4.3483f,0.0000f,1847.3874f),Vector3D(455.6034f,0.0000f,1847.3874f),Vector3D(915.5548f,0.0000f,1847.3874f),Vector3D(1375.5066f,0.0000f,1847.3874f),Vector3D(1835.4582f,0.0000f,1847.3874f),Vector3D(2295.4097f,0.0000f,1847.3874f),Vector3D(-464.2999f,0.0000f,1387.4359f),Vector3D(-4.3483f,0.0000f,1387.4359f),Vector3D(455.6034f,0.0000f,1387.4359f),Vector3D(915.5548f,0.0000f,1387.4359f),Vector3D(1375.5066f,0.0000f,1387.4359f),Vector3D(1835.4582f,0.0000f,1387.4359f),Vector3D(2295.4097f,0.0000f,1387.4359f),Vector3D(-924.2514f,0.0000f,927.4842f),Vector3D(-464.2999f,0.0000f,927.4842f),Vector3D(-4.3483f,0.0000f,927.4842f),Vector3D(455.6034f,0.0000f,927.4842f),Vector3D(915.5548f,0.0000f,927.4842f),Vector3D(1375.5066f,0.0000f,927.4842f),Vector3D(1835.4582f,0.0000f,927.4842f),Vector3D(2295.4097f,0.0000f,927.4842f),Vector3D(-1384.2032f,0.0000f,467.5327f),Vector3D(-924.2514f,0.0000f,467.5327f),Vector3D(-464.2999f,0.0000f,467.5327f),Vector3D(-4.3483f,0.0000f,467.5327f),Vector3D(455.6034f,0.0000f,467.5327f),Vector3D(915.5548f,0.0000f,467.5327f),Vector3D(1375.5066f,0.0000f,467.5327f),Vector3D(1835.4582f,0.0000f,467.5327f),Vector3D(2295.4097f,0.0000f,467.5327f),Vector3D(-1844.1547f,0.0000f,7.5811f),Vector3D(-1384.2032f,0.0000f,7.5811f),Vector3D(-924.2514f,0.0000f,7.5811f),Vector3D(-464.2999f,0.0000f,7.5811f),Vector3D(-4.3483f,0.0000f,7.5811f),Vector3D(455.6034f,0.0000f,7.5811f),Vector3D(915.5548f,0.0000f,7.5811f),Vector3D(1375.5066f,0.0000f,7.5811f),Vector3D(1835.4582f,0.0000f,7.5811f),Vector3D(-2304.1063f,0.0000f,-452.3706f),Vector3D(-1844.1547f,0.0000f,-452.3706f),Vector3D(-1384.2032f,0.0000f,-452.3706f),Vector3D(-924.2514f,0.0000f,-452.3706f),Vector3D(-464.2999f,0.0000f,-452.3706f),Vector3D(-4.3483f,0.0000f,-452.3706f),Vector3D(455.6034f,0.0000f,-452.3706f),Vector3D(915.5548f,0.0000f,-452.3706f),Vector3D(1375.5066f,0.0000f,-452.3706f),Vector3D(-2304.1063f,0.0000f,-912.3221f),Vector3D(-1844.1547f,0.0000f,-912.3221f),Vector3D(-1384.2032f,0.0000f,-912.3221f),Vector3D(-924.2514f,0.0000f,-912.3221f),Vector3D(-464.2999f,0.0000f,-912.3221f),Vector3D(-4.3483f,0.0000f,-912.3221f),Vector3D(455.6034f,0.0000f,-912.3221f),Vector3D(915.5548f,0.0000f,-912.3221f),Vector3D(-2304.1063f,0.0000f,-1372.2739f),Vector3D(-1844.1547f,0.0000f,-1372.2739f),Vector3D(-1384.2032f,0.0000f,-1372.2739f),Vector3D(-924.2514f,0.0000f,-1372.2739f),Vector3D(-464.2999f,0.0000f,-1372.2739f),Vector3D(-4.3483f,0.0000f,-1372.2739f),Vector3D(455.6034f,0.0000f,-1372.2739f),Vector3D(-2304.1063f,0.0000f,-1832.2255f),Vector3D(-1844.1547f,0.0000f,-1832.2255f),Vector3D(-1384.2032f,0.0000f,-1832.2255f),Vector3D(-924.2514f,0.0000f,-1832.2255f),Vector3D(-464.2999f,0.0000f,-1832.2255f),Vector3D(-4.3483f,0.0000f,-1832.2255f),Vector3D(-1844.1547f,0.0000f,-2292.1770f),Vector3D(-1384.2032f,0.0000f,-2292.1770f),Vector3D(-924.2514f,0.0000f,-2292.1770f),Vector3D(-464.2999f,0.0000f,-2292.1770f)};
    IndexGroup basisIndexes[64] = {IndexGroup(68,73,69),IndexGroup(74,69,73),IndexGroup(68,67,61),IndexGroup(60,61,67),IndexGroup(62,61,54),IndexGroup(53,54,61),IndexGroup(70,69,63),IndexGroup(62,63,69),IndexGroup(76,75,71),IndexGroup(70,71,75),IndexGroup(72,71,65),IndexGroup(64,65,71),IndexGroup(64,63,56),IndexGroup(55,56,63),IndexGroup(66,65,58),IndexGroup(57,58,65),IndexGroup(59,58,50),IndexGroup(49,50,58),IndexGroup(57,56,48),IndexGroup(47,48,56),IndexGroup(55,54,46),IndexGroup(45,46,54),IndexGroup(53,52,44),IndexGroup(43,44,52),IndexGroup(45,44,35),IndexGroup(34,35,44),IndexGroup(47,46,37),IndexGroup(36,37,46),IndexGroup(49,48,39),IndexGroup(38,39,48),IndexGroup(51,50,41),IndexGroup(40,41,50),IndexGroup(42,41,32),IndexGroup(31,32,41),IndexGroup(40,39,30),IndexGroup(29,30,39),IndexGroup(38,37,28),IndexGroup(27,28,37),IndexGroup(36,35,26),IndexGroup(25,26,35),IndexGroup(27,26,18),IndexGroup(17,18,26),IndexGroup(29,28,20),IndexGroup(19,20,28),IndexGroup(19,18,11),IndexGroup(10,11,18),IndexGroup(12,11,5),IndexGroup(4,5,11),IndexGroup(21,20,13),IndexGroup(12,13,20),IndexGroup(31,30,22),IndexGroup(21,22,30),IndexGroup(33,32,24),IndexGroup(23,24,32),IndexGroup(23,22,15),IndexGroup(14,15,22),IndexGroup(14,13,7),IndexGroup(6,7,13),IndexGroup(6,5,1),IndexGroup(5,0,1),IndexGroup(8,7,3),IndexGroup(7,2,3),IndexGroup(16,15,9),IndexGroup(8,9,15)};
    TriangleGroup triangleGroup = TriangleGroup(&basisVertices[0], &basisIndexes[0], 77, 64);
    SimpleMaterial simpleMaterial = SimpleMaterial(RGBColor(128, 128, 128));
    Object3D basisObj = Object3D(&triangleGroup, &simpleMaterial);
    
public:
    StrawberryBlush(){}

    Object3D* GetObject(){
        return &basisObj;
    }

    void Update(){
        basisObj.ResetVertices();
    }
};
