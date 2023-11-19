#pragma once

#include "Utils\Morph.h"
#include "..\..\..\Utils\Math\Rotation.h"
#include "..\..\..\Scene\Materials\Static\SimpleMaterial.h"
#include "..\..\..\Scene\Objects\Object3D.h"
#include "..\..\..\Renderer\Utils\IndexGroup.h"

class BetaFront{
public:
    enum Morphs {
        HideSecondEye,
        HideBlush,
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
        AngryEyeMouth,
        HideAll,
        AlphaGenCircle,
        vrc_v_aa,
        vrc_v_ch,
        vrc_v_dd,
        vrc_v_ee,
        vrc_v_ih,
        vrc_v_oh,
        vrc_v_ss,
        vrc_v_rr
    };

private:
    Vector3D basisVertices[54] = {Vector3D(-180.2830f,22.1568f,-65.0000f),Vector3D(-152.1540f,43.1344f,-65.0000f),Vector3D(-171.2245f,13.0983f,-65.0000f),Vector3D(-148.8166f,31.6921f,-65.0000f),Vector3D(-105.4312f,15.9589f,-65.0000f),Vector3D(-106.3847f,25.9709f,-65.0000f),Vector3D(-59.1851f,40.7506f,-65.0000f),Vector3D(-63.4760f,49.3323f,-65.0000f),Vector3D(-45.3590f,71.7402f,-65.0000f),Vector3D(-41.8793f,56.3165f,-65.0000f),Vector3D(-32.1758f,56.7576f,-65.0000f),Vector3D(-23.4279f,72.2169f,-65.0000f),Vector3D(-16.2765f,48.3788f,-65.0000f),Vector3D(-21.9976f,41.2273f,-65.0000f),Vector3D(-100.9826f,80.5753f,-65.0000f),Vector3D(-83.0233f,63.1584f,-65.0000f),Vector3D(-80.2524f,88.5146f,-65.0000f),Vector3D(-75.8719f,66.0190f,-65.0000f),Vector3D(-70.1507f,68.4028f,-65.0000f),Vector3D(-49.1731f,86.0431f,-65.0000f),Vector3D(-73.1952f,92.0431f,-65.0000f),Vector3D(-59.9632f,97.3360f,-65.0000f),Vector3D(-34.3935f,88.4269f,-65.0000f),Vector3D(-42.4984f,88.9037f,-65.0000f),Vector3D(-50.2596f,100.4235f,-65.0000f),Vector3D(-31.2936f,107.4806f,-65.0000f),Vector3D(-118.7805f,122.2771f,-65.0000f),Vector3D(-125.4552f,97.0086f,-65.0000f),Vector3D(-101.1403f,107.9742f,-65.0000f),Vector3D(-112.5826f,141.3476f,-65.0000f),Vector3D(-77.7789f,117.9862f,-65.0000f),Vector3D(-94.8077f,153.7929f,-65.0000f),Vector3D(-59.6619f,125.6144f,-65.0000f),Vector3D(-74.9183f,167.0928f,-65.0000f),Vector3D(-52.9872f,152.7899f,-65.0000f),Vector3D(-30.1026f,138.4870f,-65.0000f),Vector3D(-129.2693f,113.6953f,-65.0000f),Vector3D(-133.0834f,124.1841f,-65.0000f),Vector3D(-119.7341f,146.1152f,-65.0000f),Vector3D(-124.5017f,154.2202f,-65.0000f),Vector3D(-97.8030f,173.7675f,-65.0000f),Vector3D(-81.5930f,171.3837f,-65.0000f),Vector3D(-197.9232f,58.3908f,-65.0000f),Vector3D(-190.7718f,86.0431f,-65.0000f),Vector3D(-189.3415f,64.5887f,-65.0000f),Vector3D(-185.5274f,79.3684f,-65.0000f),Vector3D(-173.1315f,82.2290f,-65.0000f),Vector3D(-166.9336f,91.2875f,-65.0000f),Vector3D(-123.8090f,93.5348f,-65.0000f),Vector3D(-109.3982f,89.0057f,-65.0000f),Vector3D(-69.8712f,104.0342f,-65.0000f),Vector3D(-71.9299f,112.6807f,-65.0000f),Vector3D(-28.9032f,131.8266f,-65.0000f),Vector3D(-33.4323f,120.0920f,-65.0000f)};
    IndexGroup basisIndexes[38] = {IndexGroup(2,1,0),IndexGroup(3,1,2),IndexGroup(3,4,1),IndexGroup(4,5,1),IndexGroup(4,6,5),IndexGroup(6,7,5),IndexGroup(9,8,7),IndexGroup(9,7,6),IndexGroup(9,10,8),IndexGroup(10,11,8),IndexGroup(10,12,11),IndexGroup(10,13,12),IndexGroup(14,15,16),IndexGroup(15,17,16),IndexGroup(18,19,20),IndexGroup(19,21,20),IndexGroup(24,23,22),IndexGroup(22,25,24),IndexGroup(26,27,28),IndexGroup(28,29,26),IndexGroup(28,30,29),IndexGroup(30,31,29),IndexGroup(30,32,31),IndexGroup(32,33,31),IndexGroup(32,34,33),IndexGroup(32,35,34),IndexGroup(38,37,36),IndexGroup(38,39,37),IndexGroup(38,40,39),IndexGroup(38,41,40),IndexGroup(44,43,42),IndexGroup(44,45,43),IndexGroup(45,46,43),IndexGroup(46,47,43),IndexGroup(48,49,50),IndexGroup(50,51,48),IndexGroup(50,52,51),IndexGroup(50,53,52)};
    TriangleGroup triangleGroup = TriangleGroup(&basisVertices[0], &basisIndexes[0], 54, 38);
    SimpleMaterial simpleMaterial = SimpleMaterial(RGBColor(128, 128, 128));
    Object3D basisObj = Object3D(&triangleGroup, &simpleMaterial);

    static const byte morphCount = 35;
    int HideSecondEyeIndexes[3] = {49,50,53};
    int HideBlushIndexes[6] = {15,17,18,19,22,23};
    int TopFinInnerCloseGapIndexes[1] = {0};
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
    int SkinnyEyeIndexes[10] = {26,27,28,29,30,31,32,33,34,35};
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
    int AngryEyeMouthIndexes[21] = {0,1,3,5,6,7,8,9,10,11,12,13,26,27,28,29,31,32,33,34,35};
    int HideAllIndexes[32] = {0,1,5,7,8,11,12,14,16,20,21,24,25,26,27,28,29,30,31,32,33,34,35,36,38,41,44,45,46,48,51,52};
    int AlphaGenCircleIndexes[32] = {0,1,5,7,8,11,12,14,16,20,21,24,25,26,27,28,29,30,31,32,33,34,35,36,38,41,44,45,46,48,51,52};
    int vrc_v_aaIndexes[5] = {0,1,5,7,8};
    int vrc_v_chIndexes[3] = {0,1,3};
    int vrc_v_ddIndexes[6] = {2,3,4,6,9,10};
    int vrc_v_eeIndexes[7] = {2,3,4,6,9,10,13};
    int vrc_v_ihIndexes[7] = {0,1,2,3,4,5,7};
    int vrc_v_ohIndexes[6] = {0,1,2,3,4,5};
    int vrc_v_ssIndexes[6] = {3,4,6,9,10,13};
    int vrc_v_rrIndexes[6] = {0,1,2,3,4,5};

    Vector3D HideSecondEyeVectors[3] = {Vector3D(-14.4109f,4.5291f,0.0000f),Vector3D(-2.0587f,8.6465f,0.0000f),Vector3D(4.5291f,11.7346f,0.0000f)};
    Vector3D HideBlushVectors[6] = {Vector3D(-17.9593f,17.4169f,0.0000f),Vector3D(-4.3805f,22.4955f,0.0000f),Vector3D(-3.0445f,23.6403f,0.0000f),Vector3D(-10.7900f,11.2929f,0.0000f),Vector3D(3.0998f,19.0537f,0.0000f),Vector3D(-7.7612f,11.5198f,0.0000f)};
    Vector3D TopFinInnerCloseGapVectors[1] = {Vector3D(0.0000f,0.0000f,0.0000f)};
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
    Vector3D SkinnyEyeVectors[10] = {Vector3D(5.6861f,29.3845f,0.0000f),Vector3D(9.8077f,1.8751f,0.0000f),Vector3D(-5.3608f,39.6135f,0.0000f),Vector3D(31.4924f,34.3170f,0.0000f),Vector3D(-4.1514f,49.7102f,0.0000f),Vector3D(58.1696f,-13.0243f,0.0000f),Vector3D(8.8329f,18.3519f,0.0000f),Vector3D(-25.0369f,-70.0344f,0.0000f),Vector3D(-38.8831f,-43.5666f,0.0000f),Vector3D(-61.7678f,-29.2637f,0.0000f)};
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
    Vector3D AngryEyeMouthVectors[21] = {Vector3D(-6.3896f,6.3896f,0.0000f),Vector3D(-18.8138f,9.2294f,0.0000f),Vector3D(-4.9697f,-5.6796f,0.0000f),Vector3D(-20.5887f,17.0390f,0.0000f),Vector3D(-21.2987f,8.5195f,0.0000f),Vector3D(-18.1039f,17.7489f,0.0000f),Vector3D(3.5498f,-17.7489f,0.0000f),Vector3D(4.9697f,-23.7835f,0.0000f),Vector3D(7.8095f,8.8744f,0.0000f),Vector3D(-6.0346f,7.8095f,0.0000f),Vector3D(11.0043f,35.1428f,0.0000f),Vector3D(2.8398f,33.0130f,0.0000f),Vector3D(-25.2035f,-25.2034f,0.0000f),Vector3D(0.3550f,11.3593f,0.0000f),Vector3D(2.8398f,2.4848f,0.0000f),Vector3D(-1.0649f,-8.1645f,0.0000f),Vector3D(0.7100f,1.4199f,0.0000f),Vector3D(-9.5844f,7.0996f,0.0000f),Vector3D(-5.3247f,2.8398f,0.0000f),Vector3D(-8.5195f,37.9827f,0.0000f),Vector3D(-28.3983f,22.7186f,0.0000f)};
    Vector3D HideAllVectors[32] = {Vector3D(9.0585f,-9.0585f,0.0000f),Vector3D(3.3373f,-11.4423f,0.0000f),Vector3D(0.9535f,-10.0120f,0.0000f),Vector3D(4.2909f,-8.5817f,0.0000f),Vector3D(3.4797f,-15.4237f,0.0000f),Vector3D(-8.7479f,-15.4594f,0.0000f),Vector3D(-5.7212f,-7.1515f,0.0000f),Vector3D(17.9593f,-17.4169f,0.0000f),Vector3D(4.3805f,-22.4955f,0.0000f),Vector3D(3.0445f,-23.6403f,0.0000f),Vector3D(10.7900f,-11.2929f,0.0000f),Vector3D(7.7612f,-11.5198f,0.0000f),Vector3D(-3.0998f,-19.0537f,0.0000f),Vector3D(38.9078f,-1.6109f,0.0000f),Vector3D(45.5825f,23.6575f,0.0000f),Vector3D(21.2676f,12.6919f,0.0000f),Vector3D(10.0835f,23.9987f,0.0000f),Vector3D(-2.0938f,2.6799f,0.0000f),Vector3D(-7.6914f,11.5534f,0.0000f),Vector3D(-20.2108f,-4.9483f,0.0000f),Vector3D(-27.5808f,-1.7466f,0.0000f),Vector3D(-49.5119f,12.5563f,0.0000f),Vector3D(-49.7701f,-17.8209f,0.0000f),Vector3D(-3.8141f,10.4888f,0.0000f),Vector3D(-4.7676f,8.1050f,0.0000f),Vector3D(-16.2099f,2.3838f,0.0000f),Vector3D(-8.5817f,-6.1979f,0.0000f),Vector3D(-5.2444f,6.6747f,0.0000f),Vector3D(6.1979f,9.0585f,0.0000f),Vector3D(14.4109f,-4.5291f,0.0000f),Vector3D(2.0587f,-8.6465f,0.0000f),Vector3D(-4.5291f,-11.7346f,0.0000f)};
    Vector3D AlphaGenCircleVectors[32] = {Vector3D(9.0585f,-9.0585f,0.0000f),Vector3D(3.3373f,-11.4423f,0.0000f),Vector3D(0.9535f,-10.0120f,0.0000f),Vector3D(4.2909f,-8.5817f,0.0000f),Vector3D(3.4797f,-15.4237f,0.0000f),Vector3D(-8.7479f,-15.4594f,0.0000f),Vector3D(-5.7212f,-7.1515f,0.0000f),Vector3D(17.9593f,-17.4169f,0.0000f),Vector3D(4.3805f,-22.4955f,0.0000f),Vector3D(3.0445f,-23.6403f,0.0000f),Vector3D(10.7900f,-11.2929f,0.0000f),Vector3D(7.7612f,-11.5198f,0.0000f),Vector3D(-3.0998f,-19.0537f,0.0000f),Vector3D(4.8774f,20.8755f,0.0000f),Vector3D(19.7374f,29.1463f,0.0000f),Vector3D(7.9077f,12.2964f,0.0000f),Vector3D(1.3324f,14.1519f,0.0000f),Vector3D(-1.7166f,5.2700f,0.0000f),Vector3D(-7.6914f,11.5534f,0.0000f),Vector3D(-11.3919f,7.4419f,0.0000f),Vector3D(-14.0035f,1.2069f,0.0000f),Vector3D(-23.3880f,8.3109f,0.0000f),Vector3D(-39.4329f,9.0599f,0.0000f),Vector3D(-3.8141f,10.4888f,0.0000f),Vector3D(-4.7676f,8.1050f,0.0000f),Vector3D(-16.2099f,2.3838f,0.0000f),Vector3D(-8.5817f,-6.1979f,0.0000f),Vector3D(-5.2444f,6.6747f,0.0000f),Vector3D(6.1979f,9.0585f,0.0000f),Vector3D(14.4109f,-4.5291f,0.0000f),Vector3D(2.0587f,-8.6465f,0.0000f),Vector3D(-4.5291f,-11.7346f,0.0000f)};
    Vector3D vrc_v_aaVectors[5] = {Vector3D(0.0000f,27.6883f,0.0000f),Vector3D(0.0000f,27.6883f,0.0000f),Vector3D(0.0000f,27.6883f,0.0000f),Vector3D(0.0000f,27.6883f,0.0000f),Vector3D(0.0000f,6.8156f,0.0000f)};
    Vector3D vrc_v_chVectors[3] = {Vector3D(0.0000f,18.3169f,0.0000f),Vector3D(0.0000f,18.3169f,0.0000f),Vector3D(0.0000f,-28.1143f,0.0000f)};
    Vector3D vrc_v_ddVectors[6] = {Vector3D(0.0000f,-1.7039f,0.0000f),Vector3D(0.0000f,-1.7039f,0.0000f),Vector3D(0.0000f,-14.9091f,0.0000f),Vector3D(0.0000f,-14.9091f,0.0000f),Vector3D(0.0000f,-23.8545f,0.0000f),Vector3D(0.0000f,-23.8545f,0.0000f)};
    Vector3D vrc_v_eeVectors[7] = {Vector3D(0.0000f,-8.9454f,0.0000f),Vector3D(0.0000f,-8.9454f,0.0000f),Vector3D(0.0000f,-8.9454f,0.0000f),Vector3D(0.0000f,-17.4649f,0.0000f),Vector3D(0.0000f,-17.4649f,0.0000f),Vector3D(0.0000f,-17.4649f,0.0000f),Vector3D(0.0000f,-17.4649f,0.0000f)};
    Vector3D vrc_v_ihVectors[7] = {Vector3D(0.0000f,6.8156f,0.0000f),Vector3D(0.0000f,6.8156f,0.0000f),Vector3D(0.0000f,-7.6675f,0.0000f),Vector3D(0.0000f,-7.6675f,0.0000f),Vector3D(0.0000f,-7.6675f,0.0000f),Vector3D(0.0000f,6.8156f,0.0000f),Vector3D(0.0000f,6.8156f,0.0000f)};
    Vector3D vrc_v_ohVectors[6] = {Vector3D(0.0000f,11.5013f,0.0000f),Vector3D(0.0000f,14.4831f,0.0000f),Vector3D(0.0000f,-4.2597f,0.0000f),Vector3D(0.0000f,-34.0779f,0.0000f),Vector3D(0.0000f,1.7039f,0.0000f),Vector3D(0.0000f,3.8338f,0.0000f)};
    Vector3D vrc_v_ssVectors[6] = {Vector3D(0.0000f,-13.2052f,0.0000f),Vector3D(0.0000f,-13.2052f,0.0000f),Vector3D(0.0000f,-22.1506f,0.0000f),Vector3D(0.0000f,-32.8000f,0.0000f),Vector3D(0.0000f,-32.8000f,0.0000f),Vector3D(0.0000f,-13.2052f,0.0000f)};
    Vector3D vrc_v_rrVectors[6] = {Vector3D(0.0000f,19.5948f,0.0000f),Vector3D(0.0000f,19.1688f,0.0000f),Vector3D(0.0000f,2.5558f,0.0000f),Vector3D(0.0000f,-11.0753f,0.0000f),Vector3D(0.0000f,-11.0753f,0.0000f),Vector3D(0.0000f,19.1688f,0.0000f)};

    Morph morphs[35] = {
        Morph(3, HideSecondEyeIndexes, HideSecondEyeVectors),
        Morph(6, HideBlushIndexes, HideBlushVectors),
        Morph(1, TopFinInnerCloseGapIndexes, TopFinInnerCloseGapVectors),
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
        Morph(10, SkinnyEyeIndexes, SkinnyEyeVectors),
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
        Morph(21, AngryEyeMouthIndexes, AngryEyeMouthVectors),
        Morph(32, HideAllIndexes, HideAllVectors),
        Morph(32, AlphaGenCircleIndexes, AlphaGenCircleVectors),
        Morph(5, vrc_v_aaIndexes, vrc_v_aaVectors),
        Morph(3, vrc_v_chIndexes, vrc_v_chVectors),
        Morph(6, vrc_v_ddIndexes, vrc_v_ddVectors),
        Morph(7, vrc_v_eeIndexes, vrc_v_eeVectors),
        Morph(7, vrc_v_ihIndexes, vrc_v_ihVectors),
        Morph(6, vrc_v_ohIndexes, vrc_v_ohVectors),
        Morph(6, vrc_v_ssIndexes, vrc_v_ssVectors),
        Morph(6, vrc_v_rrIndexes, vrc_v_rrVectors)
    };

public:
    BetaFront(){}

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
