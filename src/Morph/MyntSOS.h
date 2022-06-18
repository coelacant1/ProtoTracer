#pragma once

#include "Arduino.h"
#include "..\Math\Rotation.h"
#include "Morph.h"
#include "..\Materials\SimpleMaterial.h"
#include "..\Render\IndexGroup.h"
#include "..\Render\Object3D.h"

class MyntSOS{
public:
    enum Morphs {
        Smaller
    };

private:
    Vector3D basisVertices[101] = {Vector3D(135.1478f,66.3890f,3.1326f),Vector3D(129.5017f,68.4328f,3.1326f),Vector3D(124.7988f,68.2523f,3.1326f),Vector3D(121.0533f,66.7356f,3.1326f),Vector3D(118.4350f,63.9201f,3.1326f),Vector3D(117.2985f,59.3914f,3.1326f),Vector3D(118.2167f,55.7736f,3.1326f),Vector3D(120.8273f,52.5468f,3.1326f),Vector3D(129.5543f,46.8811f,3.1326f),Vector3D(132.2744f,43.1708f,3.1326f),Vector3D(131.2372f,39.6328f,3.1326f),Vector3D(128.7653f,38.1401f,3.1326f),Vector3D(124.8697f,37.9348f,3.1326f),Vector3D(120.2046f,40.0900f,3.1326f),Vector3D(117.6086f,42.8251f,3.1326f),Vector3D(117.6832f,36.4612f,3.1326f),Vector3D(123.3350f,33.7888f,3.1326f),Vector3D(130.3306f,33.7624f,3.1326f),Vector3D(134.4924f,36.5301f,3.1326f),Vector3D(136.7314f,40.9892f,3.1326f),Vector3D(135.9670f,46.8654f,3.1326f),Vector3D(132.6577f,50.9020f,3.1326f),Vector3D(124.0173f,56.1953f,3.1326f),Vector3D(122.2016f,58.5097f,3.1326f),Vector3D(121.9938f,60.9202f,3.1326f),Vector3D(123.6623f,63.2310f,3.1326f),Vector3D(128.6758f,64.2136f,3.1326f),Vector3D(135.1054f,60.9558f,3.1326f),Vector3D(109.1674f,39.4908f,3.1326f),Vector3D(106.9759f,37.5896f,3.1326f),Vector3D(107.3716f,34.7088f,3.1326f),Vector3D(109.8698f,33.3622f,3.1326f),Vector3D(112.2297f,34.4868f,3.1326f),Vector3D(112.9812f,37.0990f,3.1326f),Vector3D(111.4169f,39.1382f,3.1326f),Vector3D(65.6141f,48.8351f,3.1326f),Vector3D(67.2646f,43.1499f,3.1326f),Vector3D(71.1815f,37.9364f,3.1326f),Vector3D(77.6635f,34.2302f,3.1326f),Vector3D(86.6799f,33.5083f,3.1326f),Vector3D(94.1710f,36.1351f,3.1326f),Vector3D(99.1399f,40.8018f,3.1326f),Vector3D(101.6734f,46.3336f,3.1326f),Vector3D(102.2488f,51.2194f,3.1326f),Vector3D(101.4939f,56.3687f,3.1326f),Vector3D(98.8262f,61.6160f,3.1326f),Vector3D(94.1156f,65.9039f,3.1326f),Vector3D(86.7131f,68.4652f,3.1326f),Vector3D(80.1244f,68.1944f,3.1326f),Vector3D(74.8626f,66.5386f,3.1326f),Vector3D(70.5418f,63.3081f,3.1326f),Vector3D(67.3851f,59.1041f,3.1326f),Vector3D(65.7360f,53.8228f,3.1326f),Vector3D(71.6282f,56.7015f,3.1326f),Vector3D(75.5192f,61.3719f,3.1326f),Vector3D(80.7115f,63.8050f,3.1326f),Vector3D(88.1216f,63.5878f,3.1326f),Vector3D(94.3530f,59.4901f,3.1326f),Vector3D(96.9465f,53.9003f,3.1326f),Vector3D(96.8476f,47.1615f,3.1326f),Vector3D(93.8925f,42.1570f,3.1326f),Vector3D(90.5081f,39.4997f,3.1326f),Vector3D(85.6087f,38.0085f,3.1326f),Vector3D(80.2607f,38.3392f,3.1326f),Vector3D(75.6295f,40.5186f,3.1326f),Vector3D(72.3073f,44.2191f,3.1326f),Vector3D(70.5524f,49.5903f,3.1326f),Vector3D(56.5381f,39.4005f,3.1326f),Vector3D(54.6804f,36.5683f,3.1326f),Vector3D(55.9993f,33.9804f,3.1326f),Vector3D(59.0774f,33.5724f,3.1326f),Vector3D(60.9350f,36.4046f,3.1326f),Vector3D(59.6162f,38.9925f,3.1326f),Vector3D(49.2059f,66.3809f,3.1326f),Vector3D(43.5517f,68.4328f,3.1326f),Vector3D(37.7708f,68.0537f,3.1326f),Vector3D(33.8233f,65.6627f,3.1326f),Vector3D(31.8044f,62.3728f,3.1326f),Vector3D(31.6338f,56.9885f,3.1326f),Vector3D(34.8773f,52.5468f,3.1326f),Vector3D(44.3636f,46.2845f,3.1326f),Vector3D(46.0330f,43.5735f,3.1326f),Vector3D(46.1537f,41.2886f,3.1326f),Vector3D(44.3066f,38.7336f,3.1326f),Vector3D(39.3971f,37.8126f,3.1326f),Vector3D(34.2545f,40.0900f,3.1326f),Vector3D(31.6586f,42.8251f,3.1326f),Vector3D(31.7332f,36.4611f,3.1326f),Vector3D(37.3797f,33.7866f,3.1326f),Vector3D(43.2232f,33.5817f,3.1326f),Vector3D(48.1024f,35.9080f,3.1326f),Vector3D(50.5001f,40.2091f,3.1326f),Vector3D(50.7261f,44.2419f,3.1326f),Vector3D(49.5694f,47.5985f,3.1326f),Vector3D(46.7088f,50.9009f,3.1326f),Vector3D(37.7179f,56.4505f,3.1326f),Vector3D(36.1287f,58.8924f,3.1326f),Vector3D(36.2380f,61.6681f,3.1326f),Vector3D(39.1279f,63.8636f,3.1326f),Vector3D(44.4970f,63.7510f,3.1326f),Vector3D(49.3718f,60.6442f,3.1326f)};
    IndexGroup basisIndexes[93] = {IndexGroup(2,0,1),IndexGroup(3,0,2),IndexGroup(3,26,0),IndexGroup(26,27,0),IndexGroup(4,26,3),IndexGroup(4,25,26),IndexGroup(5,25,4),IndexGroup(5,24,25),IndexGroup(5,23,24),IndexGroup(5,22,23),IndexGroup(6,22,5),IndexGroup(7,22,6),IndexGroup(7,21,22),IndexGroup(8,21,7),IndexGroup(8,20,21),IndexGroup(9,20,8),IndexGroup(9,19,20),IndexGroup(15,13,14),IndexGroup(10,19,9),IndexGroup(15,12,13),IndexGroup(11,19,10),IndexGroup(11,18,19),IndexGroup(12,18,11),IndexGroup(15,18,12),IndexGroup(15,17,18),IndexGroup(16,17,15),IndexGroup(29,34,28),IndexGroup(29,33,34),IndexGroup(30,33,29),IndexGroup(30,32,33),IndexGroup(31,32,30),IndexGroup(49,47,48),IndexGroup(49,46,47),IndexGroup(50,46,49),IndexGroup(55,46,50),IndexGroup(56,46,55),IndexGroup(56,45,46),IndexGroup(50,54,55),IndexGroup(51,54,50),IndexGroup(57,45,56),IndexGroup(51,53,54),IndexGroup(57,44,45),IndexGroup(58,44,57),IndexGroup(52,53,51),IndexGroup(58,43,44),IndexGroup(52,66,53),IndexGroup(35,66,52),IndexGroup(59,43,58),IndexGroup(59,42,43),IndexGroup(35,65,66),IndexGroup(36,65,35),IndexGroup(59,41,42),IndexGroup(60,41,59),IndexGroup(36,64,65),IndexGroup(61,41,60),IndexGroup(37,64,36),IndexGroup(37,63,64),IndexGroup(62,41,61),IndexGroup(62,40,41),IndexGroup(37,62,63),IndexGroup(37,40,62),IndexGroup(38,40,37),IndexGroup(38,39,40),IndexGroup(68,72,67),IndexGroup(68,71,72),IndexGroup(69,71,68),IndexGroup(69,70,71),IndexGroup(75,73,74),IndexGroup(76,73,75),IndexGroup(76,99,73),IndexGroup(99,100,73),IndexGroup(77,98,76),IndexGroup(98,99,76),IndexGroup(77,97,98),IndexGroup(78,97,77),IndexGroup(78,96,97),IndexGroup(78,95,96),IndexGroup(79,95,78),IndexGroup(79,94,95),IndexGroup(80,94,79),IndexGroup(80,93,94),IndexGroup(80,92,93),IndexGroup(81,92,80),IndexGroup(82,92,81),IndexGroup(87,85,86),IndexGroup(82,91,92),IndexGroup(83,91,82),IndexGroup(87,84,85),IndexGroup(83,90,91),IndexGroup(84,90,83),IndexGroup(87,90,84),IndexGroup(88,90,87),IndexGroup(88,89,90)};
    TriangleGroup triangleGroup = TriangleGroup(&basisVertices[0], &basisIndexes[0], 101, 93);
    SimpleMaterial simpleMaterial = SimpleMaterial(RGBColor(128, 128, 128));
    Object3D basisObj = Object3D(&triangleGroup, &simpleMaterial);

    static const byte morphCount = 1;
    int SmallerIndexes[101] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,96,97,98,99,100};

    Vector3D SmallerVectors[101] = {Vector3D(-18.1816f,-6.1361f,0.0000f),Vector3D(-16.1755f,-6.8623f,0.0000f),Vector3D(-14.5045f,-6.7982f,0.0000f),Vector3D(-13.1736f,-6.2592f,0.0000f),Vector3D(-12.2433f,-5.2589f,0.0000f),Vector3D(-11.8395f,-3.6498f,0.0000f),Vector3D(-12.1657f,-2.3643f,0.0000f),Vector3D(-13.0933f,-1.2178f,0.0000f),Vector3D(-16.1942f,0.7953f,0.0000f),Vector3D(-17.1606f,2.1136f,0.0000f),Vector3D(-16.7921f,3.3707f,0.0000f),Vector3D(-15.9138f,3.9011f,0.0000f),Vector3D(-14.5297f,3.9740f,0.0000f),Vector3D(-12.8721f,3.2083f,0.0000f),Vector3D(-11.9497f,2.2365f,0.0000f),Vector3D(-11.9762f,4.4976f,0.0000f),Vector3D(-13.9843f,5.4472f,0.0000f),Vector3D(-16.4700f,5.4565f,0.0000f),Vector3D(-17.9487f,4.4732f,0.0000f),Vector3D(-18.7443f,2.8888f,0.0000f),Vector3D(-18.4727f,0.8009f,0.0000f),Vector3D(-17.2968f,-0.6334f,0.0000f),Vector3D(-14.2268f,-2.5142f,0.0000f),Vector3D(-13.5816f,-3.3365f,0.0000f),Vector3D(-13.5078f,-4.1930f,0.0000f),Vector3D(-14.1007f,-5.0140f,0.0000f),Vector3D(-15.8820f,-5.3631f,0.0000f),Vector3D(-18.1665f,-4.2056f,0.0000f),Vector3D(-8.9504f,3.4212f,0.0000f),Vector3D(-8.1717f,4.0967f,0.0000f),Vector3D(-8.3123f,5.1203f,0.0000f),Vector3D(-9.2000f,5.5987f,0.0000f),Vector3D(-10.0385f,5.1992f,0.0000f),Vector3D(-10.3055f,4.2710f,0.0000f),Vector3D(-9.7497f,3.5464f,0.0000f),Vector3D(6.5246f,0.1010f,0.0000f),Vector3D(5.9381f,2.1210f,0.0000f),Vector3D(4.5464f,3.9735f,0.0000f),Vector3D(2.2433f,5.2903f,0.0000f),Vector3D(-0.9604f,5.5468f,0.0000f),Vector3D(-3.6220f,4.6135f,0.0000f),Vector3D(-5.3875f,2.9553f,0.0000f),Vector3D(-6.2877f,0.9898f,0.0000f),Vector3D(-6.4922f,-0.7461f,0.0000f),Vector3D(-6.2239f,-2.5758f,0.0000f),Vector3D(-5.2761f,-4.4402f,0.0000f),Vector3D(-3.6023f,-5.9637f,0.0000f),Vector3D(-0.9721f,-6.8738f,0.0000f),Vector3D(1.3689f,-6.7776f,0.0000f),Vector3D(3.2385f,-6.1893f,0.0000f),Vector3D(4.7737f,-5.0414f,0.0000f),Vector3D(5.8953f,-3.5477f,0.0000f),Vector3D(6.4813f,-1.6712f,0.0000f),Vector3D(4.3877f,-2.6940f,0.0000f),Vector3D(3.0052f,-4.3534f,0.0000f),Vector3D(1.1603f,-5.2180f,0.0000f),Vector3D(-1.4726f,-5.1408f,0.0000f),Vector3D(-3.6867f,-3.6848f,0.0000f),Vector3D(-4.6082f,-1.6987f,0.0000f),Vector3D(-4.5731f,0.6957f,0.0000f),Vector3D(-3.5231f,2.4738f,0.0000f),Vector3D(-2.3205f,3.4180f,0.0000f),Vector3D(-0.5797f,3.9478f,0.0000f),Vector3D(1.3205f,3.8303f,0.0000f),Vector3D(2.9660f,3.0560f,0.0000f),Vector3D(4.1464f,1.7411f,0.0000f),Vector3D(4.7700f,-0.1673f,0.0000f),Vector3D(9.7494f,3.4533f,0.0000f),Vector3D(10.4095f,4.4596f,0.0000f),Vector3D(9.9409f,5.3791f,0.0000f),Vector3D(8.8472f,5.5240f,0.0000f),Vector3D(8.1871f,4.5177f,0.0000f),Vector3D(8.6557f,3.5982f,0.0000f),Vector3D(12.3546f,-6.1332f,0.0000f),Vector3D(14.3636f,-6.8623f,0.0000f),Vector3D(16.4177f,-6.7276f,0.0000f),Vector3D(17.8203f,-5.8780f,0.0000f),Vector3D(18.5376f,-4.7091f,0.0000f),Vector3D(18.5982f,-2.7960f,0.0000f),Vector3D(17.4458f,-1.2178f,0.0000f),Vector3D(14.0752f,1.0073f,0.0000f),Vector3D(13.4820f,1.9705f,0.0000f),Vector3D(13.4391f,2.7824f,0.0000f),Vector3D(14.0954f,3.6902f,0.0000f),Vector3D(15.8398f,4.0174f,0.0000f),Vector3D(17.6671f,3.2083f,0.0000f),Vector3D(18.5894f,2.2365f,0.0000f),Vector3D(18.5629f,4.4976f,0.0000f),Vector3D(16.5566f,5.4479f,0.0000f),Vector3D(14.4804f,5.5207f,0.0000f),Vector3D(12.7467f,4.6942f,0.0000f),Vector3D(11.8948f,3.1660f,0.0000f),Vector3D(11.8145f,1.7331f,0.0000f),Vector3D(12.2255f,0.5404f,0.0000f),Vector3D(13.2419f,-0.6330f,0.0000f),Vector3D(16.4365f,-2.6048f,0.0000f),Vector3D(17.0011f,-3.4725f,0.0000f),Vector3D(16.9623f,-4.4587f,0.0000f),Vector3D(15.9355f,-5.2388f,0.0000f),Vector3D(14.0278f,-5.1988f,0.0000f),Vector3D(12.2957f,-4.0949f,0.0000f)};

    Morph morphs[1] = {
        Morph(101, SmallerIndexes, SmallerVectors)
    };

public:
    MyntSOS(){}

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
