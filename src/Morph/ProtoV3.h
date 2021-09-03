#pragma once

#include "Arduino.h"
#include "..\Math\Rotation.h"
#include "Morph.h"
#include "..\Materials\SimpleMaterial.h"
#include "..\Render\IndexGroup.h"
#include "..\Render\Object3D.h"

class ProtoV3{
public:
    enum Morphs {
        HappyMouth,
        FlatMouth,
        ConfuseMouth,
        AngryEye,
        HappyEye,
        SadEye,
        EyeRidgeBigger,
        EyeMove
    };

private:
    Vector3D basisVertices[67] = {Vector3D(9.9742f,52.5924f,-0.0000f),Vector3D(16.4608f,63.7123f,-0.0000f),Vector3D(22.2060f,66.4922f,-0.0000f),Vector3D(25.9126f,64.8242f,-0.0000f),Vector3D(24.0593f,61.6736f,-0.0000f),Vector3D(18.8701f,60.9323f,-0.0000f),Vector3D(14.4221f,19.0475f,-0.0000f),Vector3D(21.2794f,23.4955f,-0.0000f),Vector3D(32.5846f,24.2368f,-0.0000f),Vector3D(44.2604f,19.0475f,-0.0000f),Vector3D(52.7856f,20.5302f,-0.0000f),Vector3D(76.6933f,31.0940f,-0.0000f),Vector3D(86.5158f,30.9087f,-0.0000f),Vector3D(99.4890f,23.1248f,-0.0000f),Vector3D(111.7208f,23.8661f,-0.0000f),Vector3D(124.1380f,32.3913f,-0.0000f),Vector3D(134.8872f,46.1058f,-0.0000f),Vector3D(129.6979f,30.9087f,-0.0000f),Vector3D(125.4353f,24.4221f,-0.0000f),Vector3D(117.0954f,19.9742f,-0.0000f),Vector3D(106.5316f,18.8622f,-0.0000f),Vector3D(93.3731f,20.7155f,-0.0000f),Vector3D(84.2919f,24.7928f,-0.0000f),Vector3D(73.9133f,26.2754f,-0.0000f),Vector3D(62.6082f,22.1981f,-0.0000f),Vector3D(53.7123f,17.7502f,-0.0000f),Vector3D(47.9670f,15.5262f,-0.0000f),Vector3D(40.1831f,16.6382f,-0.0000f),Vector3D(34.4379f,20.5302f,-0.0000f),Vector3D(29.3935f,22.3431f,-0.0000f),Vector3D(21.7629f,21.2088f,-0.0000f),Vector3D(96.6615f,62.2084f,-0.0000f),Vector3D(93.3452f,82.0382f,-0.0000f),Vector3D(96.3576f,92.1513f,-0.0000f),Vector3D(105.1797f,101.6189f,-0.0000f),Vector3D(121.1025f,108.2893f,-0.0000f),Vector3D(135.5190f,108.9348f,-0.0000f),Vector3D(146.7080f,105.0617f,-0.0000f),Vector3D(157.6818f,97.1003f,-0.0000f),Vector3D(160.9094f,91.9362f,-0.0000f),Vector3D(159.8335f,84.4051f,-0.0000f),Vector3D(152.5177f,75.7982f,-0.0000f),Vector3D(142.8349f,69.7734f,-0.0000f),Vector3D(132.0763f,64.6092f,-0.0000f),Vector3D(120.4569f,60.9513f,-0.0000f),Vector3D(132.9006f,66.7741f,-0.0000f),Vector3D(145.0683f,72.3423f,-0.0000f),Vector3D(154.9674f,80.3854f,-0.0000f),Vector3D(158.4733f,85.2318f,-0.0000f),Vector3D(159.6076f,90.2845f,-0.0000f),Vector3D(157.1328f,95.6465f,-0.0000f),Vector3D(150.6365f,101.0086f,-0.0000f),Vector3D(143.3153f,105.1332f,-0.0000f),Vector3D(135.5816f,107.8142f,-0.0000f),Vector3D(121.8672f,107.2986f,-0.0000f),Vector3D(114.6491f,104.5145f,-0.0000f),Vector3D(112.4837f,102.0397f,-0.0000f),Vector3D(121.6610f,98.3275f,-0.0000f),Vector3D(128.5697f,94.7185f,-0.0000f),Vector3D(133.4162f,86.7786f,-0.0000f),Vector3D(135.1691f,79.1480f,-0.0000f),Vector3D(133.0037f,71.7236f,-0.0000f),Vector3D(128.4666f,66.6710f,-0.0000f),Vector3D(122.5293f,62.8705f,-0.0000f),Vector3D(117.2763f,60.3544f,-0.0000f),Vector3D(107.3883f,59.1625f,-0.0000f),Vector3D(101.3407f,59.5156f,-0.0000f)};
    IndexGroup basisIndexes[61] = {IndexGroup(5,1,0),IndexGroup(30,7,6),IndexGroup(31,66,65),IndexGroup(2,1,5),IndexGroup(4,3,2),IndexGroup(29,8,7),IndexGroup(9,8,28),IndexGroup(10,9,26),IndexGroup(11,10,24),IndexGroup(22,12,11),IndexGroup(21,13,12),IndexGroup(20,14,13),IndexGroup(15,14,19),IndexGroup(17,16,15),IndexGroup(20,19,14),IndexGroup(25,24,10),IndexGroup(27,26,9),IndexGroup(29,28,8),IndexGroup(33,32,57),IndexGroup(34,33,56),IndexGroup(35,34,55),IndexGroup(36,35,54),IndexGroup(52,37,36),IndexGroup(38,37,51),IndexGroup(39,38,50),IndexGroup(40,39,49),IndexGroup(47,41,40),IndexGroup(46,42,41),IndexGroup(45,43,42),IndexGroup(45,44,43),IndexGroup(52,51,37),IndexGroup(59,58,57),IndexGroup(61,60,59),IndexGroup(59,57,62),IndexGroup(57,32,63),IndexGroup(64,63,32),IndexGroup(4,2,5),IndexGroup(30,29,7),IndexGroup(27,9,28),IndexGroup(25,10,26),IndexGroup(23,11,24),IndexGroup(23,22,11),IndexGroup(22,21,12),IndexGroup(21,20,13),IndexGroup(18,15,19),IndexGroup(18,17,15),IndexGroup(56,33,57),IndexGroup(55,34,56),IndexGroup(54,35,55),IndexGroup(53,36,54),IndexGroup(53,52,36),IndexGroup(50,38,51),IndexGroup(49,39,50),IndexGroup(48,40,49),IndexGroup(48,47,40),IndexGroup(47,46,41),IndexGroup(46,45,42),IndexGroup(61,59,62),IndexGroup(62,57,63),IndexGroup(65,64,32),IndexGroup(32,31,65)};
    TriangleGroup triangleGroup = TriangleGroup(&basisVertices[0], &basisIndexes[0], 67, 61);
    SimpleMaterial simpleMaterial = SimpleMaterial(RGBColor(128, 128, 128));
    Object3D basisObj = Object3D(&triangleGroup, &simpleMaterial);

    static const byte morphCount = 8;
    int HappyMouthIndexes[24] = {7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30};
    int FlatMouthIndexes[16] = {10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25};
    int ConfuseMouthIndexes[25] = {6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30};
    int AngryEyeIndexes[33] = {31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63};
    int HappyEyeIndexes[33] = {31,32,33,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,56,57,58,59,60,61,62,63,64,65,66};
    int SadEyeIndexes[33] = {32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64};
    int EyeRidgeBiggerIndexes[12] = {45,46,47,48,49,50,51,52,53,54,55,56};
    int EyeMoveIndexes[36] = {31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66};

    Vector3D HappyMouthVectors[24] = {Vector3D(-0.0293f,0.0026f,0.0000f),Vector3D(-5.5646f,-0.0660f,0.0000f),Vector3D(-12.5607f,-0.4567f,0.0000f),Vector3D(-12.7281f,0.7202f,0.0000f),Vector3D(-25.3403f,0.5941f,0.0000f),Vector3D(-27.9533f,1.4030f,0.0000f),Vector3D(-24.9415f,-1.9718f,0.0000f),Vector3D(-2.9937f,0.2663f,0.0000f),Vector3D(0.5307f,-1.1396f,0.0000f),Vector3D(0.0678f,-0.0302f,0.0000f),Vector3D(3.2520f,-1.0277f,0.0000f),Vector3D(6.4825f,-1.9096f,0.0000f),Vector3D(6.7659f,-1.1888f,0.0000f),Vector3D(-6.5991f,-2.4196f,0.0000f),Vector3D(-23.8205f,-2.1830f,0.0000f),Vector3D(-25.9229f,-0.9532f,0.0000f),Vector3D(-21.3086f,-0.8594f,0.0000f),Vector3D(-14.9761f,1.9123f,0.0000f),Vector3D(-12.7683f,0.2167f,0.0000f),Vector3D(-12.2809f,-0.7947f,0.0000f),Vector3D(-10.1593f,-0.6204f,0.0000f),Vector3D(-7.2826f,0.0486f,0.0000f),Vector3D(-3.8191f,0.1255f,0.0000f),Vector3D(-0.0924f,0.0315f,0.0000f)};
    Vector3D FlatMouthVectors[16] = {Vector3D(-0.3259f,-1.0184f,0.0000f),Vector3D(-2.4697f,-9.0492f,0.0000f),Vector3D(-3.9132f,-9.6023f,0.0000f),Vector3D(-5.1012f,-4.6586f,0.0000f),Vector3D(1.3572f,-2.8374f,0.0000f),Vector3D(4.4166f,-9.2825f,0.0000f),Vector3D(3.6068f,-11.9024f,0.0000f),Vector3D(4.1867f,-9.2189f,0.0000f),Vector3D(3.5129f,-7.1171f,0.0000f),Vector3D(1.6240f,-2.4349f,0.0000f),Vector3D(-1.7763f,-1.8196f,0.0000f),Vector3D(-4.8898f,-6.9604f,0.0000f),Vector3D(-3.0909f,-9.0343f,0.0000f),Vector3D(-1.9512f,-8.0218f,0.0000f),Vector3D(-1.4172f,-4.5870f,0.0000f),Vector3D(-0.3080f,-0.9625f,0.0000f)};
    Vector3D ConfuseMouthVectors[25] = {Vector3D(-4.0939f,5.9468f,0.0000f),Vector3D(-4.0594f,9.2313f,0.0000f),Vector3D(-9.5928f,8.4651f,0.0000f),Vector3D(-11.6556f,0.8948f,0.0000f),Vector3D(-15.2016f,3.8022f,0.0000f),Vector3D(-29.0726f,3.3849f,0.0000f),Vector3D(-34.2059f,3.1036f,0.0000f),Vector3D(-32.0390f,-2.9153f,0.0000f),Vector3D(-22.2181f,9.7349f,0.0000f),Vector3D(-10.3662f,-12.5916f,0.0000f),Vector3D(-5.4776f,-15.7298f,0.0000f),Vector3D(-12.1968f,-14.2361f,0.0000f),Vector3D(-17.8059f,-7.2562f,0.0000f),Vector3D(-28.7694f,9.9569f,0.0000f),Vector3D(-35.7478f,-1.8918f,0.0000f),Vector3D(-31.1560f,-2.5884f,0.0000f),Vector3D(-34.9842f,6.3570f,0.0000f),Vector3D(-28.2953f,3.8782f,0.0000f),Vector3D(-21.7328f,2.0107f,0.0000f),Vector3D(-15.0813f,2.2160f,0.0000f),Vector3D(-12.5656f,1.4510f,0.0000f),Vector3D(-9.4670f,0.8693f,0.0000f),Vector3D(-8.0832f,2.3291f,0.0000f),Vector3D(-8.6109f,7.1386f,0.0000f),Vector3D(-8.1553f,5.3337f,0.0000f)};
    Vector3D AngryEyeVectors[33] = {Vector3D(0.0413f,-0.0635f,0.0000f),Vector3D(4.6286f,-7.1183f,0.0000f),Vector3D(8.2765f,-12.6749f,0.0000f),Vector3D(9.9893f,-15.1182f,0.0000f),Vector3D(5.6986f,-8.3688f,0.0000f),Vector3D(1.1052f,-1.4041f,0.0000f),Vector3D(0.2994f,-0.2994f,0.0000f),Vector3D(0.0508f,-0.0508f,0.0000f),Vector3D(0.0095f,-0.0095f,0.0000f),Vector3D(0.0031f,-0.0031f,0.0000f),Vector3D(0.0114f,-0.0114f,0.0000f),Vector3D(0.0243f,-0.0243f,0.0000f),Vector3D(0.0142f,-0.0142f,0.0000f),Vector3D(0.0001f,-0.0001f,0.0000f),Vector3D(0.0335f,-0.0335f,0.0000f),Vector3D(0.0348f,-0.0348f,0.0000f),Vector3D(0.0177f,-0.0177f,0.0000f),Vector3D(0.0114f,-0.0114f,0.0000f),Vector3D(0.0159f,-0.0159f,0.0000f),Vector3D(0.0570f,-0.0570f,0.0000f),Vector3D(0.2040f,-0.2040f,0.0000f),Vector3D(0.4010f,-0.4010f,0.0000f),Vector3D(1.1699f,-1.4944f,0.0000f),Vector3D(5.6088f,-8.2305f,0.0000f),Vector3D(8.4407f,-12.6187f,0.0000f),Vector3D(9.1960f,-13.8234f,0.0000f),Vector3D(6.3687f,-9.4560f,0.0000f),Vector3D(3.4608f,-4.9903f,0.0000f),Vector3D(1.2747f,-1.7072f,0.0000f),Vector3D(0.3663f,-0.4145f,0.0000f),Vector3D(0.1146f,-0.1146f,0.0000f),Vector3D(0.0407f,-0.0407f,0.0000f),Vector3D(0.0061f,-0.0061f,0.0000f)};
    Vector3D HappyEyeVectors[33] = {Vector3D(-0.9761f,1.6675f,0.0000f),Vector3D(-0.1925f,0.3288f,0.0000f),Vector3D(-0.0245f,0.0419f,0.0000f),Vector3D(0.0509f,-0.2376f,0.1786f),Vector3D(0.1995f,-0.9331f,0.6236f),Vector3D(0.3166f,-1.6290f,1.1158f),Vector3D(0.2707f,-1.6637f,1.2664f),Vector3D(-0.2227f,-0.7658f,1.5146f),Vector3D(-2.0059f,3.1023f,1.6687f),Vector3D(-3.6597f,7.1419f,1.2650f),Vector3D(-3.9123f,8.3553f,0.4584f),Vector3D(-2.3846f,5.2862f,0.0084f),Vector3D(-3.9754f,8.4231f,0.5539f),Vector3D(-3.3139f,6.2364f,1.4256f),Vector3D(-1.1800f,1.2590f,1.6664f),Vector3D(-0.2874f,-0.6411f,1.5452f),Vector3D(0.1463f,-1.4722f,1.3765f),Vector3D(0.2747f,-1.6101f,1.2089f),Vector3D(0.2524f,-1.3129f,0.9350f),Vector3D(0.1692f,-0.8028f,0.5550f),Vector3D(0.0640f,-0.2985f,0.2215f),Vector3D(0.0000f,0.0000f,0.0018f),Vector3D(-0.0213f,0.0364f,0.0000f),Vector3D(-0.3127f,0.5342f,0.0000f),Vector3D(-0.6492f,1.1091f,0.0000f),Vector3D(-1.5877f,2.7124f,0.0000f),Vector3D(-2.5774f,4.4030f,0.0000f),Vector3D(-3.6383f,6.2155f,0.0000f),Vector3D(-4.2634f,7.2833f,0.0000f),Vector3D(-4.3768f,7.4770f,0.0000f),Vector3D(-4.0239f,6.8741f,0.0000f),Vector3D(-2.6795f,4.5775f,0.0000f),Vector3D(-1.6436f,2.8078f,0.0000f)};
    Vector3D SadEyeVectors[33] = {Vector3D(-0.0253f,-0.0063f,0.0000f),Vector3D(-0.1406f,-0.0351f,0.0000f),Vector3D(-1.0322f,-2.2827f,0.0000f),Vector3D(-4.6570f,-13.7616f,0.0000f),Vector3D(-5.6386f,-17.4723f,0.0000f),Vector3D(-3.6860f,-12.2762f,0.0000f),Vector3D(-0.4829f,-2.4092f,0.0000f),Vector3D(0.2728f,0.3049f,0.0000f),Vector3D(0.5050f,1.3120f,0.0000f),Vector3D(0.3184f,1.1555f,0.0000f),Vector3D(-0.0536f,0.4649f,0.0000f),Vector3D(-0.2071f,-0.0296f,0.0000f),Vector3D(-0.0841f,-0.0210f,0.0000f),Vector3D(-0.2807f,-0.0005f,0.0000f),Vector3D(-0.0011f,0.6579f,0.0000f),Vector3D(0.3493f,1.0912f,0.0000f),Vector3D(0.3990f,0.9738f,0.0000f),Vector3D(0.2400f,0.2528f,0.0000f),Vector3D(-0.4706f,-2.2896f,0.0000f),Vector3D(-2.4007f,-8.4290f,0.0000f),Vector3D(-4.4780f,-14.4359f,0.0000f),Vector3D(-5.6309f,-17.4702f,0.0000f),Vector3D(-4.8027f,-14.2139f,0.0000f),Vector3D(-3.1678f,-8.8104f,0.0000f),Vector3D(-2.5766f,-6.7901f,0.0000f),Vector3D(-4.1517f,-11.7947f,0.0000f),Vector3D(-4.3661f,-12.7527f,0.0000f),Vector3D(-2.9202f,-7.6991f,0.0000f),Vector3D(-1.4658f,-2.7320f,0.0000f),Vector3D(-0.6118f,-0.3080f,0.0000f),Vector3D(-0.3376f,-0.0844f,0.0000f),Vector3D(-0.1563f,-0.0391f,0.0000f),Vector3D(-0.0517f,-0.0129f,0.0000f)};
    Vector3D EyeRidgeBiggerVectors[12] = {Vector3D(0.2041f,2.0682f,0.0000f),Vector3D(-0.5854f,1.5070f,0.0000f),Vector3D(-1.2277f,0.6963f,0.0000f),Vector3D(-1.4552f,0.2079f,0.0000f),Vector3D(-1.5288f,-0.3014f,0.0000f),Vector3D(-1.3682f,-0.8418f,0.0000f),Vector3D(-0.9467f,-1.3823f,0.0000f),Vector3D(-0.4717f,-1.7980f,0.0000f),Vector3D(0.0301f,-2.0682f,0.0000f),Vector3D(0.9199f,-2.0163f,0.0000f),Vector3D(1.3883f,-1.7357f,0.0000f),Vector3D(1.5288f,-1.4862f,0.0000f)};
    Vector3D EyeMoveVectors[36] = {Vector3D(-1.7578f,-5.2735f,0.0000f),Vector3D(-1.7578f,-5.2735f,0.0000f),Vector3D(-1.7578f,-5.2735f,0.0000f),Vector3D(-1.7578f,-5.2735f,0.0000f),Vector3D(-1.7578f,-5.2735f,0.0000f),Vector3D(-1.7578f,-5.2735f,0.0000f),Vector3D(-1.7578f,-5.2735f,0.0000f),Vector3D(-1.7578f,-5.2735f,0.0000f),Vector3D(-1.7578f,-5.2735f,0.0000f),Vector3D(-1.7578f,-5.2735f,0.0000f),Vector3D(-1.7578f,-5.2735f,0.0000f),Vector3D(-1.7578f,-5.2735f,0.0000f),Vector3D(-1.7578f,-5.2735f,0.0000f),Vector3D(-1.7578f,-5.2735f,0.0000f),Vector3D(-1.7578f,-5.2735f,0.0000f),Vector3D(-1.7578f,-5.2735f,0.0000f),Vector3D(-1.7578f,-5.2735f,0.0000f),Vector3D(-1.7578f,-5.2735f,0.0000f),Vector3D(-1.7578f,-5.2735f,0.0000f),Vector3D(-1.7578f,-5.2735f,0.0000f),Vector3D(-1.7578f,-5.2735f,0.0000f),Vector3D(-1.7578f,-5.2735f,0.0000f),Vector3D(-1.7578f,-5.2735f,0.0000f),Vector3D(-1.7578f,-5.2735f,0.0000f),Vector3D(-1.7578f,-5.2735f,0.0000f),Vector3D(-1.7578f,-5.2735f,0.0000f),Vector3D(-1.7578f,-5.2735f,0.0000f),Vector3D(-1.7578f,-5.2735f,0.0000f),Vector3D(-1.7578f,-5.2735f,0.0000f),Vector3D(-1.7578f,-5.2735f,0.0000f),Vector3D(-1.7578f,-5.2735f,0.0000f),Vector3D(-1.7578f,-5.2735f,0.0000f),Vector3D(-1.7578f,-5.2735f,0.0000f),Vector3D(-1.7578f,-5.2735f,0.0000f),Vector3D(-1.7578f,-5.2735f,0.0000f),Vector3D(-1.7578f,-5.2735f,0.0000f)};

    Morph morphs[8] = {
        Morph(24, HappyMouthIndexes, HappyMouthVectors),
        Morph(16, FlatMouthIndexes, FlatMouthVectors),
        Morph(25, ConfuseMouthIndexes, ConfuseMouthVectors),
        Morph(33, AngryEyeIndexes, AngryEyeVectors),
        Morph(33, HappyEyeIndexes, HappyEyeVectors),
        Morph(33, SadEyeIndexes, SadEyeVectors),
        Morph(12, EyeRidgeBiggerIndexes, EyeRidgeBiggerVectors),
        Morph(36, EyeMoveIndexes, EyeMoveVectors)
    };

public:
    ProtoV3(){}

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
