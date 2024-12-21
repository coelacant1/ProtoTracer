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
        EvilMouth,
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
        vrc_v_rr,
        CrashEmoticon,
        FrustratedEye,
        FrustratedMouth,
        DizzyEye,
        DizzyMouth,
        ShockedEye,
        ShockedMouth2,
        GentleEye,
        GentleMouth
    };

private:
    Vector3D* basisVertices = new Vector3D[54] {Vector3D(-18028.2993f,-6500.0000f,-2215.6806f),Vector3D(-15215.3969f,-6500.0000f,-4313.4384f),Vector3D(-17122.4499f,-6500.0000f,-1309.8304f),Vector3D(-14881.6624f,-6500.0000f,-3169.2069f),Vector3D(-10543.1175f,-6500.0000f,-1595.8884f),Vector3D(-10638.4706f,-6500.0000f,-2597.0910f),Vector3D(-5918.5143f,-6500.0000f,-4075.0570f),Vector3D(-6347.6014f,-6500.0000f,-4933.2309f),Vector3D(-4535.9011f,-6500.0000f,-7174.0179f),Vector3D(-4187.9306f,-6500.0000f,-5631.6490f),Vector3D(-3217.5775f,-6500.0000f,-5675.7560f),Vector3D(-2342.7904f,-6500.0000f,-7221.6940f),Vector3D(-1627.6456f,-6500.0000f,-4837.8782f),Vector3D(-2199.7614f,-6500.0000f,-4122.7331f),Vector3D(-10098.2628f,-6500.0000f,-8057.5314f),Vector3D(-8302.3310f,-6500.0000f,-6315.8441f),Vector3D(-8025.2361f,-6500.0000f,-8851.4566f),Vector3D(-7587.1859f,-6500.0000f,-6601.9020f),Vector3D(-7015.0700f,-6500.0000f,-6840.2834f),Vector3D(-4917.3117f,-6500.0000f,-8604.3072f),Vector3D(-7319.5248f,-6500.0000f,-9204.3123f),Vector3D(-5996.3160f,-6500.0000f,-9733.5958f),Vector3D(-3439.3458f,-6500.0000f,-8842.6895f),Vector3D(-4249.8431f,-6500.0000f,-8890.3656f),Vector3D(-5025.9628f,-6500.0000f,-10042.3450f),Vector3D(-3129.3635f,-6500.0000f,-10748.0564f),Vector3D(-11878.0546f,-6500.0000f,-12227.7079f),Vector3D(-12545.5227f,-6500.0000f,-9700.8629f),Vector3D(-10114.0308f,-6500.0000f,-10797.4186f),Vector3D(-11258.2626f,-6500.0000f,-14134.7609f),Vector3D(-7777.8912f,-6500.0000f,-11798.6212f),Vector3D(-9480.7653f,-6500.0000f,-15379.2868f),Vector3D(-5966.1908f,-6500.0000f,-12561.4424f),Vector3D(-7491.8332f,-6500.0000f,-16709.2819f),Vector3D(-5298.7223f,-6500.0000f,-15278.9927f),Vector3D(-3010.2589f,-6500.0000f,-13848.7024f),Vector3D(-12926.9333f,-6500.0000f,-11369.5345f),Vector3D(-13308.3439f,-6500.0000f,-12418.4132f),Vector3D(-11973.4068f,-6500.0000f,-14611.5236f),Vector3D(-12450.1705f,-6500.0000f,-15422.0209f),Vector3D(-9780.2963f,-6500.0000f,-17376.7509f),Vector3D(-8159.3018f,-6500.0000f,-17138.3686f),Vector3D(-19792.3241f,-6500.0000f,-5839.0808f),Vector3D(-19077.1790f,-6500.0000f,-8604.3072f),Vector3D(-18934.1507f,-6500.0000f,-6458.8733f),Vector3D(-18552.7401f,-6500.0000f,-7936.8391f),Vector3D(-17313.1542f,-6500.0000f,-8222.8966f),Vector3D(-16693.3632f,-6500.0000f,-9128.7470f),Vector3D(-12380.9032f,-6500.0000f,-9353.4832f),Vector3D(-10939.8165f,-6500.0000f,-8900.5709f),Vector3D(-6987.1206f,-6500.0000f,-10403.4185f),Vector3D(-7192.9903f,-6500.0000f,-11268.0702f),Vector3D(-2890.3165f,-6500.0000f,-13182.6572f),Vector3D(-3343.2295f,-6500.0000f,-12009.2010f)};
    IndexGroup* basisIndexes = new IndexGroup[38] {IndexGroup(2,1,0),IndexGroup(3,1,2),IndexGroup(3,4,1),IndexGroup(4,5,1),IndexGroup(4,6,5),IndexGroup(6,7,5),IndexGroup(9,8,7),IndexGroup(9,7,6),IndexGroup(9,10,8),IndexGroup(10,11,8),IndexGroup(10,12,11),IndexGroup(10,13,12),IndexGroup(14,15,16),IndexGroup(15,17,16),IndexGroup(18,19,20),IndexGroup(19,21,20),IndexGroup(24,23,22),IndexGroup(22,25,24),IndexGroup(26,27,28),IndexGroup(28,29,26),IndexGroup(28,30,29),IndexGroup(30,31,29),IndexGroup(30,32,31),IndexGroup(32,33,31),IndexGroup(32,34,33),IndexGroup(32,35,34),IndexGroup(38,37,36),IndexGroup(38,39,37),IndexGroup(38,40,39),IndexGroup(38,41,40),IndexGroup(44,43,42),IndexGroup(44,45,43),IndexGroup(45,46,43),IndexGroup(46,47,43),IndexGroup(48,49,50),IndexGroup(50,51,48),IndexGroup(50,52,51),IndexGroup(50,53,52)};
    StaticTriangleGroup<54,38> triangleGroup = StaticTriangleGroup<54,38>(&basisVertices[0], &basisIndexes[0]);
    TriangleGroup<54,38> triangleGroupMemory = TriangleGroup<54,38>(&triangleGroup);
    SimpleMaterial simpleMaterial = SimpleMaterial(RGBColor(128, 128, 128));
    Object3D basisObj = Object3D(&triangleGroup, &triangleGroupMemory, &simpleMaterial);

    static const uint8_t morphCount = 45;
    int* HideSecondEyeIndexes = new int[3] {49,50,53};
    int* HideBlushIndexes = new int[6] {15,17,18,19,22,23};
    int* TopFinInnerCloseGapIndexes = new int[1] {0};
    int* ShockedMouthIndexes = new int[12] {1,3,4,5,6,7,8,9,10,11,12,13};
    int* HappyMouthIndexes = new int[14] {0,1,2,3,4,5,6,7,8,9,10,11,12,13};
    int* OwOMouthIndexes = new int[14] {0,1,2,3,4,5,6,7,8,9,10,11,12,13};
    int* UpsetMouthIndexes = new int[10] {4,5,6,7,8,9,10,11,12,13};
    int* SillyMouthIndexes = new int[14] {0,1,2,3,4,5,6,7,8,9,10,11,12,13};
    int* FlatMouthIndexes = new int[12] {1,3,4,5,6,7,8,9,10,11,12,13};
    int* OpenToothMouthIndexes = new int[14] {0,1,2,3,4,5,6,7,8,9,10,11,12,13};
    int* SadMouthIndexes = new int[12] {1,3,4,5,6,7,8,9,10,11,12,13};
    int* PogMouthIndexes = new int[13] {0,1,3,4,5,6,7,8,9,10,11,12,13};
    int* DerpyMouthIndexes = new int[12] {1,3,4,5,6,7,8,9,10,11,12,13};
    int* EvilMouthIndexes = new int[14] {0,1,2,3,4,5,6,7,8,9,10,11,12,13};
    int* SkinnyEyeIndexes = new int[10] {26,27,28,29,30,31,32,33,34,35};
    int* SadEyeIndexes = new int[5] {26,29,31,33,34};
    int* CircleEyeIndexes = new int[9] {26,27,28,30,31,32,33,34,35};
    int* HeartEyeIndexes = new int[10] {26,27,28,29,30,31,32,33,34,35};
    int* ClosedEyeIndexes = new int[8] {26,28,29,30,31,33,34,35};
    int* BlushEyeIndexes = new int[9] {26,27,28,29,30,31,32,33,34};
    int* ClosedEyeBrowIndexes = new int[6] {36,37,38,39,40,41};
    int* AngryEyeIndexes = new int[5] {26,29,31,33,34};
    int* DeadEyeIndexes = new int[16] {26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41};
    int* HideEyeBrowIndexes = new int[3] {36,38,41};
    int* SadEyeBrowIndexes = new int[6] {36,37,38,39,40,41};
    int* AngryEyeMouthIndexes = new int[21] {0,1,3,5,6,7,8,9,10,11,12,13,26,27,28,29,31,32,33,34,35};
    int* HideAllIndexes = new int[32] {0,1,5,7,8,11,12,14,16,20,21,24,25,26,27,28,29,30,31,32,33,34,35,36,38,41,44,45,46,48,51,52};
    int* AlphaGenCircleIndexes = new int[32] {0,1,5,7,8,11,12,14,16,20,21,24,25,26,27,28,29,30,31,32,33,34,35,36,38,41,44,45,46,48,51,52};
    int* vrc_v_aaIndexes = new int[5] {0,1,5,7,8};
    int* vrc_v_chIndexes = new int[3] {0,1,3};
    int* vrc_v_ddIndexes = new int[6] {2,3,4,6,9,10};
    int* vrc_v_eeIndexes = new int[7] {2,3,4,6,9,10,13};
    int* vrc_v_ihIndexes = new int[7] {0,1,2,3,4,5,7};
    int* vrc_v_ohIndexes = new int[6] {0,1,2,3,4,5};
    int* vrc_v_ssIndexes = new int[6] {3,4,6,9,10,13};
    int* vrc_v_rrIndexes = new int[6] {0,1,2,3,4,5};
    int* CrashEmoticonIndexes = new int[49] {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,17,18,19,20,21,22,23,24,25,26,27,28,29,31,32,33,34,35,36,37,39,40,41,42,44,45,46,47,48,49,50,52,53};
    int* FrustratedEyeIndexes = new int[10] {29,31,33,34,36,37,38,39,40,41};
    int* FrustratedMouthIndexes = new int[10] {1,3,4,5,6,7,8,9,10,11};
    int* DizzyEyeIndexes = new int[22] {26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,48,49,50,51,52,53};
    int* DizzyMouthIndexes = new int[11] {1,2,3,4,5,6,7,8,9,10,11};
    int* ShockedEyeIndexes = new int[34] {14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,48,49,50,51,52,53};
    int* ShockedMouth2Indexes = new int[14] {0,1,2,3,4,5,6,7,8,9,10,11,12,13};
    int* GentleEyeIndexes = new int[16] {26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41};
    int* GentleMouthIndexes = new int[13] {0,1,2,3,4,5,6,8,9,10,11,12,13};

    Vector3D* HideSecondEyeVectors = new Vector3D[3] {Vector3D(-1441.0868f,0.0000f,-452.9133f),Vector3D(-205.8697f,0.0000f,-864.6517f),Vector3D(452.9130f,0.0000f,-1173.4562f)};
    Vector3D* HideBlushVectors = new Vector3D[6] {Vector3D(-1795.9328f,0.0000f,-1741.6873f),Vector3D(-438.0503f,0.0000f,-2249.5546f),Vector3D(-304.4548f,0.0000f,-2364.0289f),Vector3D(-1079.0043f,0.0000f,-1129.2887f),Vector3D(309.9823f,0.0000f,-1905.3669f),Vector3D(-776.1197f,0.0000f,-1151.9794f)};
    Vector3D* TopFinInnerCloseGapVectors = new Vector3D[1] {Vector3D(0.0000f,0.0000f,0.0000f)};
    Vector3D* ShockedMouthVectors = new Vector3D[12] {Vector3D(-1674.7437f,0.0000f,-101.4996f),Vector3D(-1573.2441f,0.0000f,-405.9982f),Vector3D(-2588.2387f,0.0000f,811.9966f),Vector3D(-2588.2387f,0.0000f,811.9966f),Vector3D(-5734.7260f,0.0000f,152.2493f),Vector3D(-5734.7255f,0.0000f,152.2493f),Vector3D(-4059.9833f,0.0000f,3958.4832f),Vector3D(-4059.9828f,0.0000f,3958.4832f),Vector3D(-3450.9854f,0.0000f,1522.4938f),Vector3D(-4110.7323f,0.0000f,1623.9929f),Vector3D(-2994.2373f,0.0000f,1319.4942f),Vector3D(-2638.9885f,0.0000f,1420.9940f)};
    Vector3D* HappyMouthVectors = new Vector3D[14] {Vector3D(-1522.4934f,0.0000f,-1573.2434f),Vector3D(-761.2467f,0.0000f,-253.7489f),Vector3D(-1522.4934f,0.0000f,-1573.2434f),Vector3D(-761.2467f,0.0000f,-253.7489f),Vector3D(-710.4969f,0.0000f,0.0000f),Vector3D(-710.4969f,0.0000f,0.0000f),Vector3D(-2334.4898f,0.0000f,-507.4978f),Vector3D(-2334.4903f,0.0000f,-507.4978f),Vector3D(-1420.9938f,0.0000f,2486.7392f),Vector3D(-1420.9943f,0.0000f,2182.2407f),Vector3D(-1471.7441f,0.0000f,710.4969f),Vector3D(-2435.9896f,0.0000f,862.7462f),Vector3D(-2029.9915f,0.0000f,-2994.2374f),Vector3D(-1420.9940f,0.0000f,-3095.7370f)};
    Vector3D* OwOMouthVectors = new Vector3D[14] {Vector3D(-1471.7445f,0.0000f,-1420.9940f),Vector3D(608.9973f,0.0000f,2232.9905f),Vector3D(-1471.7445f,0.0000f,-1420.9940f),Vector3D(608.9973f,0.0000f,2232.9905f),Vector3D(-1167.2449f,0.0000f,-3146.4870f),Vector3D(-1167.2449f,0.0000f,-3146.4870f),Vector3D(-1319.4942f,0.0000f,2029.9914f),Vector3D(-1319.4942f,0.0000f,2029.9914f),Vector3D(-761.2467f,0.0000f,-253.7489f),Vector3D(-761.2467f,0.0000f,-405.9982f),Vector3D(-1268.7445f,0.0000f,-710.4969f),Vector3D(-2131.4909f,0.0000f,50.7498f),Vector3D(-2561.0193f,0.0000f,-2088.0632f),Vector3D(-1954.6490f,0.0000f,-2439.1193f)};
    Vector3D* UpsetMouthVectors = new Vector3D[10] {Vector3D(-1182.5695f,0.0000f,-695.6289f),Vector3D(-1252.1315f,0.0000f,-904.3176f),Vector3D(-4104.2099f,0.0000f,1947.7608f),Vector3D(-3686.8329f,0.0000f,1669.5092f),Vector3D(-3895.5221f,0.0000f,4034.6475f),Vector3D(-4173.7733f,0.0000f,3686.8329f),Vector3D(-3269.4554f,0.0000f,4104.2104f),Vector3D(-3965.0843f,0.0000f,4591.1503f),Vector3D(-2434.7008f,0.0000f,2991.2040f),Vector3D(-2434.7010f,0.0000f,2991.2040f)};
    Vector3D* SillyMouthVectors = new Vector3D[14] {Vector3D(-69.5629f,0.0000f,-278.2516f),Vector3D(-1043.4437f,0.0000f,-208.6887f),Vector3D(-69.5629f,0.0000f,-278.2515f),Vector3D(-1043.4437f,0.0000f,-208.6887f),Vector3D(-4938.9648f,0.0000f,-1878.1979f),Vector3D(-4938.9648f,0.0000f,-1878.1979f),Vector3D(-7721.4804f,0.0000f,2504.2639f),Vector3D(-7443.2292f,0.0000f,2434.7010f),Vector3D(-8573.5264f,0.0000f,4781.7564f),Vector3D(-8834.0917f,0.0000f,4086.9184f),Vector3D(-7686.6488f,0.0000f,1693.6684f),Vector3D(-8946.0433f,0.0000f,2214.7970f),Vector3D(-8511.7692f,0.0000f,-477.7012f),Vector3D(-7990.6397f,0.0000f,-477.7012f)};
    Vector3D* FlatMouthVectors = new Vector3D[12] {Vector3D(208.6887f,0.0000f,1947.7608f),Vector3D(97.0697f,0.0000f,1798.9355f),Vector3D(-139.1258f,0.0000f,278.2515f),Vector3D(-139.1258f,0.0000f,278.2514f),Vector3D(-1182.5690f,0.0000f,2643.3897f),Vector3D(-1443.0132f,0.0000f,2568.9771f),Vector3D(-779.7408f,0.0000f,4764.2241f),Vector3D(-891.3598f,0.0000f,4094.5106f),Vector3D(-129.4262f,0.0000f,4029.7976f),Vector3D(-464.2830f,0.0000f,4699.5111f),Vector3D(347.8144f,0.0000f,2295.5751f),Vector3D(347.8144f,0.0000f,2295.5751f)};
    Vector3D* OpenToothMouthVectors = new Vector3D[14] {Vector3D(-1065.7463f,0.0000f,-1167.2449f),Vector3D(-1826.9920f,0.0000f,710.4969f),Vector3D(1052.6848f,0.0000f,967.2027f),Vector3D(506.3181f,0.0000f,2392.2548f),Vector3D(-1820.5662f,0.0000f,329.2489f),Vector3D(-4516.7303f,0.0000f,-355.2485f),Vector3D(-4937.4352f,0.0000f,2538.2476f),Vector3D(-7206.4700f,0.0000f,761.2467f),Vector3D(-6851.2211f,0.0000f,2334.4898f),Vector3D(-5228.5295f,0.0000f,3688.4813f),Vector3D(-4806.5104f,0.0000f,2912.8990f),Vector3D(-6749.7218f,0.0000f,2385.2396f),Vector3D(-5836.2254f,0.0000f,50.7498f),Vector3D(-5264.9174f,0.0000f,-2.9569f)};
    Vector3D* SadMouthVectors = new Vector3D[12] {Vector3D(50.7498f,0.0000f,1116.4951f),Vector3D(50.7498f,0.0000f,1116.4954f),Vector3D(-1522.4934f,0.0000f,-862.7465f),Vector3D(-1522.4934f,0.0000f,-862.7465f),Vector3D(-4247.9992f,0.0000f,1574.7361f),Vector3D(-4116.2620f,0.0000f,1520.6814f),Vector3D(-4038.5904f,0.0000f,4089.4928f),Vector3D(-4394.1140f,0.0000f,3308.2607f),Vector3D(-4140.5168f,0.0000f,4029.7880f),Vector3D(-4786.8779f,0.0000f,4816.4806f),Vector3D(-5099.1567f,0.0000f,3054.0302f),Vector3D(-4509.9669f,0.0000f,2775.3613f)};
    Vector3D* PogMouthVectors = new Vector3D[13] {Vector3D(-296.8979f,0.0000f,-237.5178f),Vector3D(-356.2765f,0.0000f,-356.2765f),Vector3D(-1793.6363f,0.0000f,2190.4383f),Vector3D(-5412.9524f,0.0000f,992.4825f),Vector3D(-2018.9009f,0.0000f,-1246.9680f),Vector3D(-9331.9950f,0.0000f,3690.0058f),Vector3D(-4809.7339f,0.0000f,-1009.4504f),Vector3D(-6839.5071f,0.0000f,1887.3949f),Vector3D(-10148.2244f,0.0000f,5269.6872f),Vector3D(-10509.1796f,0.0000f,5089.6478f),Vector3D(-9565.8724f,0.0000f,3619.1654f),Vector3D(-10712.2554f,0.0000f,2331.0151f),Vector3D(-10587.8401f,0.0000f,2511.2712f)};
    Vector3D* DerpyMouthVectors = new Vector3D[12] {Vector3D(-372.0627f,0.0000f,2716.0597f),Vector3D(-520.8883f,0.0000f,2455.6155f),Vector3D(-3683.4230f,0.0000f,892.9511f),Vector3D(-3683.4230f,0.0000f,892.9511f),Vector3D(-7329.6404f,0.0000f,2716.0597f),Vector3D(-7329.6409f,0.0000f,2716.0597f),Vector3D(-8557.4484f,0.0000f,3646.2171f),Vector3D(-8557.4479f,0.0000f,3646.2171f),Vector3D(-9078.3362f,0.0000f,1674.2835f),Vector3D(-10678.2076f,0.0000f,2641.6473f),Vector3D(-11347.9203f,0.0000f,-706.9197f),Vector3D(-10417.7628f,0.0000f,-1116.1890f)};
    Vector3D* EvilMouthVectors = new Vector3D[14] {Vector3D(-1471.7445f,0.0000f,-1420.9940f),Vector3D(-1065.7463f,0.0000f,2131.4909f),Vector3D(-1471.7445f,0.0000f,-1420.9940f),Vector3D(-964.2467f,0.0000f,1826.9923f),Vector3D(-3755.4836f,0.0000f,-2334.4905f),Vector3D(-3755.4836f,0.0000f,-2334.4905f),Vector3D(-7054.2202f,0.0000f,2182.2407f),Vector3D(-7054.2197f,0.0000f,2182.2407f),Vector3D(-4821.2299f,0.0000f,3704.7343f),Vector3D(-4821.2295f,0.0000f,3552.4850f),Vector3D(-4719.7299f,0.0000f,811.9969f),Vector3D(-6242.2230f,0.0000f,1674.7427f),Vector3D(-5555.2567f,0.0000f,-768.5690f),Vector3D(-4593.6375f,0.0000f,-1018.1255f)};
    Vector3D* SkinnyEyeVectors = new Vector3D[10] {Vector3D(568.6121f,0.0000f,-2938.4508f),Vector3D(980.7701f,0.0000f,-187.5095f),Vector3D(-536.0785f,0.0000f,-3961.3495f),Vector3D(3149.2424f,0.0000f,-3431.7026f),Vector3D(-415.1354f,0.0000f,-4971.0207f),Vector3D(5816.9589f,0.0000f,1302.4340f),Vector3D(883.2898f,0.0000f,-1835.1946f),Vector3D(-2503.6922f,0.0000f,7003.4351f),Vector3D(-3888.3142f,0.0000f,4356.6608f),Vector3D(-6176.7786f,0.0000f,2926.3716f)};
    Vector3D* SadEyeVectors = new Vector3D[5] {Vector3D(-510.6277f,0.0000f,127.6569f),Vector3D(-223.3992f,0.0000f,414.8846f),Vector3D(-287.2276f,0.0000f,1787.1962f),Vector3D(-95.7427f,0.0000f,3223.3362f),Vector3D(638.2842f,0.0000f,1468.0538f)};
    Vector3D* CircleEyeVectors = new Vector3D[9] {Vector3D(319.1423f,0.0000f,-829.7701f),Vector3D(1085.0830f,0.0000f,-1787.1962f),Vector3D(-702.1132f,0.0000f,319.1423f),Vector3D(-1204.5231f,0.0000f,1656.9071f),Vector3D(-139.9326f,0.0000f,-602.7298f),Vector3D(223.3996f,0.0000f,1180.8262f),Vector3D(95.7427f,0.0000f,287.2276f),Vector3D(-127.6569f,0.0000f,159.5707f),Vector3D(-1851.0249f,0.0000f,1021.2545f)};
    Vector3D* HeartEyeVectors = new Vector3D[10] {Vector3D(-529.9530f,0.0000f,-2563.1361f),Vector3D(680.1176f,0.0000f,-3384.2525f),Vector3D(-446.5046f,0.0000f,-957.8047f),Vector3D(-11.5585f,0.0000f,-2035.7122f),Vector3D(-697.2618f,0.0000f,894.3033f),Vector3D(276.0324f,0.0000f,-154.7060f),Vector3D(-819.2201f,0.0000f,334.1331f),Vector3D(248.1422f,0.0000f,-40.7982f),Vector3D(-389.8115f,0.0000f,-655.5653f),Vector3D(-2700.8369f,0.0000f,-257.3996f)};
    Vector3D* ClosedEyeVectors = new Vector3D[8] {Vector3D(-31.9138f,0.0000f,1595.7108f),Vector3D(63.8285f,0.0000f,191.4854f),Vector3D(989.3408f,0.0000f,3031.8508f),Vector3D(-183.2685f,0.0000f,348.4240f),Vector3D(1308.4831f,0.0000f,3414.8216f),Vector3D(1308.4831f,0.0000f,3414.8216f),Vector3D(382.9708f,0.0000f,702.1132f),Vector3D(-1085.0837f,0.0000f,-606.3700f)};
    Vector3D* BlushEyeVectors = new Vector3D[9] {Vector3D(3319.0794f,0.0000f,-4531.8193f),Vector3D(2158.8831f,0.0000f,-3408.8736f),Vector3D(-1851.0246f,0.0000f,861.6838f),Vector3D(2936.1086f,0.0000f,-1723.3677f),Vector3D(-3287.1647f,0.0000f,1372.3116f),Vector3D(-861.6838f,0.0000f,3957.3631f),Vector3D(-2042.5105f,0.0000f,829.7701f),Vector3D(-765.9411f,0.0000f,4467.9909f),Vector3D(1180.8262f,0.0000f,1085.0840f)};
    Vector3D* ClosedEyeBrowVectors = new Vector3D[6] {Vector3D(255.3139f,0.0000f,-638.2847f),Vector3D(1436.1401f,0.0000f,-1085.0830f),Vector3D(2265.9101f,0.0000f,31.9138f),Vector3D(2457.3956f,0.0000f,223.3992f),Vector3D(1946.7673f,0.0000f,1468.0538f),Vector3D(1946.7673f,0.0000f,1468.0538f)};
    Vector3D* AngryEyeVectors = new Vector3D[5] {Vector3D(606.3700f,0.0000f,1148.9115f),Vector3D(1180.8262f,0.0000f,1659.5392f),Vector3D(734.0269f,0.0000f,1148.9115f),Vector3D(-95.7427f,0.0000f,797.8554f),Vector3D(-95.7427f,0.0000f,382.9708f)};
    Vector3D* DeadEyeVectors = new Vector3D[16] {Vector3D(-666.7500f,0.0000f,1375.7219f),Vector3D(631.3992f,0.0000f,-387.0735f),Vector3D(-211.9598f,0.0000f,-641.8324f),Vector3D(1495.8401f,0.0000f,883.9016f),Vector3D(-712.2660f,0.0000f,-1207.6778f),Vector3D(1151.1412f,0.0000f,874.3753f),Vector3D(-1004.8871f,0.0000f,-1624.9418f),Vector3D(946.0526f,0.0000f,693.8095f),Vector3D(-196.7096f,0.0000f,-39.3419f),Vector3D(-2485.1730f,0.0000f,-1469.6312f),Vector3D(7009.2554f,0.0000f,-92.9832f),Vector3D(6629.2667f,0.0000f,1631.3972f),Vector3D(2662.4603f,0.0000f,578.7458f),Vector3D(2206.0289f,0.0000f,1861.9699f),Vector3D(-2879.8599f,0.0000f,2011.4164f),Vector3D(-3844.3842f,0.0000f,1153.6551f)};
    Vector3D* HideEyeBrowVectors = new Vector3D[3] {Vector3D(-381.4106f,0.0000f,-1048.8787f),Vector3D(-476.7628f,0.0000f,-810.4973f),Vector3D(-1620.9946f,0.0000f,-238.3823f)};
    Vector3D* SadEyeBrowVectors = new Vector3D[6] {Vector3D(1531.8823f,0.0000f,-3063.7655f),Vector3D(2648.8800f,0.0000f,-2712.7085f),Vector3D(3702.0493f,0.0000f,382.9708f),Vector3D(3702.0493f,0.0000f,382.9708f),Vector3D(5265.8463f,0.0000f,2265.9092f),Vector3D(4755.2190f,0.0000f,2489.3093f)};
    Vector3D* AngryEyeMouthVectors = new Vector3D[21] {Vector3D(-638.9599f,0.0000f,-638.9608f),Vector3D(-1881.3839f,0.0000f,-922.9436f),Vector3D(-496.9702f,0.0000f,567.9648f),Vector3D(-2058.8732f,0.0000f,-1703.8953f),Vector3D(-2129.8695f,0.0000f,-851.9478f),Vector3D(-1810.3890f,0.0000f,-1774.8904f),Vector3D(354.9781f,0.0000f,1774.8909f),Vector3D(496.9692f,0.0000f,2378.3536f),Vector3D(780.9522f,0.0000f,-887.4450f),Vector3D(-603.4629f,0.0000f,-780.9525f),Vector3D(1100.4332f,0.0000f,-3514.2822f),Vector3D(283.9832f,0.0000f,-3301.2962f),Vector3D(-2520.3457f,0.0000f,2520.3438f),Vector3D(35.4986f,0.0000f,-1135.9301f),Vector3D(283.9823f,0.0000f,-248.4846f),Vector3D(-106.4930f,0.0000f,816.4492f),Vector3D(70.9963f,0.0000f,-141.9907f),Vector3D(-958.4413f,0.0000f,-709.9562f),Vector3D(-532.4674f,0.0000f,-283.9832f),Vector3D(-851.9473f,0.0000f,-3798.2664f),Vector3D(-2839.8254f,0.0000f,-2271.8611f)};
    Vector3D* HideAllVectors = new Vector3D[32] {Vector3D(905.8495f,0.0000f,905.8502f),Vector3D(333.7345f,0.0000f,1144.2316f),Vector3D(95.3531f,0.0000f,1001.2026f),Vector3D(429.0872f,0.0000f,858.1738f),Vector3D(347.9705f,0.0000f,1542.3689f),Vector3D(-874.7871f,0.0000f,1545.9380f),Vector3D(-572.1158f,0.0000f,715.1451f),Vector3D(1795.9318f,0.0000f,1741.6873f),Vector3D(438.0503f,0.0000f,2249.5546f),Vector3D(304.4548f,0.0000f,2364.0289f),Vector3D(1079.0043f,0.0000f,1129.2887f),Vector3D(776.1197f,0.0000f,1151.9794f),Vector3D(-309.9823f,0.0000f,1905.3669f),Vector3D(3890.7819f,0.0000f,161.0947f),Vector3D(4558.2500f,0.0000f,-2365.7503f),Vector3D(2126.7581f,0.0000f,-1269.1946f),Vector3D(1008.3523f,0.0000f,-2399.8652f),Vector3D(-209.3816f,0.0000f,-267.9920f),Vector3D(-769.1441f,0.0000f,-1155.3392f),Vector3D(-2021.0819f,0.0000f,494.8292f),Vector3D(-2758.0771f,0.0000f,174.6559f),Vector3D(-4951.1881f,0.0000f,-1255.6334f),Vector3D(-4977.0143f,0.0000f,1782.0892f),Vector3D(-381.4106f,0.0000f,-1048.8787f),Vector3D(-476.7637f,0.0000f,-810.4973f),Vector3D(-1620.9946f,0.0000f,-238.3823f),Vector3D(-858.1734f,0.0000f,619.7925f),Vector3D(-524.4389f,0.0000f,-667.4681f),Vector3D(619.7910f,0.0000f,-905.8504f),Vector3D(1441.0868f,0.0000f,452.9123f),Vector3D(205.8697f,0.0000f,864.6517f),Vector3D(-452.9130f,0.0000f,1173.4562f)};
    Vector3D* AlphaGenCircleVectors = new Vector3D[32] {Vector3D(905.8495f,0.0000f,905.8502f),Vector3D(333.7345f,0.0000f,1144.2316f),Vector3D(95.3531f,0.0000f,1001.2026f),Vector3D(429.0872f,0.0000f,858.1738f),Vector3D(347.9705f,0.0000f,1542.3689f),Vector3D(-874.7871f,0.0000f,1545.9380f),Vector3D(-572.1158f,0.0000f,715.1451f),Vector3D(1795.9318f,0.0000f,1741.6873f),Vector3D(438.0503f,0.0000f,2249.5546f),Vector3D(304.4548f,0.0000f,2364.0289f),Vector3D(1079.0043f,0.0000f,1129.2887f),Vector3D(776.1197f,0.0000f,1151.9794f),Vector3D(-309.9823f,0.0000f,1905.3669f),Vector3D(487.7357f,0.0000f,-2087.5549f),Vector3D(1973.7406f,0.0000f,-2914.6252f),Vector3D(790.7658f,0.0000f,-1229.6438f),Vector3D(133.2378f,0.0000f,-1415.1888f),Vector3D(-171.6619f,0.0000f,-526.9995f),Vector3D(-769.1441f,0.0000f,-1155.3392f),Vector3D(-1139.1873f,0.0000f,-744.1931f),Vector3D(-1400.3530f,0.0000f,-120.6875f),Vector3D(-2338.8042f,0.0000f,-831.0919f),Vector3D(-3943.2867f,0.0000f,-905.9925f),Vector3D(-381.4106f,0.0000f,-1048.8787f),Vector3D(-476.7637f,0.0000f,-810.4973f),Vector3D(-1620.9946f,0.0000f,-238.3823f),Vector3D(-858.1734f,0.0000f,619.7925f),Vector3D(-524.4389f,0.0000f,-667.4681f),Vector3D(619.7910f,0.0000f,-905.8504f),Vector3D(1441.0868f,0.0000f,452.9123f),Vector3D(205.8697f,0.0000f,864.6517f),Vector3D(-452.9130f,0.0000f,1173.4562f)};
    Vector3D* vrc_v_aaVectors = new Vector3D[5] {Vector3D(0.0000f,-0.0005f,-2768.8279f),Vector3D(0.0000f,-0.0005f,-2768.8274f),Vector3D(0.0000f,-0.0005f,-2768.8277f),Vector3D(0.0005f,-0.0005f,-2768.8279f),Vector3D(0.0000f,0.0000f,-681.5581f)};
    Vector3D* vrc_v_chVectors = new Vector3D[3] {Vector3D(0.0000f,-0.0005f,-1831.6855f),Vector3D(0.0000f,-0.0005f,-1831.6860f),Vector3D(0.0000f,0.0010f,2811.4252f)};
    Vector3D* vrc_v_ddVectors = new Vector3D[6] {Vector3D(0.0000f,0.0000f,170.3897f),Vector3D(0.0000f,0.0000f,170.3897f),Vector3D(0.0000f,0.0005f,1490.9074f),Vector3D(0.0000f,0.0005f,1490.9074f),Vector3D(0.0000f,0.0010f,2385.4518f),Vector3D(-0.0005f,0.0010f,2385.4513f)};
    Vector3D* vrc_v_eeVectors = new Vector3D[7] {Vector3D(0.0000f,0.0000f,894.5446f),Vector3D(0.0000f,0.0000f,894.5446f),Vector3D(0.0000f,0.0000f,894.5446f),Vector3D(-0.0005f,0.0005f,1746.4914f),Vector3D(-0.0005f,0.0005f,1746.4914f),Vector3D(-0.0002f,0.0005f,1746.4914f),Vector3D(-0.0002f,0.0005f,1746.4914f)};
    Vector3D* vrc_v_ihVectors = new Vector3D[7] {Vector3D(0.0000f,0.0000f,-681.5577f),Vector3D(0.0000f,0.0000f,-681.5577f),Vector3D(0.0000f,0.0000f,766.7519f),Vector3D(0.0000f,0.0000f,766.7520f),Vector3D(0.0000f,0.0000f,766.7519f),Vector3D(0.0000f,0.0000f,-681.5574f),Vector3D(0.0000f,0.0000f,-681.5577f)};
    Vector3D* vrc_v_ohVectors = new Vector3D[6] {Vector3D(0.0000f,-0.0005f,-1150.1284f),Vector3D(0.0000f,-0.0010f,-1448.3094f),Vector3D(0.0000f,0.0000f,425.9735f),Vector3D(-0.0010f,0.0010f,3407.7878f),Vector3D(0.0000f,0.0000f,-170.3895f),Vector3D(0.0000f,-0.0005f,-383.3754f)};
    Vector3D* vrc_v_ssVectors = new Vector3D[6] {Vector3D(0.0000f,0.0005f,1320.5178f),Vector3D(0.0000f,0.0005f,1320.5178f),Vector3D(0.0000f,0.0010f,2215.0620f),Vector3D(-0.0005f,0.0010f,3279.9957f),Vector3D(-0.0005f,0.0010f,3279.9962f),Vector3D(-0.0002f,0.0005f,1320.5178f)};
    Vector3D* vrc_v_rrVectors = new Vector3D[6] {Vector3D(0.0000f,-0.0005f,-1959.4784f),Vector3D(0.0000f,-0.0005f,-1916.8806f),Vector3D(0.0000f,0.0000f,-255.5842f),Vector3D(0.0000f,0.0005f,1107.5311f),Vector3D(0.0000f,0.0005f,1107.5311f),Vector3D(0.0000f,-0.0005f,-1916.8808f)};
    Vector3D* CrashEmoticonVectors = new Vector3D[49] {Vector3D(6025.0158f,-0.0052f,-14326.0922f),Vector3D(4912.2782f,-0.0038f,-10292.2411f),Vector3D(4375.2089f,-0.0048f,-14626.5872f),Vector3D(3546.8378f,-0.0038f,-11103.9970f),Vector3D(246.1929f,-0.0029f,-10265.7001f),Vector3D(1267.3168f,-0.0029f,-9540.6444f),Vector3D(-4357.6164f,-0.0014f,-5328.5522f),Vector3D(-3008.4453f,-0.0014f,-4742.4531f),Vector3D(-5026.6104f,0.0010f,211.2026f),Vector3D(-6264.2007f,0.0010f,-1514.3442f),Vector3D(-8127.6708f,0.0014f,617.0468f),Vector3D(-8246.9294f,0.0024f,2579.7138f),Vector3D(-10591.1587f,0.0024f,1989.7466f),Vector3D(-10622.8752f,0.0019f,586.0257f),Vector3D(2073.0276f,0.0000f,-793.9262f),Vector3D(277.0948f,0.0000f,-2535.6135f),Vector3D(-438.0503f,0.0000f,-2249.5556f),Vector3D(-153.3027f,0.0000f,919.8136f),Vector3D(-408.8063f,0.0010f,2682.7879f),Vector3D(153.3017f,0.0005f,1405.2701f),Vector3D(689.8594f,0.0005f,1890.7275f),Vector3D(-1839.6258f,-0.0005f,-3040.4930f),Vector3D(-2938.2920f,-0.0005f,-3014.9422f),Vector3D(-2197.3305f,-0.0005f,-3730.3524f),Vector3D(-2171.7801f,-0.0005f,-3040.4930f),Vector3D(4100.1635f,0.0005f,429.0867f),Vector3D(4767.6306f,0.0000f,-2097.7554f),Vector3D(2336.1397f,0.0000f,-1001.2026f),Vector3D(3480.3715f,0.0000f,2336.1387f),Vector3D(1702.8742f,0.0000f,3580.6656f),Vector3D(-1811.7013f,-0.0005f,762.8202f),Vector3D(-286.0584f,0.0000f,4910.6598f),Vector3D(-2479.1694f,0.0000f,3480.3715f),Vector3D(-4767.6332f,0.0000f,2050.0832f),Vector3D(953.5255f,-0.0005f,-3241.9891f),Vector3D(1334.9361f,0.0000f,-2193.1095f),Vector3D(476.7637f,0.0000f,810.4982f),Vector3D(-2193.1105f,-0.0005f,2765.2292f),Vector3D(-3814.1060f,0.0000f,2526.8459f),Vector3D(715.1451f,-0.0010f,-2765.2254f),Vector3D(-143.0283f,-0.0005f,-2145.4339f),Vector3D(-524.4389f,0.0000f,-667.4681f),Vector3D(-1764.0247f,0.0000f,-381.4106f),Vector3D(-2383.8158f,0.0000f,524.4417f),Vector3D(5187.9134f,0.0010f,-1914.5880f),Vector3D(3746.8262f,0.0005f,-2367.4994f),Vector3D(-205.8697f,0.0000f,-864.6517f),Vector3D(-4302.6743f,0.0005f,1914.5870f),Vector3D(-3849.7598f,0.0010f,741.1299f)};
    Vector3D* FrustratedEyeVectors = new Vector3D[10] {Vector3D(-212.9192f,0.0000f,425.8394f),Vector3D(1809.8168f,0.0000f,1447.8540f),Vector3D(2235.6563f,0.0005f,2661.4962f),Vector3D(1831.1088f,0.0000f,1149.7660f),Vector3D(2320.8246f,-0.0010f,-2874.4154f),Vector3D(3278.9631f,-0.0010f,-2405.9925f),Vector3D(4748.1084f,-0.0010f,-766.5100f),Vector3D(4811.9841f,-0.0010f,-383.2541f),Vector3D(4918.4432f,-0.0005f,298.0881f),Vector3D(4918.4432f,-0.0005f,298.0881f)};
    Vector3D* FrustratedMouthVectors = new Vector3D[10] {Vector3D(447.1312f,0.0000f,1064.5986f),Vector3D(447.1312f,0.0000f,1064.5983f),Vector3D(-1405.2696f,0.0000f,-1213.6424f),Vector3D(-1405.2696f,0.0000f,-1298.8102f),Vector3D(-3044.7512f,0.0005f,447.1307f),Vector3D(-2491.1599f,0.0005f,340.6711f),Vector3D(-1575.6059f,0.0014f,3875.1376f),Vector3D(-1788.5256f,0.0014f,3449.2981f),Vector3D(-830.3866f,0.0005f,1043.3064f),Vector3D(-1937.5689f,0.0005f,1469.1453f)};
    Vector3D* DizzyEyeVectors = new Vector3D[22] {Vector3D(6048.3093f,-0.0010f,282.3858f),Vector3D(7574.2245f,-0.0019f,-1845.6936f),Vector3D(4662.9410f,-0.0019f,-3002.1658f),Vector3D(4811.9841f,-0.0010f,-1022.0127f),Vector3D(1852.4008f,-0.0014f,-3939.0125f),Vector3D(645.2665f,0.0000f,1197.7720f),Vector3D(-3357.6226f,0.0000f,-1974.7314f),Vector3D(-1426.5618f,0.0014f,4364.8529f),Vector3D(-3853.8465f,0.0014f,3491.8823f),Vector3D(-6142.3099f,0.0014f,2061.5940f),Vector3D(1719.5597f,-0.0010f,-3939.5142f),Vector3D(1610.6892f,0.0010f,-3400.5117f),Vector3D(6914.6523f,-0.0019f,-2115.0885f),Vector3D(7775.1412f,-0.0019f,-1975.9207f),Vector3D(5975.3075f,0.0000f,4256.1655f),Vector3D(3921.9780f,0.0010f,4591.4307f),Vector3D(7409.6050f,-0.0019f,-2193.0714f),Vector3D(5110.0712f,-0.0014f,-3044.7502f),Vector3D(-3538.9032f,0.0010f,409.6727f),Vector3D(-3836.9904f,0.0010f,1900.1112f),Vector3D(-8807.3382f,0.0005f,-2636.2686f),Vector3D(-7864.1441f,-0.0014f,-3299.8466f)};
    Vector3D* DizzyMouthVectors = new Vector3D[11] {Vector3D(-63.8762f,0.0000f,-255.5037f),Vector3D(-191.6275f,0.0000f,-596.1751f),Vector3D(-63.8762f,0.0000f,-255.5037f),Vector3D(-1724.6494f,0.0000f,-170.3360f),Vector3D(-1724.6494f,0.0000f,-170.3360f),Vector3D(-4471.3135f,0.0005f,-298.0881f),Vector3D(-4109.3497f,0.0005f,-447.1316f),Vector3D(-2874.4159f,0.0014f,4024.1811f),Vector3D(-3236.3791f,0.0014f,3683.5096f),Vector3D(-1894.9852f,0.0005f,1171.0582f),Vector3D(-2810.5395f,0.0010f,1596.8971f)};
    Vector3D* ShockedEyeVectors = new Vector3D[34] {Vector3D(3872.2057f,-0.0014f,-2978.1847f),Vector3D(2315.3481f,-0.0014f,-3989.9993f),Vector3D(2750.2131f,-0.0019f,-3176.0511f),Vector3D(2927.6466f,-0.0019f,-5021.3566f),Vector3D(2093.7109f,-0.0019f,-7008.6060f),Vector3D(638.7596f,-0.0014f,-4631.0043f),Vector3D(2129.1981f,-0.0019f,-5819.8042f),Vector3D(1673.0523f,-0.0014f,-4558.6910f),Vector3D(-1220.1929f,-0.0005f,-2780.5691f),Vector3D(-1025.1803f,-0.0010f,-3137.1431f),Vector3D(104.6038f,-0.0010f,-3806.5434f),Vector3D(-1149.1876f,-0.0005f,-2487.2570f),Vector3D(904.9101f,0.0000f,283.8936f),Vector3D(2111.4531f,-0.0010f,-2608.2678f),Vector3D(-283.8936f,-0.0010f,-3868.0410f),Vector3D(319.3798f,-0.0005f,-869.4220f),Vector3D(-1100.0853f,-0.0010f,-3992.2447f),Vector3D(-177.4330f,-0.0005f,-958.1404f),Vector3D(-195.1756f,-0.0010f,-3211.5393f),Vector3D(550.0426f,0.0000f,141.9468f),Vector3D(124.2032f,0.0000f,-514.5559f),Vector3D(-1313.0047f,0.0000f,-443.5835f),Vector3D(7834.6639f,-0.0019f,-5626.8988f),Vector3D(8651.7196f,-0.0019f,-4667.6502f),Vector3D(8104.1617f,-0.0014f,-1821.1718f),Vector3D(8928.1030f,-0.0014f,-1151.7076f),Vector3D(6874.2976f,-0.0005f,1968.9217f),Vector3D(5065.4244f,-0.0005f,2355.8578f),Vector3D(1946.8336f,-0.0005f,-2955.6465f),Vector3D(-33.3281f,-0.0010f,-3043.2425f),Vector3D(-2164.6843f,0.0005f,177.4330f),Vector3D(-1685.6146f,0.0005f,443.5825f),Vector3D(-3335.7420f,0.0010f,2146.9402f),Vector3D(-2643.7528f,0.0010f,1703.3577f)};
    Vector3D* ShockedMouth2Vectors = new Vector3D[14] {Vector3D(2265.8443f,-0.0005f,337.1426f),Vector3D(1676.5251f,-0.0005f,1091.3162f),Vector3D(1558.4488f,-0.0005f,-176.2158f),Vector3D(1539.4106f,-0.0005f,671.0651f),Vector3D(3512.0430f,-0.0010f,-2190.9101f),Vector3D(3401.6519f,-0.0010f,-1905.2026f),Vector3D(176.1918f,-0.0005f,-1585.1512f),Vector3D(440.2270f,-0.0005f,-1671.2999f),Vector3D(150.5737f,0.0005f,1911.6101f),Vector3D(-96.3240f,0.0005f,1209.2500f),Vector3D(32.6552f,0.0000f,-206.5263f),Vector3D(-981.7917f,0.0005f,258.0457f),Vector3D(-91.0410f,0.0000f,-346.4284f),Vector3D(335.4573f,0.0000f,-642.2386f)};
    Vector3D* GentleEyeVectors = new Vector3D[16] {Vector3D(405.8666f,-0.0005f,-617.6682f),Vector3D(-826.7927f,0.0000f,-1273.6998f),Vector3D(-617.4564f,0.0000f,-552.1288f),Vector3D(1689.3682f,-0.0005f,-677.2146f),Vector3D(-430.9292f,0.0000f,139.0686f),Vector3D(918.5638f,0.0000f,520.8988f),Vector3D(-290.0739f,0.0000f,674.5586f),Vector3D(939.4784f,0.0005f,2372.8104f),Vector3D(1365.4199f,0.0000f,1683.1656f),Vector3D(-48.3611f,0.0005f,1549.9449f),Vector3D(6913.7034f,-0.0005f,-3956.8005f),Vector3D(7647.0385f,-0.0005f,-3083.8699f),Vector3D(6999.4287f,0.0000f,-138.2704f),Vector3D(7771.1873f,0.0000f,429.0762f),Vector3D(5997.9982f,0.0000f,2909.7328f),Vector3D(4359.0040f,0.0005f,3248.6773f)};
    Vector3D* GentleMouthVectors = new Vector3D[13] {Vector3D(209.4707f,-0.0005f,-1380.0356f),Vector3D(2932.5752f,-0.0005f,1071.9924f),Vector3D(110.8971f,-0.0005f,-1527.8966f),Vector3D(2834.0015f,-0.0005f,690.0184f),Vector3D(2328.8107f,-0.0014f,-3363.8361f),Vector3D(2328.8107f,-0.0014f,-3203.6536f),Vector3D(-345.0089f,0.0000f,-24.6434f),Vector3D(-542.1567f,0.0000f,345.0089f),Vector3D(-726.9826f,0.0000f,-197.1478f),Vector3D(-234.1135f,0.0005f,1071.9919f),Vector3D(-1170.5663f,0.0010f,1725.0443f),Vector3D(-542.1566f,-0.0010f,-2636.8537f),Vector3D(160.1830f,-0.0010f,-2624.5317f)};

    Morph morphs[45] = {
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
        Morph(14, EvilMouthIndexes, EvilMouthVectors),
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
        Morph(6, vrc_v_rrIndexes, vrc_v_rrVectors),
        Morph(49, CrashEmoticonIndexes, CrashEmoticonVectors),
        Morph(10, FrustratedEyeIndexes, FrustratedEyeVectors),
        Morph(10, FrustratedMouthIndexes, FrustratedMouthVectors),
        Morph(22, DizzyEyeIndexes, DizzyEyeVectors),
        Morph(11, DizzyMouthIndexes, DizzyMouthVectors),
        Morph(34, ShockedEyeIndexes, ShockedEyeVectors),
        Morph(14, ShockedMouth2Indexes, ShockedMouth2Vectors),
        Morph(16, GentleEyeIndexes, GentleEyeVectors),
        Morph(13, GentleMouthIndexes, GentleMouthVectors)
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
