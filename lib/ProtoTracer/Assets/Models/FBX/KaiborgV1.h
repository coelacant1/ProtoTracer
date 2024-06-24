#pragma once

#include "Utils/Morph.h"
#include "../../../Utils/Math/Rotation.h"
#include "../../../Scene/Materials/Static/SimpleMaterial.h"
#include "../../../Scene/Objects/Object3D.h"
#include "../../../Renderer/Utils/IndexGroup.h"

class KaiborgV1{
public:
    enum Morphs {
        AddEyebrow,
        MouthFrown,
        EyeFrown,
        AltNose,
        POG,
        AlmondEyes,
        AngryEyes,
        HappySquint
    };

private:
    Vector3D basisVertices[38] = {Vector3D(107.9757f,136.2652f,0.2350f),Vector3D(101.6199f,144.7397f,0.2350f),Vector3D(75.1373f,127.5789f,0.2350f),Vector3D(133.8444f,140.6527f,0.2350f),Vector3D(114.7054f,126.9483f,0.2350f),Vector3D(142.0465f,81.8757f,0.2350f),Vector3D(101.1571f,96.1396f,0.2039f),Vector3D(123.1562f,82.9103f,0.2350f),Vector3D(133.5642f,102.9256f,0.2350f),Vector3D(87.2987f,70.7395f,0.2350f),Vector3D(92.8581f,85.4939f,0.2350f),Vector3D(117.0182f,103.1925f,0.2350f),Vector3D(109.6740f,90.1348f,0.2350f),Vector3D(129.3566f,92.8118f,0.2350f),Vector3D(146.7509f,95.2291f,0.2350f),Vector3D(104.3418f,79.8412f,0.2350f),Vector3D(160.4085f,75.6886f,0.2350f),Vector3D(31.0627f,19.4793f,0.2350f),Vector3D(55.8724f,40.2722f,0.2350f),Vector3D(59.6530f,33.4200f,0.2350f),Vector3D(94.2036f,14.9372f,0.2350f),Vector3D(93.5680f,22.9147f,0.2350f),Vector3D(113.5824f,24.9419f,0.2350f),Vector3D(128.8840f,29.8757f,0.1047f),Vector3D(146.1327f,33.4200f,0.2350f),Vector3D(140.9344f,37.9094f,0.1705f),Vector3D(18.7760f,22.0784f,0.2350f),Vector3D(152.5123f,46.4156f,0.2350f),Vector3D(26.3235f,28.5648f,0.2350f),Vector3D(12.5599f,34.5396f,0.2350f),Vector3D(109.0362f,32.4749f,0.1639f),Vector3D(130.7743f,23.0235f,0.2350f),Vector3D(12.6371f,52.0129f,0.2350f),Vector3D(18.9929f,66.8431f,0.2350f),Vector3D(24.5013f,61.7585f,0.2350f),Vector3D(37.6367f,74.0464f,0.2350f),Vector3D(42.0858f,65.9957f,0.2350f),Vector3D(58.9986f,65.2066f,0.2350f)};
    IndexGroup basisIndexes[33] = {IndexGroup(1,2,0),IndexGroup(0,3,1),IndexGroup(4,0,2),IndexGroup(4,3,0),IndexGroup(12,13,11),IndexGroup(13,14,8),IndexGroup(7,13,12),IndexGroup(6,12,11),IndexGroup(11,13,8),IndexGroup(6,10,12),IndexGroup(10,15,12),IndexGroup(10,9,15),IndexGroup(7,5,13),IndexGroup(15,7,12),IndexGroup(13,5,14),IndexGroup(5,16,14),IndexGroup(19,18,17),IndexGroup(19,20,18),IndexGroup(20,21,18),IndexGroup(20,22,21),IndexGroup(21,22,30),IndexGroup(25,23,24),IndexGroup(22,23,30),IndexGroup(18,28,17),IndexGroup(24,27,25),IndexGroup(28,26,17),IndexGroup(28,29,26),IndexGroup(22,31,23),IndexGroup(23,31,24),IndexGroup(34,33,32),IndexGroup(34,35,33),IndexGroup(36,35,34),IndexGroup(36,37,35)};
    TriangleGroup triangleGroup = TriangleGroup(&basisVertices[0], &basisIndexes[0], 38, 33);
    SimpleMaterial simpleMaterial = SimpleMaterial(RGBColor(128, 128, 128));
    Object3D basisObj = Object3D(&triangleGroup, &simpleMaterial);

    static const uint8_t morphCount = 8;
    int AddEyebrowIndexes[17] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};
    int MouthFrownIndexes[11] = {18,19,20,21,22,23,24,25,27,30,31};
    int EyeFrownIndexes[10] = {5,6,7,8,11,12,13,14,15,16};
    int AltNoseIndexes[6] = {32,33,34,35,36,37};
    int POGIndexes[15] = {17,18,19,20,21,22,23,24,25,26,27,28,29,30,31};
    int AlmondEyesIndexes[8] = {5,7,9,12,13,14,15,16};
    int AngryEyesIndexes[11] = {5,6,7,8,9,10,11,12,14,15,16};
    int HappySquintIndexes[7] = {5,7,9,12,13,15,16};

    Vector3D AddEyebrowVectors[17] = {Vector3D(23.7598f,-29.9088f,0.0000f),Vector3D(25.2438f,-32.6674f,0.0000f),Vector3D(31.4270f,-27.0813f,0.0000f),Vector3D(17.7199f,-31.3370f,0.0000f),Vector3D(22.1885f,-26.8760f,0.0000f),Vector3D(-3.5442f,-12.7593f,0.0000f),Vector3D(-3.5442f,-12.7593f,0.0000f),Vector3D(-3.5442f,-12.7593f,0.0000f),Vector3D(-3.5442f,-12.7593f,0.0000f),Vector3D(-3.5442f,-12.7593f,0.0000f),Vector3D(-3.5442f,-12.7593f,0.0000f),Vector3D(-3.5442f,-12.7593f,0.0000f),Vector3D(-3.5442f,-12.7593f,0.0000f),Vector3D(-3.5442f,-12.7593f,0.0000f),Vector3D(-3.5442f,-12.7593f,0.0000f),Vector3D(-3.5442f,-12.7593f,0.0000f),Vector3D(-3.5442f,-12.7593f,0.0000f)};
    Vector3D MouthFrownVectors[11] = {Vector3D(0.9451f,-9.4513f,0.0000f),Vector3D(-2.5991f,-8.5062f,0.0000f),Vector3D(-8.0336f,-2.3628f,0.0000f),Vector3D(-6.3797f,-4.2531f,0.0000f),Vector3D(-12.7593f,-7.0885f,0.0000f),Vector3D(-13.9407f,-15.5947f,0.0000f),Vector3D(-18.4301f,-22.4469f,0.0000f),Vector3D(-13.4682f,-21.0292f,0.0000f),Vector3D(-14.4133f,-39.2230f,0.0000f),Vector3D(-8.0336f,-9.9239f,0.0000f),Vector3D(-19.1389f,-15.3584f,0.0000f)};
    Vector3D EyeFrownVectors[10] = {Vector3D(-4.7257f,-9.6876f,0.0000f),Vector3D(-0.2363f,-1.6540f,0.0000f),Vector3D(-4.2531f,-12.2867f,0.0000f),Vector3D(-4.4440f,-15.1605f,0.0000f),Vector3D(-3.7805f,-11.8142f,0.0000f),Vector3D(-4.0168f,-7.0885f,0.0000f),Vector3D(-3.5442f,-10.8690f,0.0000f),Vector3D(2.5991f,-8.0336f,0.0000f),Vector3D(-3.7805f,-9.9239f,0.0000f),Vector3D(-2.8354f,0.0000f,0.0000f)};
    Vector3D AltNoseVectors[6] = {Vector3D(5.4345f,-3.3080f,0.0000f),Vector3D(-6.8522f,-2.3628f,0.0000f),Vector3D(-6.1434f,-1.8903f,0.0000f),Vector3D(-25.4960f,-9.5661f,0.0000f),Vector3D(-23.7278f,-6.1275f,0.0000f),Vector3D(-28.8266f,3.3080f,0.0000f)};
    Vector3D POGVectors[15] = {Vector3D(-3.3080f,-2.3628f,0.0000f),Vector3D(-27.4089f,-4.7257f,0.0000f),Vector3D(-24.1009f,-17.9575f,0.0000f),Vector3D(-50.5646f,5.1982f,0.0000f),Vector3D(-60.0160f,20.3204f,0.0000f),Vector3D(-66.6319f,-1.6540f,0.0000f),Vector3D(-80.1000f,6.8522f,0.0000f),Vector3D(-87.4248f,2.3628f,0.0000f),Vector3D(-89.3151f,0.7088f,0.0000f),Vector3D(5.6267f,-12.4503f,0.0000f),Vector3D(-95.9310f,-2.8354f,0.0000f),Vector3D(-7.7838f,16.4331f,0.0000f),Vector3D(-6.3642f,8.5206f,0.0000f),Vector3D(-66.6319f,7.7973f,0.0000f),Vector3D(-77.2646f,2.3628f,0.0000f)};
    Vector3D AlmondEyesVectors[8] = {Vector3D(-1.4177f,-1.4177f,0.0000f),Vector3D(-1.4177f,-9.2150f,0.0000f),Vector3D(0.4726f,2.1266f,0.0000f),Vector3D(0.2363f,-3.0717f,0.0000f),Vector3D(-0.4726f,-3.0717f,0.0000f),Vector3D(-1.4177f,3.5442f,0.0000f),Vector3D(0.7088f,-8.2699f,0.0000f),Vector3D(-5.1982f,15.5947f,0.0000f)};
    Vector3D AngryEyesVectors[11] = {Vector3D(2.8354f,7.0885f,0.0000f),Vector3D(-4.0168f,-5.4345f,0.0000f),Vector3D(7.0885f,-9.2150f,0.0000f),Vector3D(-12.0504f,3.3080f,0.0000f),Vector3D(1.6540f,-1.1814f,0.0000f),Vector3D(-1.1814f,-5.1982f,0.0000f),Vector3D(-6.6159f,-1.8903f,0.0000f),Vector3D(4.4894f,-4.7257f,0.0000f),Vector3D(-12.9956f,12.9956f,0.0000f),Vector3D(3.0717f,-12.0504f,0.0000f),Vector3D(-14.6496f,32.6071f,0.0000f)};
    Vector3D HappySquintVectors[7] = {Vector3D(-2.4735f,11.2681f,0.0000f),Vector3D(-3.0232f,13.1919f,0.0000f),Vector3D(1.9238f,3.2980f,0.0000f),Vector3D(-2.4735f,5.7715f,0.0000f),Vector3D(-3.2980f,7.1456f,0.0000f),Vector3D(-2.4735f,9.3443f,0.0000f),Vector3D(-1.3742f,2.7483f,0.0000f)};

    Morph morphs[8] = {
        Morph(17, AddEyebrowIndexes, AddEyebrowVectors),
        Morph(11, MouthFrownIndexes, MouthFrownVectors),
        Morph(10, EyeFrownIndexes, EyeFrownVectors),
        Morph(6, AltNoseIndexes, AltNoseVectors),
        Morph(15, POGIndexes, POGVectors),
        Morph(8, AlmondEyesIndexes, AlmondEyesVectors),
        Morph(11, AngryEyesIndexes, AngryEyesVectors),
        Morph(7, HappySquintIndexes, HappySquintVectors)
    };

public:
    KaiborgV1(){}

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
