#pragma once

#include "..\..\Math\Rotation.h"
#include "..\Morph.h"
#include "..\..\Materials\SimpleMaterial.h"
#include "..\..\Render\IndexGroup.h"
#include "..\..\Render\Object3D.h"

class SageSchloSideDisplay{
public:
    enum Morphs {
        Exclamation,
        Dizzy,
        Battery,
        BatteryFull
    };

private:
    Vector3D basisVertices[41] = {Vector3D(47.3332f,0.0000f,-49.9636f),Vector3D(49.2712f,0.0000f,-49.9636f),Vector3D(51.5074f,0.0000f,-49.9636f),Vector3D(54.0417f,0.0000f,-49.9636f),Vector3D(56.7251f,0.0000f,-49.9636f),Vector3D(59.9650f,0.0000f,-49.9636f),Vector3D(60.0003f,0.0000f,-34.2866f),Vector3D(64.1423f,0.0000f,-34.2866f),Vector3D(69.0016f,0.0000f,-34.2866f),Vector3D(72.9668f,0.0000f,-34.2866f),Vector3D(76.5670f,0.0000f,-34.2866f),Vector3D(79.8102f,0.0000f,-34.2866f),Vector3D(80.0241f,0.0000f,-49.9636f),Vector3D(83.7081f,0.0000f,-49.9636f),Vector3D(86.3915f,0.0000f,-49.9636f),Vector3D(89.3730f,0.0000f,-49.9636f),Vector3D(92.5036f,0.0000f,-49.9636f),Vector3D(94.3712f,0.0000f,-49.9636f),Vector3D(45.5123f,0.0000f,-69.8718f),Vector3D(46.5503f,0.0000f,-69.8718f),Vector3D(48.0234f,0.0000f,-69.8718f),Vector3D(49.9318f,0.0000f,-69.8718f),Vector3D(52.3444f,0.0000f,-69.8718f),Vector3D(54.8286f,0.0000f,-69.8718f),Vector3D(57.3790f,0.0000f,-69.8718f),Vector3D(60.1797f,0.0000f,-69.8718f),Vector3D(60.3494f,0.0000f,-84.7140f),Vector3D(65.7571f,0.0000f,-84.7140f),Vector3D(70.6671f,0.0000f,-84.7140f),Vector3D(75.0901f,0.0000f,-84.7140f),Vector3D(79.7657f,0.0000f,-84.7140f),Vector3D(79.9369f,0.0000f,-69.8718f),Vector3D(79.8824f,0.0000f,-69.8718f),Vector3D(85.5296f,0.0000f,-69.8718f),Vector3D(89.0248f,0.0000f,-69.8718f),Vector3D(91.4266f,0.0000f,-69.8718f),Vector3D(45.2124f,0.0000f,-49.9636f),Vector3D(45.1380f,0.0000f,-69.8718f),Vector3D(93.3496f,0.0000f,-69.8718f),Vector3D(94.2809f,0.0000f,-69.8718f),Vector3D(94.6391f,0.0000f,-69.8718f)};
    IndexGroup basisIndexes[39] = {IndexGroup(37,18,36),IndexGroup(18,19,36),IndexGroup(36,19,0),IndexGroup(19,20,0),IndexGroup(0,20,1),IndexGroup(20,21,1),IndexGroup(1,21,2),IndexGroup(21,22,2),IndexGroup(2,22,3),IndexGroup(22,23,3),IndexGroup(3,23,4),IndexGroup(23,24,4),IndexGroup(4,24,5),IndexGroup(24,25,5),IndexGroup(5,25,6),IndexGroup(25,26,6),IndexGroup(6,26,7),IndexGroup(26,27,7),IndexGroup(7,27,8),IndexGroup(27,28,8),IndexGroup(8,28,9),IndexGroup(28,29,9),IndexGroup(10,29,30),IndexGroup(30,31,10),IndexGroup(10,31,11),IndexGroup(31,32,11),IndexGroup(11,32,12),IndexGroup(32,33,12),IndexGroup(12,33,13),IndexGroup(33,34,13),IndexGroup(13,34,14),IndexGroup(34,35,14),IndexGroup(14,35,15),IndexGroup(35,38,15),IndexGroup(15,38,16),IndexGroup(38,39,16),IndexGroup(16,39,17),IndexGroup(39,40,17),IndexGroup(10,9,29)};
    TriangleGroup triangleGroup = TriangleGroup(&basisVertices[0], &basisIndexes[0], 41, 39);
    SimpleMaterial simpleMaterial = SimpleMaterial(RGBColor(128, 128, 128));
    Object3D basisObj = Object3D(&triangleGroup, &simpleMaterial);

    static const uint8_t morphCount = 4;
    int ExclamationIndexes[41] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40};
    int DizzyIndexes[41] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40};
    int BatteryIndexes[41] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40};
    int BatteryFullIndexes[4] = {26,27,28,29};

    Vector3D ExclamationVectors[41] = {Vector3D(28.9991f,0.0000f,10.3707f),Vector3D(27.0610f,0.0000f,8.4327f),Vector3D(24.8249f,0.0000f,6.1965f),Vector3D(22.2906f,0.0000f,3.1233f),Vector3D(11.5039f,0.0000f,3.1233f),Vector3D(8.2639f,0.0000f,-3.7887f),Vector3D(16.3320f,0.0000f,-19.4657f),Vector3D(12.1899f,0.0000f,-22.1155f),Vector3D(7.3307f,0.0000f,-26.9747f),Vector3D(3.3655f,0.0000f,-30.9399f),Vector3D(-0.2347f,0.0000f,-34.5401f),Vector3D(-3.4779f,0.0000f,-37.7833f),Vector3D(-3.6919f,0.0000f,-22.3203f),Vector3D(-7.3758f,0.0000f,-26.0042f),Vector3D(-10.0592f,0.0000f,-28.6876f),Vector3D(-13.0408f,0.0000f,-31.6692f),Vector3D(-16.1714f,0.0000f,-34.7998f),Vector3D(-18.0390f,0.0000f,-36.6674f),Vector3D(17.3145f,0.0000f,32.0998f),Vector3D(16.2765f,0.0000f,31.0619f),Vector3D(14.8033f,0.0000f,29.5887f),Vector3D(12.8949f,0.0000f,27.6803f),Vector3D(10.4824f,0.0000f,23.0315f),Vector3D(13.4004f,0.0000f,23.0315f),Vector3D(10.8499f,0.0000f,23.0315f),Vector3D(8.0492f,0.0000f,16.1196f),Vector3D(2.4773f,0.0000f,30.9618f),Vector3D(-2.9304f,0.0000f,26.6971f),Vector3D(-7.8403f,0.0000f,21.7872f),Vector3D(-12.2634f,0.0000f,17.3641f),Vector3D(-16.9390f,0.0000f,12.6885f),Vector3D(-17.1101f,0.0000f,-2.3248f),Vector3D(-17.0557f,0.0000f,-2.2703f),Vector3D(-22.7029f,0.0000f,-7.9175f),Vector3D(-26.1981f,0.0000f,-11.4127f),Vector3D(-28.5998f,0.0000f,-13.8145f),Vector3D(31.1199f,0.0000f,12.4915f),Vector3D(17.6887f,0.0000f,32.4741f),Vector3D(-30.5228f,0.0000f,-15.7375f),Vector3D(-31.4541f,0.0000f,-16.6688f),Vector3D(-31.8123f,0.0000f,-17.0269f)};
    Vector3D DizzyVectors[41] = {Vector3D(19.0069f,0.0000f,-3.6229f),Vector3D(23.5365f,0.0000f,-4.6505f),Vector3D(26.7502f,0.0000f,-7.8418f),Vector3D(26.5110f,0.0000f,-14.0119f),Vector3D(23.3593f,0.0000f,-19.0372f),Vector3D(16.7131f,0.0000f,-25.0168f),Vector3D(11.1144f,0.0000f,-43.7514f),Vector3D(-0.3806f,0.0000f,-43.7743f),Vector3D(-12.3285f,0.0000f,-40.5095f),Vector3D(-20.6987f,0.0000f,-33.7231f),Vector3D(-24.9334f,0.0000f,-24.8204f),Vector3D(-23.7528f,0.0000f,-16.2138f),Vector3D(-17.3836f,0.0000f,4.4265f),Vector3D(-12.0225f,0.0000f,5.7042f),Vector3D(-7.5262f,0.0000f,4.2418f),Vector3D(-4.2314f,0.0000f,-0.6684f),Vector3D(-3.5449f,0.0000f,-8.6210f),Vector3D(-4.8282f,0.0000f,-16.9160f),Vector3D(12.8263f,0.0000f,11.1643f),Vector3D(14.3795f,0.0000f,16.8163f),Vector3D(19.2957f,0.0000f,19.6567f),Vector3D(24.9653f,0.0000f,18.3347f),Vector3D(28.5321f,0.0000f,13.3481f),Vector3D(28.5954f,0.0000f,5.8862f),Vector3D(25.5400f,0.0000f,-1.3152f),Vector3D(17.7907f,0.0000f,-8.3993f),Vector3D(10.7212f,0.0000f,3.0873f),Vector3D(-3.1286f,0.0000f,2.8535f),Vector3D(-16.3286f,0.0000f,6.5590f),Vector3D(-26.4980f,0.0000f,15.4462f),Vector3D(-31.8389f,0.0000f,26.8672f),Vector3D(-26.3644f,0.0000f,22.3326f),Vector3D(-16.9113f,0.0000f,28.3611f),Vector3D(-13.0024f,0.0000f,29.9098f),Vector3D(-6.8427f,0.0000f,27.5362f),Vector3D(-2.0732f,0.0000f,21.0800f),Vector3D(17.1730f,0.0000f,-5.8117f),Vector3D(14.4353f,0.0000f,7.8449f),Vector3D(0.1611f,0.0000f,11.0567f),Vector3D(-1.2920f,0.0000f,0.8342f),Vector3D(-1.8653f,0.0000f,-0.4154f)};
    Vector3D BatteryVectors[41] = {Vector3D(13.2064f,0.0000f,-30.0296f),Vector3D(4.7857f,0.0000f,-30.0296f),Vector3D(2.5495f,0.0000f,-10.3561f),Vector3D(0.0152f,0.0000f,-3.3636f),Vector3D(-2.6682f,0.0000f,4.0402f),Vector3D(-5.9082f,0.0000f,12.9797f),Vector3D(-5.8590f,0.0000f,0.7071f),Vector3D(-3.2080f,0.0000f,0.7071f),Vector3D(-0.0980f,0.0000f,0.7071f),Vector3D(2.4398f,0.0000f,0.7071f),Vector3D(4.7440f,0.0000f,0.7071f),Vector3D(1.4429f,0.0000f,-3.2483f),Vector3D(1.2289f,0.0000f,-3.2572f),Vector3D(-2.4550f,0.0000f,-9.2990f),Vector3D(-5.1384f,0.0000f,-13.6998f),Vector3D(-8.1200f,0.0000f,-30.0296f),Vector3D(-17.6329f,0.0000f,-30.0296f),Vector3D(-19.5004f,0.0000f,-34.3827f),Vector3D(23.2196f,0.0000f,-13.6765f),Vector3D(22.2930f,0.0000f,-6.1515f),Vector3D(10.2861f,0.0000f,-6.1515f),Vector3D(8.2664f,0.0000f,5.2052f),Vector3D(5.8539f,0.0000f,11.8617f),Vector3D(3.3697f,0.0000f,18.7159f),Vector3D(0.8192f,0.0000f,25.7528f),Vector3D(-1.9815f,0.0000f,32.9238f),Vector3D(-2.2675f,0.0000f,48.4816f),Vector3D(-2.1745f,0.0000f,48.4816f),Vector3D(0.9679f,0.0000f,48.4816f),Vector3D(2.1426f,0.0000f,48.4816f),Vector3D(-2.6431f,0.0000f,46.6954f),Vector3D(-2.8143f,0.0000f,23.3663f),Vector3D(-2.7598f,0.0000f,16.8834f),Vector3D(-8.4070f,0.0000f,7.6219f),Vector3D(-11.9022f,0.0000f,1.8898f),Vector3D(-14.3040f,0.0000f,-6.1515f),Vector3D(15.3272f,0.0000f,-34.3827f),Vector3D(23.5939f,0.0000f,-14.4744f),Vector3D(-26.1037f,0.0000f,-6.1515f),Vector3D(-27.1463f,0.0000f,-13.9744f),Vector3D(-27.5045f,0.0000f,-14.4744f)};
    Vector3D BatteryFullVectors[4] = {Vector3D(0.0000f,0.0000f,-39.8512f),Vector3D(0.0000f,0.0000f,-39.8512f),Vector3D(0.0000f,0.0000f,-39.8512f),Vector3D(0.0000f,0.0000f,-39.8512f)};

    Morph morphs[4] = {
        Morph(41, ExclamationIndexes, ExclamationVectors),
        Morph(41, DizzyIndexes, DizzyVectors),
        Morph(41, BatteryIndexes, BatteryVectors),
        Morph(4, BatteryFullIndexes, BatteryFullVectors)
    };

public:
    SageSchloSideDisplay(){}

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
