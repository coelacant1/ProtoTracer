#pragma once

#include "Utils/Morph.h"
#include "../../../Utils/Math/Rotation.h"
#include "../../../Scene/Materials/Static/SimpleMaterial.h"
#include "../../../Scene/Objects/Object3D.h"
#include "../../../Renderer/Utils/IndexGroup.h"

class BetaRear{
public:
    enum Morphs {
        Move1,
        Move2,
        Move3,
        Move4,
        Move5,
        HideAll
    };

private:
    Vector3D basisVertices[30] = {Vector3D(35.1173f,97.3756f,-65.0000f),Vector3D(45.1294f,85.4565f,-65.0000f),Vector3D(37.2243f,35.9136f,-65.0000f),Vector3D(12.3140f,19.4665f,-65.0000f),Vector3D(49.0064f,25.8081f,-65.0000f),Vector3D(58.5622f,7.0786f,-65.0000f),Vector3D(43.2223f,101.6665f,-65.0000f),Vector3D(80.8866f,99.2827f,-65.0000f),Vector3D(53.7111f,88.3171f,-65.0000f),Vector3D(68.4908f,83.5495f,-65.0000f),Vector3D(61.0067f,34.9704f,-65.0000f),Vector3D(71.9723f,24.0049f,-65.0000f),Vector3D(91.3754f,99.7594f,-65.0000f),Vector3D(103.2945f,90.7009f,-65.0000f),Vector3D(84.1957f,35.1965f,-65.0000f),Vector3D(108.8505f,47.3869f,-65.0000f),Vector3D(118.1553f,38.7117f,-65.0000f),Vector3D(125.7276f,26.0820f,-65.0000f),Vector3D(102.8177f,102.1432f,-65.0000f),Vector3D(134.2644f,99.3334f,-65.0000f),Vector3D(112.3530f,93.5615f,-65.0000f),Vector3D(122.8221f,87.8911f,-65.0000f),Vector3D(121.4033f,48.1674f,-65.0000f),Vector3D(133.3224f,40.5392f,-65.0000f),Vector3D(143.5457f,99.7594f,-65.0000f),Vector3D(152.0570f,93.8351f,-65.0000f),Vector3D(140.4541f,34.6771f,-65.0000f),Vector3D(152.0800f,54.2556f,-65.0000f),Vector3D(160.5519f,51.5981f,-65.0000f),Vector3D(164.5609f,42.7428f,-65.0000f)};
    IndexGroup basisIndexes[20] = {IndexGroup(2,1,0),IndexGroup(0,3,2),IndexGroup(3,4,2),IndexGroup(3,5,4),IndexGroup(8,7,6),IndexGroup(8,9,7),IndexGroup(10,7,9),IndexGroup(10,11,7),IndexGroup(14,13,12),IndexGroup(14,15,13),IndexGroup(14,16,15),IndexGroup(14,17,16),IndexGroup(20,19,18),IndexGroup(20,21,19),IndexGroup(21,22,19),IndexGroup(19,22,23),IndexGroup(26,25,24),IndexGroup(26,27,25),IndexGroup(26,28,27),IndexGroup(26,29,28)};
    StaticTriangleGroup<30,20> triangleGroup = StaticTriangleGroup<30,20>(&basisVertices[0], &basisIndexes[0]);
	TriangleGroup<30,20> triangleGroupMemory = TriangleGroup<30,20>(&triangleGroup);
	SimpleMaterial simpleMaterial = SimpleMaterial(RGBColor(128, 128, 128));
	Object3D basisObj = Object3D(&triangleGroup, &triangleGroupMemory, &simpleMaterial);

    static const byte morphCount = 6;
    int Move1Indexes[3] = {0,3,5};
    int Move2Indexes[3] = {6,7,11};
    int Move3Indexes[3] = {12,14,17};
    int Move4Indexes[3] = {18,19,23};
    int Move5Indexes[3] = {24,26,29};
    int HideAllIndexes[30] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29};

    Vector3D Move1Vectors[3] = {Vector3D(0.0869f,-22.7885f,0.0000f),Vector3D(9.3551f,8.8768f,0.0000f),Vector3D(-9.4420f,13.9117f,0.0000f)};
    Vector3D Move2Vectors[3] = {Vector3D(7.9449f,-9.5756f,0.0000f),Vector3D(-5.5720f,-8.7201f,0.0000f),Vector3D(-2.3729f,18.2956f,0.0000f)};
    Vector3D Move3Vectors[3] = {Vector3D(3.9075f,-19.8791f,0.0000f),Vector3D(7.0048f,7.9736f,0.0000f),Vector3D(-10.9122f,11.9055f,0.0000f)};
    Vector3D Move4Vectors[3] = {Vector3D(5.9576f,-6.1944f,0.0000f),Vector3D(-3.1147f,-5.3838f,0.0000f),Vector3D(-2.8429f,11.5782f,0.0000f)};
    Vector3D Move5Vectors[3] = {Vector3D(2.1996f,-14.9841f,0.0000f),Vector3D(3.3378f,8.9768f,0.0000f),Vector3D(-5.5374f,6.0073f,0.0000f)};
    Vector3D HideAllVectors[30] = {Vector3D(4.4416f,-52.1924f,0.0000f),Vector3D(-5.5704f,-40.2734f,0.0000f),Vector3D(2.3347f,9.2696f,0.0000f),Vector3D(27.2449f,25.7167f,0.0000f),Vector3D(-9.4475f,19.3751f,0.0000f),Vector3D(-19.0032f,38.1046f,0.0000f),Vector3D(19.9927f,-29.7013f,0.0000f),Vector3D(-17.6716f,-27.3175f,0.0000f),Vector3D(9.5039f,-16.3519f,0.0000f),Vector3D(-5.2758f,-11.5843f,0.0000f),Vector3D(2.2083f,36.9948f,0.0000f),Vector3D(-8.7573f,47.9603f,0.0000f),Vector3D(13.8911f,-43.4532f,0.0000f),Vector3D(1.9720f,-34.3947f,0.0000f),Vector3D(21.0708f,21.1098f,0.0000f),Vector3D(-3.5840f,8.9193f,0.0000f),Vector3D(-12.8888f,17.5946f,0.0000f),Vector3D(-20.4611f,30.2242f,0.0000f),Vector3D(18.3461f,-23.5372f,0.0000f),Vector3D(-13.1006f,-20.7274f,0.0000f),Vector3D(8.8108f,-14.9555f,0.0000f),Vector3D(-1.6583f,-9.2851f,0.0000f),Vector3D(-0.2395f,30.4386f,0.0000f),Vector3D(-12.1585f,38.0668f,0.0000f),Vector3D(8.6626f,-36.9480f,0.0000f),Vector3D(0.1513f,-31.0237f,0.0000f),Vector3D(11.7542f,28.1342f,0.0000f),Vector3D(0.1283f,8.5558f,0.0000f),Vector3D(-8.3436f,11.2133f,0.0000f),Vector3D(-12.3526f,20.0686f,0.0000f)};

    Morph morphs[6] = {
        Morph(3, Move1Indexes, Move1Vectors),
        Morph(3, Move2Indexes, Move2Vectors),
        Morph(3, Move3Indexes, Move3Vectors),
        Morph(3, Move4Indexes, Move4Vectors),
        Morph(3, Move5Indexes, Move5Vectors),
        Morph(30, HideAllIndexes, HideAllVectors)
    };

public:
    BetaRear(){}

    Object3D* GetObject(){
        return &basisObj;
    }

    void SetMorphWeight(Morphs morph, float weight){
        morphs[morph].Weight = weight;
    }

    float* GetMorphWeightReference(Morphs morph){
        return &morphs[morph].Weight;
    }

    void Reset(){
        for(int i = 0; i < morphCount; i++){
            morphs[i].Weight = 0.0f;
        }
    }

    void Update(){
        basisObj.ResetVertices();

        for(int i = 0; i < morphCount; i++){
            if(morphs[i].Weight > 0.0f){
                morphs[i].MorphObject3D(basisObj.GetTriangleGroup());
            }
        }

    }
};
