#pragma once

#include "Arduino.h"
#include "..\Math\Rotation.h"
#include "Morph.h"
#include "..\Materials\SimpleMaterial.h"
#include "..\Render\IndexGroup.h"
#include "..\Render\Object3D.h"

class ProtoDR{
public:
    enum Morphs {
        HideSecondEye,
        HideBlush,
        TopFinOuterThin,
        TopFinInnerThin,
        MidFinTopThin,
        MidFinBotThin,
        MidFinMidBigger,
        BotFinLR1Thin,
        BotFinLR2Thin,
        BotFinLR3Thin,
        BotFinLR4Thin,
        BotFinLR5Thin,
        TopFinInnerCloseGap,
        ShockedMouth,
        HappyMouth,
        OwOMouth,
        UpsetMouth,
        SillyMouth,
        FlatMouth,
        OpenToothMouth,
        SadMouth,
        PogMouth,
        DerpyMouth,
        SkinnyEye,
        SadEye,
        CircleEye,
        HeartEye,
        ClosedEye,
        BlushEye,
        ClosedEyeBrow,
        AngryEye,
        DeadEye,
        HideEyeBrow,
        SadEyeBrow,
        AngryEyeBrow,
        OwO,
        NewFins,
        AngryEyeMouth
    };

private:
    Vector3D basisVertices[128] = {Vector3D(-180.2830f,22.1568f,-65.0000f),Vector3D(-152.1540f,43.1344f,-65.0000f),Vector3D(-171.2245f,13.0983f,-65.0000f),Vector3D(-148.8166f,31.6921f,-65.0000f),Vector3D(-105.4312f,15.9589f,-65.0000f),Vector3D(-106.3847f,25.9709f,-65.0000f),Vector3D(-59.1851f,40.7506f,-65.0000f),Vector3D(-63.4760f,49.3323f,-65.0000f),Vector3D(-45.3590f,71.7402f,-65.0000f),Vector3D(-41.8793f,56.3165f,-65.0000f),Vector3D(-32.1758f,56.7576f,-65.0000f),Vector3D(-23.4279f,72.2169f,-65.0000f),Vector3D(-16.2765f,48.3788f,-65.0000f),Vector3D(-21.9976f,41.2273f,-65.0000f),Vector3D(-100.9826f,80.5753f,-65.0000f),Vector3D(-83.0233f,63.1584f,-65.0000f),Vector3D(-80.2524f,88.5146f,-65.0000f),Vector3D(-75.8719f,66.0190f,-65.0000f),Vector3D(-70.1507f,68.4028f,-65.0000f),Vector3D(-49.1731f,86.0431f,-65.0000f),Vector3D(-73.1952f,92.0431f,-65.0000f),Vector3D(-59.9632f,97.3360f,-65.0000f),Vector3D(-34.3935f,88.4269f,-65.0000f),Vector3D(-42.4984f,88.9037f,-65.0000f),Vector3D(-50.2596f,100.4235f,-65.0000f),Vector3D(-31.2936f,107.4806f,-65.0000f),Vector3D(-118.7805f,122.2771f,-65.0000f),Vector3D(-125.4552f,97.0086f,-65.0000f),Vector3D(-101.1403f,107.9742f,-65.0000f),Vector3D(-112.5826f,141.3476f,-65.0000f),Vector3D(-77.7789f,117.9862f,-65.0000f),Vector3D(-94.8077f,153.7929f,-65.0000f),Vector3D(-59.6619f,125.6144f,-65.0000f),Vector3D(-74.9183f,167.0928f,-65.0000f),Vector3D(-52.9872f,152.7899f,-65.0000f),Vector3D(-30.1026f,138.4870f,-65.0000f),Vector3D(-129.2693f,113.6953f,-65.0000f),Vector3D(-133.0834f,124.1841f,-65.0000f),Vector3D(-119.7341f,146.1152f,-65.0000f),Vector3D(-124.5017f,154.2202f,-65.0000f),Vector3D(-97.8030f,173.7675f,-65.0000f),Vector3D(-81.5930f,171.3837f,-65.0000f),Vector3D(-197.9232f,58.3908f,-65.0000f),Vector3D(-190.7718f,86.0431f,-65.0000f),Vector3D(-189.3415f,64.5887f,-65.0000f),Vector3D(-185.5274f,79.3684f,-65.0000f),Vector3D(-173.1315f,82.2290f,-65.0000f),Vector3D(-166.9336f,91.2875f,-65.0000f),Vector3D(-4.8341f,133.2426f,-65.0000f),Vector3D(-1.0200f,140.8708f,-65.0000f),Vector3D(-58.2316f,202.8501f,-65.0000f),Vector3D(-21.0441f,196.6521f,-65.0000f),Vector3D(61.9127f,246.7123f,-65.0000f),Vector3D(96.2397f,284.3766f,-65.0000f),Vector3D(-10.0785f,192.8380f,-65.0000f),Vector3D(2.7941f,147.5455f,-65.0000f),Vector3D(20.9111f,166.6161f,-65.0000f),Vector3D(21.8646f,190.9310f,-65.0000f),Vector3D(32.3534f,200.9430f,-65.0000f),Vector3D(53.3310f,230.9791f,-65.0000f),Vector3D(15.6667f,132.2891f,-65.0000f),Vector3D(74.3086f,186.6401f,-65.0000f),Vector3D(48.5633f,145.1617f,-65.0000f),Vector3D(84.7973f,172.3372f,-65.0000f),Vector3D(151.5442f,176.6281f,-65.0000f),Vector3D(186.8247f,185.2098f,-65.0000f),Vector3D(67.1571f,147.5455f,-65.0000f),Vector3D(90.0417f,165.1858f,-65.0000f),Vector3D(107.2052f,147.0688f,-65.0000f),Vector3D(134.8575f,167.0928f,-65.0000f),Vector3D(19.0040f,127.0447f,-65.0000f),Vector3D(52.8542f,139.9173f,-65.0000f),Vector3D(129.6131f,124.6609f,-65.0000f),Vector3D(114.3567f,139.4406f,-65.0000f),Vector3D(153.9280f,171.3837f,-65.0000f),Vector3D(188.2550f,180.4422f,-65.0000f),Vector3D(2.3173f,108.4509f,-65.0000f),Vector3D(12.3293f,96.5319f,-65.0000f),Vector3D(15.6667f,40.2738f,-65.0000f),Vector3D(2.3173f,13.5751f,-65.0000f),Vector3D(30.9231f,37.4132f,-65.0000f),Vector3D(48.5633f,25.9709f,-65.0000f),Vector3D(10.4223f,112.7418f,-65.0000f),Vector3D(48.0866f,110.3580f,-65.0000f),Vector3D(20.9111f,99.3924f,-65.0000f),Vector3D(35.6907f,94.6248f,-65.0000f),Vector3D(41.4119f,46.4717f,-65.0000f),Vector3D(52.3774f,35.5062f,-65.0000f),Vector3D(58.5754f,110.8348f,-65.0000f),Vector3D(70.4944f,101.7763f,-65.0000f),Vector3D(62.3895f,33.1224f,-65.0000f),Vector3D(77.6459f,56.0070f,-65.0000f),Vector3D(90.0417f,53.1464f,-65.0000f),Vector3D(102.9143f,45.9950f,-65.0000f),Vector3D(70.0177f,113.2186f,-65.0000f),Vector3D(105.2982f,110.8348f,-65.0000f),Vector3D(79.5530f,104.6368f,-65.0000f),Vector3D(93.8558f,99.3924f,-65.0000f),Vector3D(100.5305f,58.3908f,-65.0000f),Vector3D(112.4496f,50.7626f,-65.0000f),Vector3D(112.4496f,110.8348f,-65.0000f),Vector3D(124.3687f,103.2065f,-65.0000f),Vector3D(123.4152f,51.7161f,-65.0000f),Vector3D(140.5786f,75.5543f,-65.0000f),Vector3D(160.1259f,74.6008f,-65.0000f),Vector3D(177.7662f,67.4493f,-65.0000f),Vector3D(-123.8090f,93.5348f,-65.0000f),Vector3D(-109.3982f,89.0057f,-65.0000f),Vector3D(-69.8712f,104.0342f,-65.0000f),Vector3D(-71.9299f,112.6807f,-65.0000f),Vector3D(-28.9032f,131.8266f,-65.0000f),Vector3D(-33.4323f,120.0920f,-65.0000f),Vector3D(-296.1408f,194.8713f,-65.0000f),Vector3D(-295.2308f,155.7414f,-65.0000f),Vector3D(-254.2810f,154.8314f,-65.0000f),Vector3D(-255.6460f,193.9613f,-65.0000f),Vector3D(-295.2308f,208.0662f,-65.0000f),Vector3D(-295.2308f,244.0111f,-65.0000f),Vector3D(-256.5560f,244.0111f,-65.0000f),Vector3D(-257.4660f,208.0662f,-65.0000f),Vector3D(-245.1811f,242.6461f,-65.0000f),Vector3D(-244.7261f,207.1562f,-65.0000f),Vector3D(-208.3262f,242.6461f,-65.0000f),Vector3D(-208.3262f,207.6112f,-65.0000f),Vector3D(-242.9061f,192.1413f,-65.0000f),Vector3D(-241.9961f,157.5614f,-65.0000f),Vector3D(-207.4162f,156.1964f,-65.0000f),Vector3D(-206.9612f,192.5963f,-65.0000f)};
    IndexGroup basisIndexes[84] = {IndexGroup(2,1,0),IndexGroup(3,1,2),IndexGroup(3,4,1),IndexGroup(4,5,1),IndexGroup(4,6,5),IndexGroup(6,7,5),IndexGroup(9,8,7),IndexGroup(9,7,6),IndexGroup(9,10,8),IndexGroup(10,11,8),IndexGroup(10,12,11),IndexGroup(10,13,12),IndexGroup(14,15,16),IndexGroup(15,17,16),IndexGroup(18,19,20),IndexGroup(19,21,20),IndexGroup(24,23,22),IndexGroup(22,25,24),IndexGroup(26,27,28),IndexGroup(28,29,26),IndexGroup(28,30,29),IndexGroup(30,31,29),IndexGroup(30,32,31),IndexGroup(32,33,31),IndexGroup(32,34,33),IndexGroup(32,35,34),IndexGroup(38,37,36),IndexGroup(38,39,37),IndexGroup(38,40,39),IndexGroup(38,41,40),IndexGroup(44,43,42),IndexGroup(44,45,43),IndexGroup(45,46,43),IndexGroup(46,47,43),IndexGroup(48,49,50),IndexGroup(49,51,50),IndexGroup(50,51,52),IndexGroup(52,53,50),IndexGroup(54,55,56),IndexGroup(57,54,56),IndexGroup(58,54,57),IndexGroup(54,58,59),IndexGroup(62,61,60),IndexGroup(63,61,62),IndexGroup(63,64,61),IndexGroup(64,65,61),IndexGroup(68,67,66),IndexGroup(68,69,67),IndexGroup(72,71,70),IndexGroup(72,73,71),IndexGroup(72,74,73),IndexGroup(72,75,74),IndexGroup(78,77,76),IndexGroup(76,79,78),IndexGroup(79,80,78),IndexGroup(79,81,80),IndexGroup(84,83,82),IndexGroup(84,85,83),IndexGroup(86,83,85),IndexGroup(86,87,83),IndexGroup(90,89,88),IndexGroup(90,91,89),IndexGroup(90,92,91),IndexGroup(90,93,92),IndexGroup(96,95,94),IndexGroup(96,97,95),IndexGroup(97,98,95),IndexGroup(95,98,99),IndexGroup(102,101,100),IndexGroup(102,103,101),IndexGroup(102,104,103),IndexGroup(102,105,104),IndexGroup(106,107,108),IndexGroup(108,109,106),IndexGroup(108,110,109),IndexGroup(108,111,110),IndexGroup(112,113,114),IndexGroup(114,115,112),IndexGroup(118,117,116),IndexGroup(116,119,118),IndexGroup(120,121,122),IndexGroup(121,123,122),IndexGroup(124,125,126),IndexGroup(126,127,124)};
    TriangleGroup triangleGroup = TriangleGroup(&basisVertices[0], &basisIndexes[0], 128, 84);
    SimpleMaterial simpleMaterial = SimpleMaterial(RGBColor(128, 128, 128));
    Object3D basisObj = Object3D(&triangleGroup, &simpleMaterial);

    static const byte morphCount = 38;
    int HideSecondEyeIndexes[3] = {107,108,111};
    int HideBlushIndexes[6] = {15,17,18,19,22,23};
    int TopFinOuterThinIndexes[3] = {49,51,52};
    int TopFinInnerThinIndexes[3] = {56,57,58};
    int MidFinTopThinIndexes[3] = {62,63,64};
    int MidFinBotThinIndexes[3] = {71,73,74};
    int MidFinMidBiggerIndexes[4] = {66,67,68,69};
    int BotFinLR1ThinIndexes[3] = {77,78,80};
    int BotFinLR2ThinIndexes[3] = {84,85,86};
    int BotFinLR3ThinIndexes[3] = {89,91,92};
    int BotFinLR4ThinIndexes[3] = {96,97,98};
    int BotFinLR5ThinIndexes[3] = {101,103,104};
    int TopFinInnerCloseGapIndexes[3] = {54,55,59};
    int ShockedMouthIndexes[12] = {1,3,4,5,6,7,8,9,10,11,12,13};
    int HappyMouthIndexes[14] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13};
    int OwOMouthIndexes[14] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13};
    int UpsetMouthIndexes[10] = {4,5,6,7,8,9,10,11,12,13};
    int SillyMouthIndexes[14] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13};
    int FlatMouthIndexes[12] = {1,3,4,5,6,7,8,9,10,11,12,13};
    int OpenToothMouthIndexes[14] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13};
    int SadMouthIndexes[12] = {1,3,4,5,6,7,8,9,10,11,12,13};
    int PogMouthIndexes[13] = {0,1,3,4,5,6,7,8,9,10,11,12,13};
    int DerpyMouthIndexes[12] = {1,3,4,5,6,7,8,9,10,11,12,13};
    int SkinnyEyeIndexes[14] = {26,27,28,29,30,31,32,33,34,35,124,125,126,127};
    int SadEyeIndexes[5] = {26,29,31,33,34};
    int CircleEyeIndexes[9] = {26,27,28,30,31,32,33,34,35};
    int HeartEyeIndexes[10] = {26,27,28,29,30,31,32,33,34,35};
    int ClosedEyeIndexes[8] = {26,28,29,30,31,33,34,35};
    int BlushEyeIndexes[9] = {26,27,28,29,30,31,32,33,34};
    int ClosedEyeBrowIndexes[6] = {36,37,38,39,40,41};
    int AngryEyeIndexes[5] = {26,29,31,33,34};
    int DeadEyeIndexes[16] = {26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41};
    int HideEyeBrowIndexes[3] = {36,38,41};
    int SadEyeBrowIndexes[6] = {36,37,38,39,40,41};
    int AngryEyeBrowIndexes[6] = {36,37,38,39,40,41};
    int OwOIndexes[112] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,96,97,98,99,100,101,102,103,104,105,106,107,108,109,110,111};
    int NewFinsIndexes[41] = {49,51,52,54,55,56,57,58,59,62,63,64,66,69,71,73,74,78,80,82,83,84,85,86,87,88,89,90,91,92,93,94,96,97,98,99,101,102,103,104,105};
    int AngryEyeMouthIndexes[21] = {0,1,3,5,6,7,8,9,10,11,12,13,26,27,28,29,31,32,33,34,35};

    Vector3D HideSecondEyeVectors[3] = {Vector3D(-14.4109f,4.5291f,0.0000f),Vector3D(-2.0587f,8.6465f,0.0000f),Vector3D(4.5291f,11.7346f,0.0000f)};
    Vector3D HideBlushVectors[6] = {Vector3D(-17.9593f,17.4169f,0.0000f),Vector3D(-4.3805f,22.4955f,0.0000f),Vector3D(-3.0445f,23.6403f,0.0000f),Vector3D(-10.7900f,11.2929f,0.0000f),Vector3D(3.0998f,19.0537f,0.0000f),Vector3D(-7.7612f,11.5198f,0.0000f)};
    Vector3D TopFinOuterThinVectors[3] = {Vector3D(-3.8141f,-7.6282f,0.0000f),Vector3D(-37.1875f,6.1979f,0.0000f),Vector3D(34.3270f,37.6643f,0.0000f)};
    Vector3D TopFinInnerThinVectors[3] = {Vector3D(-18.1170f,-19.0705f,0.0000f),Vector3D(-31.9431f,1.9070f,0.0000f),Vector3D(20.9776f,30.0361f,0.0000f)};
    Vector3D MidFinTopThinVectors[3] = {Vector3D(-32.8967f,-12.8726f,0.0000f),Vector3D(-10.4888f,14.3029f,0.0000f),Vector3D(35.2805f,8.5817f,0.0000f)};
    Vector3D MidFinBotThinVectors[3] = {Vector3D(-33.8502f,-12.8726f,0.0000f),Vector3D(15.2564f,-14.7797f,0.0000f),Vector3D(34.3270f,9.0585f,0.0000f)};
    Vector3D MidFinMidBiggerVectors[4] = {Vector3D(-22.7499f,-7.2800f,0.0000f),Vector3D(-8.6450f,11.3750f,0.0000f),Vector3D(11.3750f,-10.9200f,0.0000f),Vector3D(25.4799f,8.6450f,0.0000f)};
    Vector3D BotFinLR1ThinVectors[3] = {Vector3D(-10.0120f,11.9191f,0.0000f),Vector3D(-13.3494f,-26.6987f,0.0000f),Vector3D(17.6402f,-11.4423f,0.0000f)};
    Vector3D BotFinLR2ThinVectors[3] = {Vector3D(-10.4888f,13.3494f,0.0000f),Vector3D(12.3982f,15.7309f,0.0678f),Vector3D(10.9656f,-10.9656f,0.0000f)};
    Vector3D BotFinLR3ThinVectors[3] = {Vector3D(-11.9191f,9.0585f,0.0000f),Vector3D(-15.2564f,-22.8846f,0.0000f),Vector3D(12.8726f,-7.1514f,0.0000f)};
    Vector3D BotFinLR4ThinVectors[3] = {Vector3D(-9.5353f,8.5817f,0.0000f),Vector3D(11.4423f,11.4423f,0.0000f),Vector3D(11.9191f,-7.6282f,0.0000f)};
    Vector3D BotFinLR5ThinVectors[3] = {Vector3D(-11.9191f,7.6282f,0.0000f),Vector3D(-17.1635f,-23.8382f,0.0000f),Vector3D(17.6402f,-7.1514f,0.0000f)};
    Vector3D TopFinInnerCloseGapVectors[3] = {Vector3D(-15.8470f,4.6954f,0.0000f),Vector3D(-5.8693f,-4.4019f,0.0000f),Vector3D(18.7816f,26.7051f,0.0000f)};
    Vector3D ShockedMouthVectors[12] = {Vector3D(-16.7474f,1.0150f,0.0000f),Vector3D(-15.7324f,4.0600f,0.0000f),Vector3D(-25.8824f,-8.1200f,0.0000f),Vector3D(-25.8824f,-8.1200f,0.0000f),Vector3D(-57.3473f,-1.5225f,0.0000f),Vector3D(-57.3473f,-1.5225f,0.0000f),Vector3D(-40.5998f,-39.5848f,0.0000f),Vector3D(-40.5998f,-39.5848f,0.0000f),Vector3D(-34.5099f,-15.2249f,0.0000f),Vector3D(-41.1073f,-16.2399f,0.0000f),Vector3D(-29.9424f,-13.1949f,0.0000f),Vector3D(-26.3899f,-14.2099f,0.0000f)};
    Vector3D HappyMouthVectors[14] = {Vector3D(-15.2249f,15.7324f,0.0000f),Vector3D(-7.6125f,2.5375f,0.0000f),Vector3D(-15.2249f,15.7324f,0.0000f),Vector3D(-7.6125f,2.5375f,0.0000f),Vector3D(-7.1050f,0.0000f,0.0000f),Vector3D(-7.1050f,0.0000f,0.0000f),Vector3D(-23.3449f,5.0750f,0.0000f),Vector3D(-23.3449f,5.0750f,0.0000f),Vector3D(-14.2099f,-24.8674f,0.0000f),Vector3D(-14.2099f,-21.8224f,0.0000f),Vector3D(-14.7174f,-7.1050f,0.0000f),Vector3D(-24.3599f,-8.6275f,0.0000f),Vector3D(-20.2999f,29.9424f,0.0000f),Vector3D(-14.2099f,30.9574f,0.0000f)};
    Vector3D OwOMouthVectors[14] = {Vector3D(-14.7174f,14.2099f,0.0000f),Vector3D(6.0900f,-22.3299f,0.0000f),Vector3D(-14.7174f,14.2099f,0.0000f),Vector3D(6.0900f,-22.3299f,0.0000f),Vector3D(-11.6724f,31.4649f,0.0000f),Vector3D(-11.6724f,31.4649f,0.0000f),Vector3D(-13.1949f,-20.2999f,0.0000f),Vector3D(-13.1949f,-20.2999f,0.0000f),Vector3D(-7.6125f,2.5375f,0.0000f),Vector3D(-7.6125f,4.0600f,0.0000f),Vector3D(-12.6874f,7.1050f,0.0000f),Vector3D(-21.3149f,-0.5075f,0.0000f),Vector3D(-25.6102f,20.8806f,0.0000f),Vector3D(-19.5465f,24.3912f,0.0000f)};
    Vector3D UpsetMouthVectors[10] = {Vector3D(-11.8257f,6.9563f,0.0000f),Vector3D(-12.5213f,9.0432f,0.0000f),Vector3D(-41.0421f,-19.4776f,0.0000f),Vector3D(-36.8683f,-16.6951f,0.0000f),Vector3D(-38.9552f,-40.3465f,0.0000f),Vector3D(-41.7377f,-36.8683f,0.0000f),Vector3D(-32.6946f,-41.0421f,0.0000f),Vector3D(-39.6508f,-45.9115f,0.0000f),Vector3D(-24.3470f,-29.9120f,0.0000f),Vector3D(-24.3470f,-29.9120f,0.0000f)};
    Vector3D SillyMouthVectors[14] = {Vector3D(-0.6956f,2.7825f,0.0000f),Vector3D(-10.4344f,2.0869f,0.0000f),Vector3D(-0.6956f,2.7825f,0.0000f),Vector3D(-10.4344f,2.0869f,0.0000f),Vector3D(-49.3896f,18.7820f,0.0000f),Vector3D(-49.3896f,18.7820f,0.0000f),Vector3D(-77.2148f,-25.0426f,0.0000f),Vector3D(-74.4323f,-24.3470f,0.0000f),Vector3D(-85.7353f,-47.8176f,0.0000f),Vector3D(-88.3409f,-40.8692f,0.0000f),Vector3D(-76.8665f,-16.9367f,0.0000f),Vector3D(-89.4604f,-22.1480f,0.0000f),Vector3D(-85.1177f,4.7770f,0.0000f),Vector3D(-79.9064f,4.7770f,0.0000f)};
    Vector3D FlatMouthVectors[12] = {Vector3D(2.0869f,-19.4776f,0.0000f),Vector3D(0.9707f,-17.9894f,0.0000f),Vector3D(-1.3913f,-2.7825f,0.0000f),Vector3D(-1.3913f,-2.7825f,0.0000f),Vector3D(-11.8257f,-26.4339f,0.0000f),Vector3D(-14.4301f,-25.6898f,0.0000f),Vector3D(-7.7974f,-47.6422f,0.0000f),Vector3D(-8.9136f,-40.9451f,0.0000f),Vector3D(-1.2943f,-40.2980f,0.0000f),Vector3D(-4.6428f,-46.9951f,0.0000f),Vector3D(3.4781f,-22.9558f,0.0000f),Vector3D(3.4781f,-22.9558f,0.0000f)};
    Vector3D OpenToothMouthVectors[14] = {Vector3D(-10.6575f,11.6724f,0.0000f),Vector3D(-18.2699f,-7.1050f,0.0000f),Vector3D(10.5268f,-9.6720f,0.0000f),Vector3D(5.0632f,-23.9225f,0.0000f),Vector3D(-18.2057f,-3.2925f,0.0000f),Vector3D(-45.1673f,3.5525f,0.0000f),Vector3D(-49.3744f,-25.3825f,0.0000f),Vector3D(-72.0647f,-7.6125f,0.0000f),Vector3D(-68.5122f,-23.3449f,0.0000f),Vector3D(-52.2853f,-36.8848f,0.0000f),Vector3D(-48.0651f,-29.1290f,0.0000f),Vector3D(-67.4972f,-23.8524f,0.0000f),Vector3D(-58.3623f,-0.5075f,0.0000f),Vector3D(-52.6492f,0.0296f,0.0000f)};
    Vector3D SadMouthVectors[12] = {Vector3D(0.5075f,-11.1650f,0.0000f),Vector3D(0.5075f,-11.1650f,0.0000f),Vector3D(-15.2249f,8.6275f,0.0000f),Vector3D(-15.2249f,8.6275f,0.0000f),Vector3D(-42.4800f,-15.7474f,0.0000f),Vector3D(-41.1626f,-15.2068f,0.0000f),Vector3D(-40.3859f,-40.8949f,0.0000f),Vector3D(-43.9411f,-33.0826f,0.0000f),Vector3D(-41.4052f,-40.2979f,0.0000f),Vector3D(-47.8688f,-48.1648f,0.0000f),Vector3D(-50.9916f,-30.5403f,0.0000f),Vector3D(-45.0997f,-27.7536f,0.0000f)};
    Vector3D PogMouthVectors[13] = {Vector3D(-2.9690f,2.3752f,0.0000f),Vector3D(-3.5628f,3.5628f,0.0000f),Vector3D(-17.9364f,-21.9044f,0.0000f),Vector3D(-54.1295f,-9.9248f,0.0000f),Vector3D(-20.1890f,12.4697f,0.0000f),Vector3D(-93.3200f,-36.9001f,0.0000f),Vector3D(-48.0973f,10.0945f,0.0000f),Vector3D(-68.3951f,-18.8739f,0.0000f),Vector3D(-101.4822f,-52.6969f,0.0000f),Vector3D(-105.0918f,-50.8965f,0.0000f),Vector3D(-95.6587f,-36.1917f,0.0000f),Vector3D(-107.1226f,-23.3102f,0.0000f),Vector3D(-105.8784f,-25.1127f,0.0000f)};
    Vector3D DerpyMouthVectors[12] = {Vector3D(-3.7206f,-27.1606f,0.0000f),Vector3D(-5.2089f,-24.5562f,0.0000f),Vector3D(-36.8342f,-8.9295f,0.0000f),Vector3D(-36.8342f,-8.9295f,0.0000f),Vector3D(-73.2964f,-27.1606f,0.0000f),Vector3D(-73.2964f,-27.1606f,0.0000f),Vector3D(-85.5745f,-36.4622f,0.0000f),Vector3D(-85.5745f,-36.4622f,0.0000f),Vector3D(-90.7834f,-16.7428f,0.0000f),Vector3D(-106.7821f,-26.4165f,0.0000f),Vector3D(-113.4792f,7.0692f,0.0000f),Vector3D(-104.1776f,11.1619f,0.0000f)};
    Vector3D SkinnyEyeVectors[14] = {Vector3D(5.6861f,29.3845f,0.0000f),Vector3D(9.8077f,1.8751f,0.0000f),Vector3D(-5.3608f,39.6135f,0.0000f),Vector3D(31.4924f,34.3170f,0.0000f),Vector3D(-4.1514f,49.7102f,0.0000f),Vector3D(58.1696f,-13.0243f,0.0000f),Vector3D(8.8329f,18.3519f,0.0000f),Vector3D(-25.0369f,-70.0344f,0.0000f),Vector3D(-38.8831f,-43.5666f,0.0000f),Vector3D(-61.7678f,-29.2637f,0.0000f),Vector3D(146.2873f,-47.2281f,0.0000f),Vector3D(142.0408f,-60.5030f,0.0000f),Vector3D(115.5458f,-46.9731f,0.0000f),Vector3D(114.2275f,-41.0432f,0.0000f)};
    Vector3D SadEyeVectors[5] = {Vector3D(-5.1063f,-1.2766f,0.0000f),Vector3D(-2.2340f,-4.1488f,0.0000f),Vector3D(-2.8723f,-17.8720f,0.0000f),Vector3D(-0.9574f,-32.2334f,0.0000f),Vector3D(6.3828f,-14.6805f,0.0000f)};
    Vector3D CircleEyeVectors[9] = {Vector3D(3.1914f,8.2977f,0.0000f),Vector3D(10.8508f,17.8720f,0.0000f),Vector3D(-7.0211f,-3.1914f,0.0000f),Vector3D(-12.0452f,-16.5691f,0.0000f),Vector3D(-1.3993f,6.0273f,0.0000f),Vector3D(2.2340f,-11.8083f,0.0000f),Vector3D(0.9574f,-2.8723f,0.0000f),Vector3D(-1.2766f,-1.5957f,0.0000f),Vector3D(-18.5102f,-10.2125f,0.0000f)};
    Vector3D HeartEyeVectors[10] = {Vector3D(-5.2995f,25.6314f,0.0000f),Vector3D(6.8012f,33.8425f,0.0000f),Vector3D(-4.4650f,9.5780f,0.0000f),Vector3D(-0.1156f,20.3571f,0.0000f),Vector3D(-6.9726f,-8.9430f,0.0000f),Vector3D(2.7603f,1.5471f,0.0000f),Vector3D(-8.1922f,-3.3413f,0.0000f),Vector3D(2.4814f,0.4080f,0.0000f),Vector3D(-3.8981f,6.5557f,0.0000f),Vector3D(-27.0084f,2.5740f,0.0000f)};
    Vector3D ClosedEyeVectors[8] = {Vector3D(-0.3191f,-15.9571f,0.0000f),Vector3D(0.6383f,-1.9149f,0.0000f),Vector3D(9.8934f,-30.3185f,0.0000f),Vector3D(-1.8327f,-3.4842f,0.0000f),Vector3D(13.0848f,-34.1482f,0.0000f),Vector3D(13.0848f,-34.1482f,0.0000f),Vector3D(3.8297f,-7.0211f,0.0000f),Vector3D(-10.8508f,6.0637f,0.0000f)};
    Vector3D BlushEyeVectors[9] = {Vector3D(33.1908f,45.3182f,0.0000f),Vector3D(21.5888f,34.0887f,0.0000f),Vector3D(-18.5102f,-8.6168f,0.0000f),Vector3D(29.3611f,17.2337f,0.0000f),Vector3D(-32.8716f,-13.7231f,0.0000f),Vector3D(-8.6168f,-39.5736f,0.0000f),Vector3D(-20.4251f,-8.2977f,0.0000f),Vector3D(-7.6594f,-44.6799f,0.0000f),Vector3D(11.8083f,-10.8508f,0.0000f)};
    Vector3D ClosedEyeBrowVectors[6] = {Vector3D(2.5531f,6.3828f,0.0000f),Vector3D(14.3614f,10.8508f,0.0000f),Vector3D(22.6591f,-0.3191f,0.0000f),Vector3D(24.5740f,-2.2340f,0.0000f),Vector3D(19.4677f,-14.6805f,0.0000f),Vector3D(19.4677f,-14.6805f,0.0000f)};
    Vector3D AngryEyeVectors[5] = {Vector3D(6.0637f,-11.4891f,0.0000f),Vector3D(11.8083f,-16.5954f,0.0000f),Vector3D(7.3403f,-11.4891f,0.0000f),Vector3D(-0.9574f,-7.9786f,0.0000f),Vector3D(-0.9574f,-3.8297f,0.0000f)};
    Vector3D DeadEyeVectors[16] = {Vector3D(-6.6675f,-13.7572f,0.0000f),Vector3D(6.3140f,3.8707f,0.0000f),Vector3D(-2.1196f,6.4183f,0.0000f),Vector3D(14.9584f,-8.8390f,0.0000f),Vector3D(-7.1227f,12.0768f,0.0000f),Vector3D(11.5114f,-8.7438f,0.0000f),Vector3D(-10.0489f,16.2494f,0.0000f),Vector3D(9.4605f,-6.9381f,0.0000f),Vector3D(-1.9671f,0.3934f,0.0000f),Vector3D(-24.8517f,14.6963f,0.0000f),Vector3D(70.0926f,0.9298f,0.0000f),Vector3D(66.2927f,-16.3140f,0.0000f),Vector3D(26.6246f,-5.7875f,0.0000f),Vector3D(22.0603f,-18.6197f,0.0000f),Vector3D(-28.7986f,-20.1142f,0.0000f),Vector3D(-38.4438f,-11.5366f,0.0000f)};
    Vector3D HideEyeBrowVectors[3] = {Vector3D(-3.8141f,10.4888f,0.0000f),Vector3D(-4.7676f,8.1050f,0.0000f),Vector3D(-16.2099f,2.3838f,0.0000f)};
    Vector3D SadEyeBrowVectors[6] = {Vector3D(15.3188f,30.6377f,0.0000f),Vector3D(26.4888f,27.1271f,0.0000f),Vector3D(37.0205f,-3.8297f,0.0000f),Vector3D(37.0205f,-3.8297f,0.0000f),Vector3D(52.6585f,-22.6591f,0.0000f),Vector3D(47.5522f,-24.8931f,0.0000f)};
    Vector3D AngryEyeBrowVectors[6] = {Vector3D(3.8297f,-10.8508f,0.0000f),Vector3D(9.5743f,-9.5743f,0.0000f),Vector3D(17.8720f,-7.6594f,0.0000f),Vector3D(17.8720f,-7.6594f,0.0000f),Vector3D(9.7007f,-9.1705f,0.0000f),Vector3D(3.9561f,-6.9365f,0.0000f)};
    Vector3D OwOVectors[112] = {Vector3D(18.4569f,83.8868f,0.0000f),Vector3D(19.4900f,-13.0609f,0.0000f),Vector3D(-12.3074f,84.6132f,0.0000f),Vector3D(-5.5531f,-9.9506f,0.0000f),Vector3D(-38.0856f,9.9486f,0.0000f),Vector3D(-4.5735f,12.4346f,0.0000f),Vector3D(-80.1656f,-25.6960f,0.0000f),Vector3D(-47.4822f,-10.9268f,0.0000f),Vector3D(-94.7614f,42.6355f,0.0000f),Vector3D(-54.0600f,-24.5978f,0.0000f),Vector3D(-67.9295f,-14.1860f,0.0000f),Vector3D(-94.9867f,50.4908f,0.0000f),Vector3D(-72.9760f,-1.6412f,0.0000f),Vector3D(-67.2548f,5.5103f,0.0000f),Vector3D(58.9225f,-141.1768f,0.0000f),Vector3D(58.9225f,-141.1768f,0.0000f),Vector3D(58.9225f,-141.1768f,0.0000f),Vector3D(58.9225f,-141.1768f,0.0000f),Vector3D(58.9225f,-141.1768f,0.0000f),Vector3D(58.9225f,-141.1768f,0.0000f),Vector3D(58.9225f,-141.1768f,0.0000f),Vector3D(58.9225f,-141.1768f,0.0000f),Vector3D(-7.2815f,-35.8781f,0.0000f),Vector3D(-20.8822f,-44.6869f,0.0000f),Vector3D(-21.4531f,-34.5009f,0.0000f),Vector3D(-18.7134f,-33.2260f,0.0000f),Vector3D(91.3549f,22.9060f,0.0000f),Vector3D(76.3238f,39.8424f,0.0000f),Vector3D(72.8391f,-25.3875f,0.0000f),Vector3D(105.9871f,-50.4289f,0.0000f),Vector3D(38.6248f,-39.5656f,0.0000f),Vector3D(77.3593f,-67.0402f,0.0000f),Vector3D(28.8398f,-68.8996f,0.0000f),Vector3D(65.8020f,-102.0459f,0.0000f),Vector3D(43.8709f,-87.7430f,0.0000f),Vector3D(-0.7195f,-81.7722f,0.0000f),Vector3D(25.8736f,2.3255f,0.0000f),Vector3D(51.3934f,0.1688f,0.0000f),Vector3D(37.1685f,-84.3587f,0.0000f),Vector3D(63.6418f,-84.1317f,0.0000f),Vector3D(26.0902f,-107.8450f,0.0000f),Vector3D(9.8803f,-105.4612f,0.0000f),Vector3D(25.2442f,43.4868f,0.0000f),Vector3D(13.9268f,26.6874f,0.0000f),Vector3D(27.5154f,41.4549f,0.0000f),Vector3D(23.7013f,26.6752f,0.0000f),Vector3D(43.8640f,36.3127f,0.0000f),Vector3D(33.5001f,38.1071f,0.0000f),Vector3D(-15.9047f,26.9593f,0.0000f),Vector3D(-8.8659f,23.4971f,0.0000f),Vector3D(88.3608f,-110.2862f,0.0000f),Vector3D(11.1582f,-32.2842f,0.0000f),Vector3D(-75.9647f,-71.4914f,0.0000f),Vector3D(-95.2727f,-115.8426f,0.0000f),Vector3D(39.4381f,-0.9531f,0.0000f),Vector3D(-16.8460f,27.6753f,0.0000f),Vector3D(-19.9441f,1.9180f,0.0000f),Vector3D(0.8081f,-14.0649f,0.0000f),Vector3D(1.1722f,-19.9109f,0.0000f),Vector3D(-19.8054f,-49.9470f,0.0000f),Vector3D(28.7118f,52.9090f,0.0000f),Vector3D(-0.7679f,-77.4121f,0.0000f),Vector3D(-25.8906f,31.7044f,0.0000f),Vector3D(-32.9625f,-71.4413f,0.0000f),Vector3D(-99.7093f,-75.7321f,0.0000f),Vector3D(-124.1369f,-80.1478f,0.0000f),Vector3D(-43.7148f,-70.0005f,0.0000f),Vector3D(-70.7655f,-76.7879f,0.0000f),Vector3D(-40.3514f,-52.8596f,0.0000f),Vector3D(-72.1697f,-62.0308f,0.0000f),Vector3D(196.8170f,-1.1365f,0.0000f),Vector3D(196.8170f,-1.1365f,0.0000f),Vector3D(163.9203f,-12.5788f,0.0000f),Vector3D(163.9203f,-12.5788f,0.0000f),Vector3D(163.9203f,-12.5788f,0.0000f),Vector3D(163.9203f,-12.5788f,0.0000f),Vector3D(-23.0561f,51.7510f,0.0000f),Vector3D(17.7998f,-3.9680f,0.0000f),Vector3D(3.6096f,48.1241f,0.0000f),Vector3D(6.1061f,70.6568f,0.0000f),Vector3D(-11.6468f,50.9846f,0.0000f),Vector3D(-40.1399f,58.2609f,0.0000f),Vector3D(108.8270f,-119.2356f,0.0000f),Vector3D(108.8270f,-119.2356f,0.0000f),Vector3D(108.8270f,-119.2356f,0.0000f),Vector3D(111.0363f,-115.4475f,0.0000f),Vector3D(108.8270f,-119.2356f,0.0000f),Vector3D(108.8270f,-119.2356f,0.0000f),Vector3D(196.8065f,-25.3840f,0.0000f),Vector3D(196.8065f,-25.3840f,0.0000f),Vector3D(196.8065f,-25.3840f,0.0000f),Vector3D(196.8065f,-25.3840f,0.0000f),Vector3D(196.8065f,-25.3840f,0.0000f),Vector3D(196.8065f,-25.3840f,0.0000f),Vector3D(137.7277f,-5.0120f,0.0000f),Vector3D(137.7277f,-5.0120f,0.0000f),Vector3D(137.7277f,-5.0120f,0.0000f),Vector3D(137.7277f,-5.0120f,0.0000f),Vector3D(137.7277f,-5.0120f,0.0000f),Vector3D(137.7277f,-5.0120f,0.0000f),Vector3D(75.0486f,-113.9227f,0.0000f),Vector3D(75.0486f,-113.9227f,0.0000f),Vector3D(75.0486f,-113.9227f,0.0000f),Vector3D(75.0486f,-113.9227f,0.0000f),Vector3D(75.0486f,-113.9227f,0.0000f),Vector3D(75.0486f,-113.9227f,0.0000f),Vector3D(73.8020f,-19.2803f,0.0000f),Vector3D(70.2440f,-10.5851f,0.0000f),Vector3D(30.7171f,-25.6136f,0.0000f),Vector3D(21.9229f,-38.4261f,0.0000f),Vector3D(-37.7679f,-14.1605f,0.0000f),Vector3D(-22.3859f,1.7401f,0.0000f)};
    Vector3D NewFinsVectors[41] = {Vector3D(-2.9582f,4.4372f,0.0000f),Vector3D(-23.1722f,3.2047f,0.0000f),Vector3D(19.9675f,21.9396f,0.0000f),Vector3D(94.9074f,24.6512f,0.0000f),Vector3D(-7.8884f,-13.3117f,0.0000f),Vector3D(-25.1443f,-22.9257f,0.0000f),Vector3D(51.7676f,26.8699f,0.0000f),Vector3D(49.0560f,68.0375f,0.0000f),Vector3D(42.8932f,53.4932f,0.0000f),Vector3D(-18.8138f,-7.0996f,0.0000f),Vector3D(-6.0346f,8.5195f,0.0000f),Vector3D(18.8139f,3.9048f,0.0000f),Vector3D(22.8846f,17.6402f,0.0000f),Vector3D(-27.6523f,-20.0240f,0.0000f),Vector3D(-23.4286f,-8.5195f,0.0000f),Vector3D(10.6493f,-8.5195f,0.0000f),Vector3D(20.5887f,6.0346f,0.0000f),Vector3D(-3.3641f,-16.3224f,0.0000f),Vector3D(8.6279f,-5.5465f,0.0000f),Vector3D(-8.1050f,-4.2909f,0.0000f),Vector3D(-8.2102f,-1.5407f,0.0000f),Vector3D(-8.5817f,-2.8606f,0.0000f),Vector3D(0.6300f,5.0124f,0.0000f),Vector3D(40.1953f,57.4804f,0.0000f),Vector3D(22.4335f,74.2886f,0.0000f),Vector3D(-10.0120f,-84.8639f,0.0000f),Vector3D(-31.7651f,-70.1150f,0.0000f),Vector3D(9.3675f,0.2465f,0.0000f),Vector3D(6.1069f,-11.8589f,0.0000f),Vector3D(77.8526f,14.5618f,0.0000f),Vector3D(73.0769f,18.2595f,0.0000f),Vector3D(3.0814f,-3.5950f,0.0000f),Vector3D(0.6848f,-0.6848f,0.0000f),Vector3D(18.6596f,7.5323f,0.0000f),Vector3D(27.4331f,49.0955f,0.0000f),Vector3D(0.0000f,60.0722f,0.0000f),Vector3D(2.9102f,4.1085f,0.0000f),Vector3D(5.9030f,59.2590f,0.0000f),Vector3D(3.3608f,11.8301f,0.0000f),Vector3D(4.0329f,-8.2187f,0.0000f),Vector3D(-1.7749f,-2.8398f,0.0000f)};
    Vector3D AngryEyeMouthVectors[21] = {Vector3D(-6.3896f,6.3896f,0.0000f),Vector3D(-18.8138f,9.2294f,0.0000f),Vector3D(-4.9697f,-5.6796f,0.0000f),Vector3D(-20.5887f,17.0390f,0.0000f),Vector3D(-21.2987f,8.5195f,0.0000f),Vector3D(-18.1039f,17.7489f,0.0000f),Vector3D(3.5498f,-17.7489f,0.0000f),Vector3D(4.9697f,-23.7835f,0.0000f),Vector3D(7.8095f,8.8744f,0.0000f),Vector3D(-6.0346f,7.8095f,0.0000f),Vector3D(11.0043f,35.1428f,0.0000f),Vector3D(2.8398f,33.0130f,0.0000f),Vector3D(-25.2035f,-25.2034f,0.0000f),Vector3D(0.3550f,11.3593f,0.0000f),Vector3D(2.8398f,2.4848f,0.0000f),Vector3D(-1.0649f,-8.1645f,0.0000f),Vector3D(0.7100f,1.4199f,0.0000f),Vector3D(-9.5844f,7.0996f,0.0000f),Vector3D(-5.3247f,2.8398f,0.0000f),Vector3D(-8.5195f,37.9827f,0.0000f),Vector3D(-28.3983f,22.7186f,0.0000f)};

    Morph morphs[38] = {
        Morph(3, HideSecondEyeIndexes, HideSecondEyeVectors),
        Morph(6, HideBlushIndexes, HideBlushVectors),
        Morph(3, TopFinOuterThinIndexes, TopFinOuterThinVectors),
        Morph(3, TopFinInnerThinIndexes, TopFinInnerThinVectors),
        Morph(3, MidFinTopThinIndexes, MidFinTopThinVectors),
        Morph(3, MidFinBotThinIndexes, MidFinBotThinVectors),
        Morph(4, MidFinMidBiggerIndexes, MidFinMidBiggerVectors),
        Morph(3, BotFinLR1ThinIndexes, BotFinLR1ThinVectors),
        Morph(3, BotFinLR2ThinIndexes, BotFinLR2ThinVectors),
        Morph(3, BotFinLR3ThinIndexes, BotFinLR3ThinVectors),
        Morph(3, BotFinLR4ThinIndexes, BotFinLR4ThinVectors),
        Morph(3, BotFinLR5ThinIndexes, BotFinLR5ThinVectors),
        Morph(3, TopFinInnerCloseGapIndexes, TopFinInnerCloseGapVectors),
        Morph(12, ShockedMouthIndexes, ShockedMouthVectors),
        Morph(14, HappyMouthIndexes, HappyMouthVectors),
        Morph(14, OwOMouthIndexes, OwOMouthVectors),
        Morph(10, UpsetMouthIndexes, UpsetMouthVectors),
        Morph(14, SillyMouthIndexes, SillyMouthVectors),
        Morph(12, FlatMouthIndexes, FlatMouthVectors),
        Morph(14, OpenToothMouthIndexes, OpenToothMouthVectors),
        Morph(12, SadMouthIndexes, SadMouthVectors),
        Morph(13, PogMouthIndexes, PogMouthVectors),
        Morph(12, DerpyMouthIndexes, DerpyMouthVectors),
        Morph(14, SkinnyEyeIndexes, SkinnyEyeVectors),
        Morph(5, SadEyeIndexes, SadEyeVectors),
        Morph(9, CircleEyeIndexes, CircleEyeVectors),
        Morph(10, HeartEyeIndexes, HeartEyeVectors),
        Morph(8, ClosedEyeIndexes, ClosedEyeVectors),
        Morph(9, BlushEyeIndexes, BlushEyeVectors),
        Morph(6, ClosedEyeBrowIndexes, ClosedEyeBrowVectors),
        Morph(5, AngryEyeIndexes, AngryEyeVectors),
        Morph(16, DeadEyeIndexes, DeadEyeVectors),
        Morph(3, HideEyeBrowIndexes, HideEyeBrowVectors),
        Morph(6, SadEyeBrowIndexes, SadEyeBrowVectors),
        Morph(6, AngryEyeBrowIndexes, AngryEyeBrowVectors),
        Morph(112, OwOIndexes, OwOVectors),
        Morph(41, NewFinsIndexes, NewFinsVectors),
        Morph(21, AngryEyeMouthIndexes, AngryEyeMouthVectors)
    };
    
public:
    ProtoDR(){}

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

        SetMorphWeight(HideBlush, 1.0f);
        SetMorphWeight(HideSecondEye, 1.0f);
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
