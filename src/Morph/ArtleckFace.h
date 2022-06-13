#pragma once

#include "Arduino.h"
#include "..\Math\Rotation.h"
#include "Morph.h"
#include "..\Materials\SimpleMaterial.h"
#include "..\Render\IndexGroup.h"
#include "..\Render\Object3D.h"

class ArtleckFace{
public:
    enum Morphs {
        Doubt,
        Surprised,
        Sadness,
        Anger,
        LookDown,
        LookUp,
        Blink,
        Frown,
        vrc_v_sil,
        vrc_v_th,
        vrc_v_nn,
        vrc_v_ss,
        vrc_v_rr,
        vrc_v_dd,
        vrc_v_kk,
        vrc_v_ff,
        vrc_v_pp,
        vrc_v_ch,
        vrc_v_ou,
        vrc_v_oh,
        vrc_v_ih,
        vrc_v_ee,
        vrc_v_aa
    };

private:
    Vector3D basisVertices[43] = {Vector3D(124.5121f,128.4426f,38.0390f),Vector3D(-116.2399f,-189.6453f,-157.7461f),Vector3D(-116.2399f,-189.6453f,157.7461f),Vector3D(-13.5575f,83.7609f,100.1844f),Vector3D(-19.7301f,81.3303f,101.3765f),Vector3D(0.5099f,74.5742f,93.8843f),Vector3D(-5.4593f,67.5740f,93.8118f),Vector3D(15.7293f,63.7347f,84.6558f),Vector3D(9.4177f,52.3987f,82.8787f),Vector3D(126.2560f,123.3352f,35.1901f),Vector3D(122.1260f,122.6784f,38.0922f),Vector3D(126.1367f,115.1332f,32.6282f),Vector3D(113.6601f,129.5294f,46.6482f),Vector3D(110.7891f,124.9748f,47.8381f),Vector3D(117.8798f,124.9005f,42.0946f),Vector3D(119.1971f,131.3236f,43.0500f),Vector3D(101.8869f,35.5422f,-0.0001f),Vector3D(107.1882f,50.2625f,-0.0001f),Vector3D(85.6418f,30.8234f,17.4882f),Vector3D(94.1791f,44.5764f,17.1952f),Vector3D(61.8107f,28.2406f,32.4678f),Vector3D(76.5997f,40.4917f,32.2235f),Vector3D(53.6406f,37.4347f,49.0389f),Vector3D(63.4320f,48.6924f,49.0095f),Vector3D(41.8656f,45.4268f,61.3486f),Vector3D(50.9254f,59.2305f,62.7153f),Vector3D(21.2053f,39.8635f,69.2860f),Vector3D(28.5759f,53.4154f,72.6573f),Vector3D(-54.4529f,188.7751f,90.2627f),Vector3D(15.6081f,152.1762f,70.8560f),Vector3D(3.3854f,135.3741f,76.2594f),Vector3D(13.0987f,166.4444f,63.2206f),Vector3D(-40.4225f,160.6541f,102.4187f),Vector3D(-46.6512f,174.9827f,101.0011f),Vector3D(-5.5156f,155.3279f,82.3806f),Vector3D(-26.6245f,166.1712f,90.9944f),Vector3D(39.5996f,135.3590f,55.2955f),Vector3D(-15.7252f,139.5587f,85.6432f),Vector3D(-4.3928f,173.1405f,69.9518f),Vector3D(-32.4702f,150.1820f,95.1737f),Vector3D(-24.2665f,179.1493f,78.1480f),Vector3D(19.9433f,135.0883f,65.6605f),Vector3D(25.5838f,157.7392f,58.6482f)};
    IndexGroup basisIndexes[38] = {IndexGroup(21,23,22),IndexGroup(6,5,3),IndexGroup(8,7,5),IndexGroup(10,11,9),IndexGroup(12,13,14),IndexGroup(15,14,10),IndexGroup(24,25,27),IndexGroup(18,16,17),IndexGroup(19,21,20),IndexGroup(23,25,24),IndexGroup(26,27,7),IndexGroup(20,21,22),IndexGroup(4,6,3),IndexGroup(6,8,5),IndexGroup(0,10,9),IndexGroup(15,12,14),IndexGroup(0,15,10),IndexGroup(26,24,27),IndexGroup(19,18,17),IndexGroup(18,19,20),IndexGroup(22,23,24),IndexGroup(8,26,7),IndexGroup(40,35,34),IndexGroup(29,30,41),IndexGroup(35,33,32),IndexGroup(40,28,33),IndexGroup(38,34,29),IndexGroup(42,31,29),IndexGroup(34,37,30),IndexGroup(35,39,37),IndexGroup(38,40,34),IndexGroup(36,29,41),IndexGroup(39,35,32),IndexGroup(35,40,33),IndexGroup(31,38,29),IndexGroup(36,42,29),IndexGroup(29,34,30),IndexGroup(34,35,37)};
    TriangleGroup triangleGroup = TriangleGroup(&basisVertices[0], &basisIndexes[0], 43, 38);
    SimpleMaterial simpleMaterial = SimpleMaterial(RGBColor(128, 128, 128));
    Object3D basisObj = Object3D(&triangleGroup, &simpleMaterial);

    static const byte morphCount = 23;
    int DoubtIndexes[15] = {28,29,30,31,32,33,34,35,36,37,38,39,40,41,42};
    int SurprisedIndexes[15] = {28,29,30,31,32,33,34,35,36,37,38,39,40,41,42};
    int SadnessIndexes[15] = {28,29,30,31,32,33,34,35,36,37,38,39,40,41,42};
    int AngerIndexes[15] = {28,29,30,31,32,33,34,35,36,37,38,39,40,41,42};
    int LookDownIndexes[15] = {28,29,30,31,32,33,34,35,36,37,38,39,40,41,42};
    int LookUpIndexes[15] = {28,29,30,31,32,33,34,35,36,37,38,39,40,41,42};
    int BlinkIndexes[15] = {28,29,30,31,32,33,34,35,36,37,38,39,40,41,42};
    int FrownIndexes[19] = {3,4,5,6,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42};
    int vrc_v_silIndexes[17] = {4,5,6,7,8,16,17,18,19,20,21,22,23,24,25,26,27};
    int vrc_v_thIndexes[18] = {3,4,5,6,7,8,16,17,18,19,20,21,22,23,24,25,26,27};
    int vrc_v_nnIndexes[18] = {3,4,5,6,7,8,16,17,18,19,20,21,22,23,24,25,26,27};
    int vrc_v_ssIndexes[18] = {3,4,5,6,7,8,16,17,18,19,20,21,22,23,24,25,26,27};
    int vrc_v_rrIndexes[18] = {3,4,5,6,7,8,16,17,18,19,20,21,22,23,24,25,26,27};
    int vrc_v_ddIndexes[18] = {3,4,5,6,7,8,16,17,18,19,20,21,22,23,24,25,26,27};
    int vrc_v_kkIndexes[18] = {3,4,5,6,7,8,16,17,18,19,20,21,22,23,24,25,26,27};
    int vrc_v_ffIndexes[18] = {3,4,5,6,7,8,16,17,18,19,20,21,22,23,24,25,26,27};
    int vrc_v_ppIndexes[18] = {3,4,5,6,7,8,16,17,18,19,20,21,22,23,24,25,26,27};
    int vrc_v_chIndexes[18] = {3,4,5,6,7,8,16,17,18,19,20,21,22,23,24,25,26,27};
    int vrc_v_ouIndexes[18] = {3,4,5,6,7,8,16,17,18,19,20,21,22,23,24,25,26,27};
    int vrc_v_ohIndexes[18] = {3,4,5,6,7,8,16,17,18,19,20,21,22,23,24,25,26,27};
    int vrc_v_ihIndexes[18] = {3,4,5,6,7,8,16,17,18,19,20,21,22,23,24,25,26,27};
    int vrc_v_eeIndexes[18] = {3,4,5,6,7,8,16,17,18,19,20,21,22,23,24,25,26,27};
    int vrc_v_aaIndexes[18] = {3,4,5,6,7,8,16,17,18,19,20,21,22,23,24,25,26,27};

    Vector3D DoubtVectors[15] = {Vector3D(-1.2830f,-4.7105f,1.8777f),Vector3D(1.4503f,3.2458f,1.4656f),Vector3D(0.0000f,2.3024f,1.0459f),Vector3D(1.4503f,-3.2167f,5.8390f),Vector3D(-0.9238f,4.4197f,0.0000f),Vector3D(-0.8724f,0.4797f,0.0000f),Vector3D(-1.2690f,-0.0440f,1.4656f),Vector3D(0.0000f,2.5932f,1.4656f),Vector3D(1.4503f,7.9617f,0.0000f),Vector3D(-2.5379f,0.7743f,1.7433f),Vector3D(-0.2423f,-4.6508f,8.4284f),Vector3D(0.0000f,1.7439f,1.0455f),Vector3D(1.6423f,-5.1054f,6.1742f),Vector3D(1.8128f,9.0494f,0.0000f),Vector3D(-1.0845f,2.6512f,3.9949f)};
    Vector3D SurprisedVectors[15] = {Vector3D(-2.4121f,-10.1942f,-0.0117f),Vector3D(-2.4121f,-8.1418f,0.0000f),Vector3D(-2.6327f,-20.0540f,2.3432f),Vector3D(-0.5992f,-2.0315f,-0.4845f),Vector3D(-2.4121f,-8.1418f,0.0000f),Vector3D(-2.4121f,-8.1418f,-0.6554f),Vector3D(-2.4121f,-8.1418f,0.0000f),Vector3D(-2.4121f,-8.1418f,0.0000f),Vector3D(-2.4121f,-8.1418f,0.0000f),Vector3D(-2.4121f,-19.9795f,3.3125f),Vector3D(-1.6869f,-1.2431f,-0.3583f),Vector3D(-2.4121f,-16.2550f,1.8587f),Vector3D(-2.7746f,-0.9648f,0.3253f),Vector3D(-0.9618f,-16.2994f,0.0000f),Vector3D(1.0323f,-5.3349f,0.0000f)};
    Vector3D SadnessVectors[15] = {Vector3D(0.5598f,-18.8919f,2.0739f),Vector3D(-0.7752f,-0.2048f,0.0000f),Vector3D(-0.2516f,-4.1348f,0.0000f),Vector3D(-1.0774f,-2.6291f,0.0000f),Vector3D(0.3696f,-4.5001f,0.0000f),Vector3D(-0.9649f,-9.2214f,0.0000f),Vector3D(-0.7724f,-3.7345f,0.9056f),Vector3D(-1.0186f,-5.1724f,0.8888f),Vector3D(1.0637f,8.7887f,0.0000f),Vector3D(-0.3611f,-4.2598f,0.0000f),Vector3D(-3.0280f,-11.2820f,0.6324f),Vector3D(-0.7089f,-1.4271f,0.0000f),Vector3D(-1.0967f,-15.0484f,4.4366f),Vector3D(-0.3419f,-0.0890f,0.0000f),Vector3D(1.8874f,3.7454f,0.0000f)};
    Vector3D AngerVectors[15] = {Vector3D(0.0000f,-2.3000f,0.0000f),Vector3D(-3.7413f,-12.0933f,3.6291f),Vector3D(-4.2041f,-3.7941f,0.0000f),Vector3D(-0.4345f,-17.4562f,3.7219f),Vector3D(-0.7251f,-3.7502f,0.0000f),Vector3D(-1.4503f,-3.2064f,0.0000f),Vector3D(-1.5847f,-5.1377f,1.3139f),Vector3D(-1.1549f,-5.1179f,0.6616f),Vector3D(-2.1422f,-9.2297f,1.0403f),Vector3D(-3.3361f,-5.1427f,0.0000f),Vector3D(-0.4481f,-10.0561f,4.7320f),Vector3D(-1.4503f,-4.1128f,0.0000f),Vector3D(-1.0844f,-4.9872f,-1.5115f),Vector3D(-1.8508f,-6.2216f,0.0000f),Vector3D(-2.1194f,-17.3191f,0.2456f)};
    Vector3D LookDownVectors[15] = {Vector3D(-1.3824f,-0.4366f,1.2314f),Vector3D(-0.3478f,-0.7458f,0.9131f),Vector3D(-0.0675f,0.6679f,0.3004f),Vector3D(-0.2032f,-2.0200f,1.4330f),Vector3D(0.2056f,1.2564f,0.0814f),Vector3D(-0.7922f,0.6767f,0.5863f),Vector3D(-0.3141f,-1.1281f,1.0664f),Vector3D(-0.7620f,-0.5709f,0.9801f),Vector3D(0.5309f,0.1761f,0.1665f),Vector3D(-0.1113f,0.1166f,0.4351f),Vector3D(-0.6462f,-2.3766f,1.8816f),Vector3D(-0.5261f,0.5282f,0.4684f),Vector3D(-0.8626f,-1.9651f,1.6705f),Vector3D(0.0000f,1.9651f,0.0000f),Vector3D(0.4570f,-0.8116f,0.6738f)};
    Vector3D LookUpVectors[15] = {Vector3D(-1.2830f,-2.0781f,-1.7761f),Vector3D(-1.2830f,-5.1539f,0.0000f),Vector3D(-1.2830f,-5.1539f,0.0000f),Vector3D(-1.2830f,-0.3293f,-2.0789f),Vector3D(-1.2830f,-5.1539f,0.0000f),Vector3D(-1.2830f,-5.1539f,0.0000f),Vector3D(-1.2830f,-5.1539f,0.0000f),Vector3D(-1.2830f,-5.1539f,0.0000f),Vector3D(-1.2830f,-5.1539f,0.0000f),Vector3D(-1.2830f,-5.1539f,0.0000f),Vector3D(-3.4231f,-0.3293f,-1.6088f),Vector3D(-1.2830f,-5.1539f,0.0000f),Vector3D(-1.2830f,-2.8721f,-1.3506f),Vector3D(-1.2830f,-5.1539f,0.0000f),Vector3D(-1.2830f,-5.1539f,0.0000f)};
    Vector3D BlinkVectors[15] = {Vector3D(0.6782f,-16.1350f,12.3138f),Vector3D(-1.4836f,-9.9820f,9.1312f),Vector3D(-3.0317f,6.5122f,3.0040f),Vector3D(-0.2191f,-20.0049f,14.3298f),Vector3D(-0.8449f,0.6143f,0.8142f),Vector3D(-8.6472f,-1.3770f,5.8626f),Vector3D(-1.2974f,-4.8963f,10.6644f),Vector3D(-4.9732f,-5.9895f,9.8006f),Vector3D(3.4957f,-5.4761f,1.6652f),Vector3D(1.2436f,9.1565f,4.3507f),Vector3D(-1.2781f,-19.2105f,18.8162f),Vector3D(-1.9982f,6.9276f,4.6838f),Vector3D(-5.0034f,-16.8824f,16.7054f),Vector3D(-5.1230f,3.3287f,0.0000f),Vector3D(3.6976f,-16.9954f,6.7381f)};
    Vector3D FrownVectors[19] = {Vector3D(0.0000f,-19.4851f,-3.4480f),Vector3D(0.0000f,-23.5128f,-3.9973f),Vector3D(-0.6649f,-9.0778f,-2.1497f),Vector3D(0.0000f,-10.3950f,-2.5070f),Vector3D(0.6782f,-16.1350f,12.3138f),Vector3D(-1.0730f,-8.6978f,9.1312f),Vector3D(-3.0317f,6.5122f,3.0040f),Vector3D(0.1914f,-18.7208f,14.3298f),Vector3D(-0.8449f,0.6143f,0.8142f),Vector3D(-8.6472f,-1.3770f,5.8626f),Vector3D(-1.9132f,-6.8225f,10.6644f),Vector3D(-5.2298f,-6.7921f,9.8006f),Vector3D(4.8813f,-1.1421f,1.6652f),Vector3D(0.5764f,7.0697f,4.3507f),Vector3D(-5.0596f,-19.4170f,18.8162f),Vector3D(-1.9982f,6.9276f,4.6838f),Vector3D(-5.4140f,-18.1666f,16.7054f),Vector3D(-6.4781f,5.1774f,0.0000f),Vector3D(5.9557f,-9.9325f,6.7381f)};
    Vector3D vrc_v_silVectors[17] = {Vector3D(0.0000f,-0.0911f,-0.0101f),Vector3D(0.0000f,0.0237f,0.0009f),Vector3D(-0.0515f,-0.0860f,0.0000f),Vector3D(0.0000f,0.0643f,0.0268f),Vector3D(-0.0705f,-0.1041f,-0.0167f),Vector3D(-0.1191f,-0.1434f,0.0000f),Vector3D(0.0508f,0.0410f,0.0000f),Vector3D(-0.1390f,-0.1242f,-0.0032f),Vector3D(0.0597f,0.0469f,0.0000f),Vector3D(-0.0737f,-0.1027f,-0.0173f),Vector3D(0.0677f,0.0590f,0.0096f),Vector3D(-0.0893f,-0.1116f,-0.0309f),Vector3D(0.0780f,0.0645f,0.0000f),Vector3D(-0.0530f,-0.1266f,-0.0494f),Vector3D(0.0726f,0.0424f,-0.0122f),Vector3D(-0.0713f,-0.1144f,-0.0233f),Vector3D(0.0140f,0.0368f,0.0145f)};
    Vector3D vrc_v_thVectors[18] = {Vector3D(55.7137f,-22.2539f,-30.6447f),Vector3D(57.3329f,-23.1836f,-30.8233f),Vector3D(49.2026f,-12.0649f,-27.9191f),Vector3D(46.8795f,-13.8555f,-27.8181f),Vector3D(44.0447f,-5.3543f,-25.3489f),Vector3D(38.7850f,-7.6427f,-25.5255f),Vector3D(-2.4611f,-9.2482f,0.0000f),Vector3D(-1.0435f,-2.8305f,0.0000f),Vector3D(-1.6069f,-3.8519f,-7.0329f),Vector3D(5.0344f,-0.3199f,-6.8186f),Vector3D(13.2976f,-1.1604f,-11.9691f),Vector3D(15.6842f,0.8370f,-12.3657f),Vector3D(18.4484f,-5.6751f,-19.0777f),Vector3D(27.8347f,-3.1722f,-19.0476f),Vector3D(26.4203f,-8.8531f,-22.8275f),Vector3D(32.1776f,-8.6533f,-22.3755f),Vector3D(34.2168f,-3.3388f,-23.0582f),Vector3D(40.8266f,-2.1968f,-23.3941f)};
    Vector3D vrc_v_nnVectors[18] = {Vector3D(10.3832f,-4.9453f,-5.7070f),Vector3D(10.3832f,-6.4953f,-6.0773f),Vector3D(9.2577f,-1.5436f,-4.6158f),Vector3D(7.5258f,-5.7149f,-5.6157f),Vector3D(8.4137f,-0.1044f,-4.5801f),Vector3D(5.3768f,-3.8705f,-5.1054f),Vector3D(-1.4197f,-6.3433f,0.0000f),Vector3D(0.2899f,0.7924f,0.0000f),Vector3D(-3.8337f,-3.8842f,-1.1310f),Vector3D(2.0397f,1.1999f,-1.0434f),Vector3D(-1.0585f,-3.0941f,-1.9226f),Vector3D(3.5898f,1.6312f,-1.4451f),Vector3D(0.9537f,-4.1197f,-3.8531f),Vector3D(9.7005f,-0.6937f,-3.1317f),Vector3D(2.9793f,-4.6032f,-5.0208f),Vector3D(6.3255f,-1.0398f,-3.8029f),Vector3D(4.3005f,-3.2232f,-4.8067f),Vector3D(7.4736f,0.0000f,-4.0987f)};
    Vector3D vrc_v_ssVectors[18] = {Vector3D(55.7137f,-22.2539f,-30.6447f),Vector3D(57.3329f,-23.1836f,-30.8233f),Vector3D(49.2026f,-12.0649f,-27.9191f),Vector3D(46.8795f,-13.8555f,-27.8181f),Vector3D(44.0447f,-5.3543f,-25.3489f),Vector3D(38.7850f,-7.6427f,-25.5255f),Vector3D(-2.4248f,-8.6864f,0.0000f),Vector3D(-0.8221f,-2.7784f,0.0000f),Vector3D(-1.6069f,-3.8519f,-7.0329f),Vector3D(5.0344f,-0.3199f,-6.8186f),Vector3D(13.2976f,-1.1604f,-11.9691f),Vector3D(15.6842f,0.8370f,-12.3657f),Vector3D(18.4484f,-5.6751f,-19.0777f),Vector3D(27.8347f,-3.1722f,-19.0476f),Vector3D(26.4203f,-8.8531f,-22.8275f),Vector3D(32.1776f,-8.6533f,-22.3755f),Vector3D(34.2168f,-3.3388f,-23.0582f),Vector3D(40.8266f,-2.1968f,-23.3941f)};
    Vector3D vrc_v_rrVectors[18] = {Vector3D(10.3832f,-4.9453f,-5.7070f),Vector3D(10.3832f,-6.4953f,-6.0773f),Vector3D(9.2577f,-1.5436f,-4.6158f),Vector3D(7.5258f,-5.7149f,-5.6157f),Vector3D(8.4137f,-0.1044f,-4.5801f),Vector3D(5.3768f,-3.8705f,-5.1054f),Vector3D(-1.4643f,-6.3290f,0.0000f),Vector3D(0.4014f,0.7568f,0.0000f),Vector3D(-3.8337f,-3.8842f,-1.1310f),Vector3D(2.0397f,1.1999f,-1.0434f),Vector3D(-1.0585f,-3.0941f,-1.9226f),Vector3D(3.5898f,1.6312f,-1.4451f),Vector3D(0.9537f,-4.1197f,-3.8531f),Vector3D(9.7005f,-0.6937f,-3.1317f),Vector3D(2.9793f,-4.6032f,-5.0208f),Vector3D(6.3255f,-1.0398f,-3.8029f),Vector3D(4.3005f,-3.2232f,-4.8067f),Vector3D(7.4736f,0.0000f,-4.0987f)};
    Vector3D vrc_v_ddVectors[18] = {Vector3D(10.3832f,-4.9453f,-5.7070f),Vector3D(10.3832f,-6.4953f,-6.0773f),Vector3D(9.2577f,-1.5436f,-4.6158f),Vector3D(7.5258f,-5.7149f,-5.6157f),Vector3D(8.4137f,-0.1044f,-4.5801f),Vector3D(5.3768f,-3.8705f,-5.1054f),Vector3D(-1.1299f,-6.4359f,0.0000f),Vector3D(0.6243f,0.6855f,0.0000f),Vector3D(-3.8337f,-3.8842f,-1.1310f),Vector3D(2.0397f,1.1999f,-1.0434f),Vector3D(-1.0585f,-3.0941f,-1.9226f),Vector3D(3.5898f,1.6312f,-1.4451f),Vector3D(0.9537f,-4.1197f,-3.8531f),Vector3D(9.7005f,-0.6937f,-3.1317f),Vector3D(2.9793f,-4.6032f,-5.0208f),Vector3D(6.3255f,-1.0398f,-3.8029f),Vector3D(4.3005f,-3.2232f,-4.8067f),Vector3D(7.4736f,0.0000f,-4.0987f)};
    Vector3D vrc_v_kkVectors[18] = {Vector3D(10.3832f,-4.9453f,-5.7070f),Vector3D(10.3832f,-6.4953f,-6.0773f),Vector3D(9.2577f,-1.5436f,-4.6158f),Vector3D(7.5258f,-5.7149f,-5.6157f),Vector3D(8.4137f,-0.1044f,-4.5801f),Vector3D(5.3768f,-3.8705f,-5.1054f),Vector3D(-1.2414f,-6.4003f,0.0000f),Vector3D(0.4014f,0.7568f,0.0000f),Vector3D(-3.8337f,-3.8842f,-1.1310f),Vector3D(2.0397f,1.1999f,-1.0434f),Vector3D(-1.0585f,-3.0941f,-1.9226f),Vector3D(3.5898f,1.6312f,-1.4451f),Vector3D(0.9537f,-4.1197f,-3.8531f),Vector3D(9.7005f,-0.6937f,-3.1317f),Vector3D(2.9793f,-4.6032f,-5.0208f),Vector3D(6.3255f,-1.0398f,-3.8029f),Vector3D(4.3005f,-3.2232f,-4.8067f),Vector3D(7.4736f,0.0000f,-4.0987f)};
    Vector3D vrc_v_ffVectors[18] = {Vector3D(50.5221f,-19.7813f,-27.7912f),Vector3D(53.8863f,-20.9971f,-28.9628f),Vector3D(44.5737f,-11.2931f,-25.6112f),Vector3D(43.1166f,-10.9980f,-25.0102f),Vector3D(39.8379f,-6.9527f,-24.1192f),Vector3D(36.0966f,-5.7074f,-23.6100f),Vector3D(-0.4079f,-3.5015f,0.0000f),Vector3D(-1.0125f,-3.1602f,0.0000f),Vector3D(2.4288f,0.0487f,-6.4674f),Vector3D(4.0145f,-0.9198f,-6.2969f),Vector3D(16.6971f,2.3452f,-11.6713f),Vector3D(13.8893f,0.0214f,-11.6432f),Vector3D(18.1844f,-2.1488f,-17.6998f),Vector3D(22.9845f,-3.4401f,-17.4817f),Vector3D(24.2933f,-6.5516f,-20.3171f),Vector3D(28.7599f,-8.1333f,-20.4741f),Vector3D(32.3730f,-1.7273f,-20.7728f),Vector3D(37.0898f,-3.8473f,-22.1694f)};
    Vector3D vrc_v_ppVectors[18] = {Vector3D(50.5221f,-19.7813f,-27.7912f),Vector3D(53.8863f,-20.9971f,-28.9628f),Vector3D(44.5737f,-11.2931f,-25.6112f),Vector3D(43.1166f,-10.9980f,-25.0102f),Vector3D(39.8379f,-6.9527f,-24.1192f),Vector3D(36.0966f,-5.7074f,-23.6100f),Vector3D(-0.4079f,-3.5015f,0.0000f),Vector3D(-0.8835f,-3.2014f,0.0000f),Vector3D(2.4288f,0.0487f,-6.4674f),Vector3D(4.0145f,-0.9198f,-6.2969f),Vector3D(16.6971f,2.3452f,-11.6713f),Vector3D(13.8893f,0.0214f,-11.6432f),Vector3D(18.1844f,-2.1488f,-17.6998f),Vector3D(22.9845f,-3.4401f,-17.4817f),Vector3D(24.2933f,-6.5516f,-20.3171f),Vector3D(28.7599f,-8.1333f,-20.4741f),Vector3D(32.3730f,-1.7273f,-20.7728f),Vector3D(37.0898f,-3.8473f,-22.1694f)};
    Vector3D vrc_v_chVectors[18] = {Vector3D(50.5221f,-19.7813f,-27.7912f),Vector3D(52.1413f,-19.9360f,-27.7846f),Vector3D(44.5737f,-11.2931f,-25.6112f),Vector3D(43.1166f,-10.9980f,-25.0102f),Vector3D(39.8379f,-5.3021f,-23.0589f),Vector3D(36.0966f,-5.7074f,-22.9728f),Vector3D(-1.2365f,-5.8725f,0.0000f),Vector3D(-1.0770f,-3.1395f,0.0000f),Vector3D(0.3100f,-1.9097f,-6.4674f),Vector3D(4.0145f,-0.9198f,-6.2969f),Vector3D(13.8269f,0.3867f,-11.0078f),Vector3D(13.8893f,0.0214f,-11.6432f),Vector3D(17.9715f,-3.6153f,-17.1511f),Vector3D(22.9845f,-2.8253f,-17.4817f),Vector3D(24.9306f,-6.5516f,-20.3171f),Vector3D(29.0149f,-8.1333f,-20.4741f),Vector3D(32.0665f,-1.7273f,-20.6548f),Vector3D(37.0898f,-2.1968f,-21.3447f)};
    Vector3D vrc_v_ouVectors[18] = {Vector3D(41.5328f,-19.7813f,-22.8279f),Vector3D(49.2123f,-22.8400f,-25.6120f),Vector3D(41.4017f,-9.0964f,-22.2196f),Vector3D(40.1876f,-13.9021f,-22.4630f),Vector3D(39.5621f,-3.9489f,-23.0589f),Vector3D(33.1676f,-8.6115f,-22.9728f),Vector3D(-3.0636f,-11.6037f,0.0000f),Vector3D(1.2488f,3.5699f,0.0000f),Vector3D(-3.7964f,-5.6544f,-6.4674f),Vector3D(10.0717f,5.8024f,-4.1736f),Vector3D(9.7627f,-3.1048f,-10.8375f),Vector3D(20.2069f,7.9198f,-9.0634f),Vector3D(15.4620f,-7.5212f,-18.3048f),Vector3D(21.7707f,-2.0925f,-16.2415f),Vector3D(22.0016f,-9.4557f,-20.4349f),Vector3D(29.2406f,-4.1591f,-17.9281f),Vector3D(30.3579f,-4.6313f,-21.3640f),Vector3D(36.1608f,0.0000f,-20.6379f)};
    Vector3D vrc_v_ohVectors[18] = {Vector3D(41.5328f,-19.7813f,-22.8279f),Vector3D(42.1668f,-23.1975f,-24.3093f),Vector3D(37.0308f,-6.1748f,-18.4634f),Vector3D(32.1326f,-16.5115f,-22.4630f),Vector3D(33.6550f,-0.4173f,-18.3202f),Vector3D(23.5366f,-9.1342f,-20.4218f),Vector3D(-5.0571f,-18.5755f,0.0000f),Vector3D(1.1256f,3.1808f,0.0000f),Vector3D(-13.3053f,-9.1893f,-4.5241f),Vector3D(8.1590f,4.7995f,-4.1736f),Vector3D(-2.2045f,-6.0286f,-7.6903f),Vector3D(14.3593f,6.5249f,-5.7802f),Vector3D(5.8443f,-10.1306f,-15.4125f),Vector3D(14.9136f,-2.7747f,-12.5269f),Vector3D(13.9466f,-12.0651f,-20.0831f),Vector3D(25.3021f,-4.1591f,-15.2117f),Vector3D(19.2313f,-6.5451f,-19.2269f),Vector3D(29.8943f,0.0000f,-16.3948f)};
    Vector3D vrc_v_ihVectors[18] = {Vector3D(-1.2097f,-7.5390f,-0.4844f),Vector3D(1.0150f,-10.6264f,-1.0883f),Vector3D(-6.2079f,-2.3909f,1.6494f),Vector3D(-9.0888f,-5.9046f,2.7358f),Vector3D(-7.3105f,1.7397f,5.1746f),Vector3D(-11.1172f,-0.5831f,6.1909f),Vector3D(-3.4087f,-12.3781f,0.0000f),Vector3D(-0.9415f,-3.5000f,0.0000f),Vector3D(-9.1238f,-7.7668f,0.0557f),Vector3D(-1.0489f,-1.8323f,0.0000f),Vector3D(-4.5751f,-5.2331f,1.9684f),Vector3D(-1.5496f,0.0000f,2.0561f),Vector3D(-8.0493f,-5.0303f,0.9413f),Vector3D(1.2997f,0.0000f,-0.3553f),Vector3D(-8.1619f,-3.3666f,1.4302f),Vector3D(-1.8067f,0.0000f,1.5485f),Vector3D(-10.0850f,0.5141f,7.2497f),Vector3D(-6.6223f,2.7824f,5.0436f)};
    Vector3D vrc_v_eeVectors[18] = {Vector3D(-1.1700f,-14.4306f,-1.3944f),Vector3D(1.6335f,-17.0856f,-4.3495f),Vector3D(2.8776f,-6.0434f,-1.7126f),Vector3D(-7.2394f,-12.6639f,-2.0173f),Vector3D(2.8776f,-0.0088f,0.2740f),Vector3D(-8.6067f,-7.2782f,-1.1393f),Vector3D(-2.3704f,-10.3029f,0.0000f),Vector3D(1.2519f,2.5814f,0.0000f),Vector3D(-7.2394f,-3.1148f,-0.0149f),Vector3D(2.8776f,2.0616f,0.0000f),Vector3D(-7.2394f,-3.1148f,-0.0149f),Vector3D(2.8776f,2.0616f,0.0000f),Vector3D(-7.2394f,-3.1148f,-0.0149f),Vector3D(2.8776f,2.0616f,0.0000f),Vector3D(-7.2394f,-3.1148f,-0.0149f),Vector3D(2.8776f,2.0616f,0.0000f),Vector3D(-7.2395f,-3.1148f,-0.0149f),Vector3D(2.8776f,2.0616f,0.0000f)};
    Vector3D vrc_v_aaVectors[18] = {Vector3D(2.0528f,6.4208f,0.0000f),Vector3D(2.0528f,-2.6863f,-1.0137f),Vector3D(2.0528f,8.7858f,0.0896f),Vector3D(-3.0922f,-2.1785f,0.0045f),Vector3D(2.0528f,12.8498f,2.6851f),Vector3D(-4.2263f,-1.5813f,-1.6690f),Vector3D(-2.4973f,-10.2713f,0.0000f),Vector3D(4.1269f,11.4809f,0.0000f),Vector3D(-11.8422f,-5.9974f,-0.3235f),Vector3D(8.0227f,11.1017f,0.0000f),Vector3D(-5.1926f,-3.4487f,-1.7323f),Vector3D(8.8249f,12.3221f,0.9566f),Vector3D(-6.8817f,-4.7409f,-3.0909f),Vector3D(9.8500f,12.8619f,0.0000f),Vector3D(-3.2484f,-6.2331f,-4.9366f),Vector3D(9.3170f,10.6583f,-1.2217f),Vector3D(-4.3114f,-2.6162f,-2.3333f),Vector3D(3.4527f,10.1068f,1.4474f)};

    Morph morphs[23] = {
        Morph(15, DoubtIndexes, DoubtVectors),
        Morph(15, SurprisedIndexes, SurprisedVectors),
        Morph(15, SadnessIndexes, SadnessVectors),
        Morph(15, AngerIndexes, AngerVectors),
        Morph(15, LookDownIndexes, LookDownVectors),
        Morph(15, LookUpIndexes, LookUpVectors),
        Morph(15, BlinkIndexes, BlinkVectors),
        Morph(19, FrownIndexes, FrownVectors),
        Morph(17, vrc_v_silIndexes, vrc_v_silVectors),
        Morph(18, vrc_v_thIndexes, vrc_v_thVectors),
        Morph(18, vrc_v_nnIndexes, vrc_v_nnVectors),
        Morph(18, vrc_v_ssIndexes, vrc_v_ssVectors),
        Morph(18, vrc_v_rrIndexes, vrc_v_rrVectors),
        Morph(18, vrc_v_ddIndexes, vrc_v_ddVectors),
        Morph(18, vrc_v_kkIndexes, vrc_v_kkVectors),
        Morph(18, vrc_v_ffIndexes, vrc_v_ffVectors),
        Morph(18, vrc_v_ppIndexes, vrc_v_ppVectors),
        Morph(18, vrc_v_chIndexes, vrc_v_chVectors),
        Morph(18, vrc_v_ouIndexes, vrc_v_ouVectors),
        Morph(18, vrc_v_ohIndexes, vrc_v_ohVectors),
        Morph(18, vrc_v_ihIndexes, vrc_v_ihVectors),
        Morph(18, vrc_v_eeIndexes, vrc_v_eeVectors),
        Morph(18, vrc_v_aaIndexes, vrc_v_aaVectors)
    };

public:
    ArtleckFace(){}

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
