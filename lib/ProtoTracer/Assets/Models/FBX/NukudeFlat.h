#pragma once

#include "Utils/Morph.h"
#include "../../../Utils/Math/Rotation.h"
#include "../../../Scene/Materials/Static/SimpleMaterial.h"
#include "../../../Scene/Objects/Object3D.h"
#include "../../../Renderer/Utils/IndexGroup.h"

class NukudeFace{
public:
    enum Morphs {
        Frown,
        Doubt,
        Surprised,
        Sadness,
        Anger,
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
        vrc_v_aa,
        LookDown,
        LookUp,
        Blink,
        BiggerNose,
        MoveEye,
        HideBlush
    };

private:
    Vector3D basisVertices[54] = {Vector3D(114.4961f,100.4348f,38.0390f),Vector3D(-16.2406f,183.0337f,90.2627f),Vector3D(41.1693f,158.5203f,68.8966f),Vector3D(37.7711f,137.6436f,76.2594f),Vector3D(40.1910f,177.0351f,61.4203f),Vector3D(-36.5644f,156.8831f,105.9506f),Vector3D(-30.0644f,169.5036f,101.0011f),Vector3D(19.1438f,167.7457f,77.4576f),Vector3D(-2.8963f,170.2276f,87.8225f),Vector3D(61.0096f,144.0314f,61.4888f),Vector3D(15.1167f,148.7076f,85.6432f),Vector3D(23.9513f,186.1461f,66.5753f),Vector3D(-8.3186f,153.6293f,95.1737f),Vector3D(1.8648f,189.6453f,78.1480f),Vector3D(62.8154f,121.5189f,65.6606f),Vector3D(55.0487f,161.4408f,58.6482f),Vector3D(-13.5575f,83.7609f,100.1844f),Vector3D(-19.7301f,81.3303f,101.3765f),Vector3D(0.5099f,74.5742f,93.8843f),Vector3D(-5.4593f,67.5740f,93.8118f),Vector3D(15.7293f,63.7347f,84.6558f),Vector3D(9.4177f,52.3987f,82.8788f),Vector3D(116.2399f,95.3274f,35.1901f),Vector3D(112.1099f,94.6706f,38.0922f),Vector3D(116.1206f,87.1254f,32.6282f),Vector3D(103.6440f,101.5216f,46.6482f),Vector3D(100.7730f,96.9670f,47.8381f),Vector3D(107.8638f,96.8928f,42.0946f),Vector3D(109.1810f,103.3158f,43.0500f),Vector3D(92.9030f,37.9899f,-0.0001f),Vector3D(107.1882f,50.2625f,-0.0001f),Vector3D(82.7367f,33.0260f,17.4882f),Vector3D(94.1791f,44.5764f,17.1952f),Vector3D(61.8107f,28.2406f,32.4678f),Vector3D(76.5997f,40.4917f,32.2235f),Vector3D(53.6406f,37.4347f,49.0390f),Vector3D(63.4320f,48.6924f,49.0095f),Vector3D(41.8656f,45.4268f,61.3487f),Vector3D(50.9254f,59.2305f,62.7153f),Vector3D(21.2053f,39.8635f,69.2860f),Vector3D(28.5759f,53.4154f,72.6573f),Vector3D(-22.6342f,120.6927f,95.4003f),Vector3D(-15.7318f,136.4694f,95.4003f),Vector3D(-6.3644f,137.4555f,95.4003f),Vector3D(-8.8295f,110.0926f,95.4003f),Vector3D(0.5380f,108.1205f,95.4003f),Vector3D(3.4961f,136.2230f,95.4003f),Vector3D(18.2869f,132.5253f,95.4003f),Vector3D(5.7147f,106.8880f,95.4003f),Vector3D(14.0962f,105.4089f,95.4003f),Vector3D(27.1613f,128.8276f,95.4003f),Vector3D(33.3241f,126.1159f,95.4003f),Vector3D(31.5985f,107.1345f,95.4003f),Vector3D(80.0f,180.0f,90.0f)};
    IndexGroup basisIndexes[44] = {IndexGroup(13,8,7),IndexGroup(2,3,14),IndexGroup(8,6,5),IndexGroup(13,1,6),IndexGroup(11,7,2),IndexGroup(15,4,2),IndexGroup(7,10,3),IndexGroup(8,12,10),IndexGroup(34,36,35),IndexGroup(19,18,16),IndexGroup(21,20,18),IndexGroup(23,24,22),IndexGroup(25,26,27),IndexGroup(28,27,23),IndexGroup(37,38,40),IndexGroup(31,29,30),IndexGroup(32,34,33),IndexGroup(36,38,37),IndexGroup(39,40,20),IndexGroup(11,13,7),IndexGroup(9,2,14),IndexGroup(12,8,5),IndexGroup(8,13,6),IndexGroup(4,11,2),IndexGroup(9,15,2),IndexGroup(2,7,3),IndexGroup(7,8,10),IndexGroup(33,34,35),IndexGroup(17,19,16),IndexGroup(19,21,18),IndexGroup(0,23,22),IndexGroup(28,25,27),IndexGroup(0,28,23),IndexGroup(39,37,40),IndexGroup(32,31,30),IndexGroup(31,32,33),IndexGroup(35,36,37),IndexGroup(21,39,20),IndexGroup(50,52,49),IndexGroup(48,45,47),IndexGroup(42,43,44),IndexGroup(44,41,42),IndexGroup(52,50,51),IndexGroup(47,45,46)};
    StaticTriangleGroup<54,44> triangleGroup = StaticTriangleGroup<54,44>(&basisVertices[0], &basisIndexes[0]);
	TriangleGroup<54,44> triangleGroupMemory = TriangleGroup<54,44>(&triangleGroup);
	SimpleMaterial simpleMaterial = SimpleMaterial(RGBColor(128, 128, 128));
	Object3D basisObj = Object3D(&triangleGroup, &triangleGroupMemory, &simpleMaterial);

    static const byte morphCount = 26;
    int FrownIndexes[4] = {16,17,18,19};
    int DoubtIndexes[41] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40};
    int SurprisedIndexes[41] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40};
    int SadnessIndexes[41] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40};
    int AngerIndexes[41] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40};
    int vrc_v_silIndexes[17] = {17,18,19,20,21,29,30,31,32,33,34,35,36,37,38,39,40};
    int vrc_v_thIndexes[18] = {16,17,18,19,20,21,29,30,31,32,33,34,35,36,37,38,39,40};
    int vrc_v_nnIndexes[18] = {16,17,18,19,20,21,29,30,31,32,33,34,35,36,37,38,39,40};
    int vrc_v_ssIndexes[18] = {16,17,18,19,20,21,29,30,31,32,33,34,35,36,37,38,39,40};
    int vrc_v_rrIndexes[18] = {16,17,18,19,20,21,29,30,31,32,33,34,35,36,37,38,39,40};
    int vrc_v_ddIndexes[18] = {16,17,18,19,20,21,29,30,31,32,33,34,35,36,37,38,39,40};
    int vrc_v_kkIndexes[18] = {16,17,18,19,20,21,29,30,31,32,33,34,35,36,37,38,39,40};
    int vrc_v_ffIndexes[18] = {16,17,18,19,20,21,29,30,31,32,33,34,35,36,37,38,39,40};
    int vrc_v_ppIndexes[18] = {16,17,18,19,20,21,29,30,31,32,33,34,35,36,37,38,39,40};
    int vrc_v_chIndexes[18] = {16,17,18,19,20,21,29,30,31,32,33,34,35,36,37,38,39,40};
    int vrc_v_ouIndexes[18] = {16,17,18,19,20,21,29,30,31,32,33,34,35,36,37,38,39,40};
    int vrc_v_ohIndexes[18] = {16,17,18,19,20,21,29,30,31,32,33,34,35,36,37,38,39,40};
    int vrc_v_ihIndexes[18] = {16,17,18,19,20,21,29,30,31,32,33,34,35,36,37,38,39,40};
    int vrc_v_eeIndexes[18] = {16,17,18,19,20,21,29,30,31,32,33,34,35,36,37,38,39,40};
    int vrc_v_aaIndexes[17] = {17,18,19,20,21,29,30,31,32,33,34,35,36,37,38,39,40};
    int LookDownIndexes[41] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40};
    int LookUpIndexes[41] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40};
    int BlinkIndexes[41] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40};
    int BiggerNoseIndexes[8] = {0,22,23,24,25,26,27,28};
    int MoveEyeIndexes[15] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
    int HideBlushIndexes[12] = {41,42,43,44,45,46,47,48,49,50,51,52};

    Vector3D FrownVectors[4] = {Vector3D(0.0000f,-19.4851f,-3.4480f),Vector3D(0.0000f,-23.5129f,-3.9973f),Vector3D(-0.6649f,-9.0778f,-2.1497f),Vector3D(0.0000f,-10.3950f,-2.5070f)};
    Vector3D DoubtVectors[41] = {Vector3D(0.0000f,-0.0517f,0.0000f),Vector3D(0.0000f,-8.0583f,1.8777f),Vector3D(0.0000f,-4.7676f,1.4656f),Vector3D(0.0000f,-5.9648f,1.0459f),Vector3D(0.0000f,-11.2302f,5.8390f),Vector3D(0.0000f,-0.0517f,0.0000f),Vector3D(0.0000f,-4.1523f,0.0000f),Vector3D(0.0000f,-7.4048f,1.4656f),Vector3D(0.0000f,-4.7676f,1.4656f),Vector3D(0.0000f,-0.0517f,0.0000f),Vector3D(0.0000f,-8.3994f,1.7433f),Vector3D(-1.9359f,-17.3088f,8.4284f),Vector3D(0.0000f,-5.6169f,1.0455f),Vector3D(0.0000f,-17.6029f,6.1743f),Vector3D(0.0000f,-0.0517f,0.0000f),Vector3D(-5.6166f,2.6142f,3.9949f),Vector3D(0.0000f,-0.0517f,0.0000f),Vector3D(0.0000f,-0.0517f,0.0000f),Vector3D(0.0000f,-0.0517f,0.0000f),Vector3D(0.0000f,-0.0517f,0.0000f),Vector3D(0.0000f,-0.0517f,0.0000f),Vector3D(0.0000f,-0.0517f,0.0000f),Vector3D(0.0000f,-0.0517f,0.0000f),Vector3D(0.0000f,-0.0517f,0.0000f),Vector3D(0.0000f,-0.0517f,0.0000f),Vector3D(0.0000f,-0.0517f,0.0000f),Vector3D(0.0000f,-0.0517f,0.0000f),Vector3D(0.0000f,-0.0517f,0.0000f),Vector3D(0.0000f,-0.0517f,0.0000f),Vector3D(0.0000f,-0.0517f,0.0000f),Vector3D(0.0000f,-0.0517f,0.0000f),Vector3D(0.0000f,-0.0517f,0.0000f),Vector3D(0.0000f,-0.0517f,0.0000f),Vector3D(0.0000f,-0.0517f,0.0000f),Vector3D(0.0000f,-0.0517f,0.0000f),Vector3D(0.0000f,-0.0517f,0.0000f),Vector3D(0.0000f,-0.0517f,0.0000f),Vector3D(0.0000f,-0.0517f,0.0000f),Vector3D(0.0000f,-0.0517f,0.0000f),Vector3D(0.0000f,-0.0517f,0.0000f),Vector3D(0.0000f,-0.0517f,0.0000f)};
    Vector3D SurprisedVectors[41] = {Vector3D(0.0000f,-0.5973f,0.0000f),Vector3D(0.0000f,-2.6498f,-0.0117f),Vector3D(0.0000f,-0.5973f,0.0000f),Vector3D(-1.3083f,-8.3401f,2.3432f),Vector3D(0.0000f,1.7060f,-0.4845f),Vector3D(0.0000f,-0.5973f,0.0000f),Vector3D(0.0000f,-0.5973f,-0.6554f),Vector3D(0.0000f,-0.5973f,0.0000f),Vector3D(0.0000f,-0.5973f,0.0000f),Vector3D(0.0000f,-0.5973f,0.0000f),Vector3D(0.0000f,-12.4351f,3.3125f),Vector3D(0.0000f,3.2196f,-0.3583f),Vector3D(0.0000f,-8.7105f,1.8587f),Vector3D(0.0000f,0.5973f,0.3253f),Vector3D(0.0000f,-0.5973f,0.0000f),Vector3D(0.0000f,-3.2289f,0.0000f),Vector3D(0.0000f,-0.5973f,0.0000f),Vector3D(0.0000f,-0.5973f,0.0000f),Vector3D(0.0000f,-0.5973f,0.0000f),Vector3D(0.0000f,-0.5973f,0.0000f),Vector3D(0.0000f,-0.5973f,0.0000f),Vector3D(0.0000f,-0.5973f,0.0000f),Vector3D(0.0000f,-0.5973f,0.0000f),Vector3D(0.0000f,-0.5973f,0.0000f),Vector3D(0.0000f,-0.5973f,0.0000f),Vector3D(0.0000f,-0.5973f,0.0000f),Vector3D(0.0000f,-0.5973f,0.0000f),Vector3D(0.0000f,-0.5973f,0.0000f),Vector3D(0.0000f,-0.5973f,0.0000f),Vector3D(0.0000f,-0.5973f,0.0000f),Vector3D(0.0000f,-0.5973f,0.0000f),Vector3D(0.0000f,-0.5973f,0.0000f),Vector3D(0.0000f,-0.5973f,0.0000f),Vector3D(0.0000f,-0.5973f,0.0000f),Vector3D(0.0000f,-0.5973f,0.0000f),Vector3D(0.0000f,-0.5973f,0.0000f),Vector3D(0.0000f,-0.5973f,0.0000f),Vector3D(0.0000f,-0.5973f,0.0000f),Vector3D(0.0000f,-0.5973f,0.0000f),Vector3D(0.0000f,-0.5973f,0.0000f),Vector3D(0.0000f,-0.5973f,0.0000f)};
    Vector3D SadnessVectors[41] = {Vector3D(0.0000f,-0.0906f,0.0000f),Vector3D(0.0000f,-9.9653f,2.0739f),Vector3D(0.0000f,-0.0906f,0.0000f),Vector3D(0.0000f,-0.0906f,0.0000f),Vector3D(0.0000f,-0.0906f,0.0000f),Vector3D(0.0000f,-0.0906f,0.0000f),Vector3D(0.0000f,-0.0906f,0.0000f),Vector3D(0.0000f,-3.0830f,0.9056f),Vector3D(0.0000f,-3.9807f,0.8888f),Vector3D(0.0000f,-0.0906f,0.0000f),Vector3D(0.0000f,-0.0906f,0.0000f),Vector3D(0.0000f,-0.0906f,0.6324f),Vector3D(0.0000f,-0.0906f,0.0000f),Vector3D(0.0000f,-13.9156f,4.4366f),Vector3D(0.0000f,-0.0906f,0.0000f),Vector3D(0.0000f,-0.0906f,0.0000f),Vector3D(0.0000f,-0.0906f,0.0000f),Vector3D(0.0000f,-0.0906f,0.0000f),Vector3D(0.0000f,-0.0906f,0.0000f),Vector3D(0.0000f,-0.0906f,0.0000f),Vector3D(0.0000f,-0.0906f,0.0000f),Vector3D(0.0000f,-0.0906f,0.0000f),Vector3D(0.0000f,-0.0906f,0.0000f),Vector3D(0.0000f,-0.0906f,0.0000f),Vector3D(0.0000f,-0.0906f,0.0000f),Vector3D(0.0000f,-0.0906f,0.0000f),Vector3D(0.0000f,-0.0906f,0.0000f),Vector3D(0.0000f,-0.0906f,0.0000f),Vector3D(0.0000f,-0.0906f,0.0000f),Vector3D(0.0000f,-0.0906f,0.0000f),Vector3D(0.0000f,-0.0906f,0.0000f),Vector3D(0.0000f,-0.0906f,0.0000f),Vector3D(0.0000f,-0.0906f,0.0000f),Vector3D(0.0000f,-0.0906f,0.0000f),Vector3D(0.0000f,-0.0906f,0.0000f),Vector3D(0.0000f,-0.0906f,0.0000f),Vector3D(0.0000f,-0.0906f,0.0000f),Vector3D(0.0000f,-0.0906f,0.0000f),Vector3D(0.0000f,-0.0906f,0.0000f),Vector3D(0.0000f,-0.0906f,0.0000f),Vector3D(0.0000f,-0.0906f,0.0000f)};
    Vector3D AngerVectors[41] = {Vector3D(0.0000f,0.1536f,0.0000f),Vector3D(0.0000f,0.1536f,0.0000f),Vector3D(0.0000f,-8.3546f,2.4040f),Vector3D(0.0000f,0.1536f,0.0000f),Vector3D(0.0000f,-8.4615f,3.7219f),Vector3D(0.0000f,0.1536f,0.0000f),Vector3D(0.0000f,0.1536f,0.0000f),Vector3D(0.0000f,-6.4574f,2.4040f),Vector3D(0.0000f,0.1536f,0.0000f),Vector3D(0.2929f,-5.1186f,1.0403f),Vector3D(0.0000f,0.1536f,0.0000f),Vector3D(-3.2219f,-4.3656f,4.7320f),Vector3D(0.0000f,0.1536f,0.0000f),Vector3D(0.0000f,4.7536f,-1.5115f),Vector3D(0.0000f,0.1536f,0.0000f),Vector3D(0.0000f,1.1929f,0.2456f),Vector3D(0.0000f,0.1536f,0.0000f),Vector3D(0.0000f,0.1536f,0.0000f),Vector3D(0.0000f,0.1536f,0.0000f),Vector3D(0.0000f,0.1536f,0.0000f),Vector3D(0.0000f,0.1536f,0.0000f),Vector3D(0.0000f,0.1536f,0.0000f),Vector3D(0.0000f,0.1536f,0.0000f),Vector3D(0.0000f,0.1536f,0.0000f),Vector3D(0.0000f,0.1536f,0.0000f),Vector3D(0.0000f,0.1536f,0.0000f),Vector3D(0.0000f,0.1536f,0.0000f),Vector3D(0.0000f,0.1536f,0.0000f),Vector3D(0.0000f,0.1536f,0.0000f),Vector3D(0.0000f,0.1536f,0.0000f),Vector3D(0.0000f,0.1536f,0.0000f),Vector3D(0.0000f,0.1536f,0.0000f),Vector3D(0.0000f,0.1536f,0.0000f),Vector3D(0.0000f,0.1536f,0.0000f),Vector3D(0.0000f,0.1536f,0.0000f),Vector3D(0.0000f,0.1536f,0.0000f),Vector3D(0.0000f,0.1536f,0.0000f),Vector3D(0.0000f,0.1536f,0.0000f),Vector3D(0.0000f,0.1536f,0.0000f),Vector3D(0.0000f,0.1536f,0.0000f),Vector3D(0.0000f,0.1536f,0.0000f)};
    Vector3D vrc_v_silVectors[17] = {Vector3D(0.0000f,-0.0911f,-0.0101f),Vector3D(0.0000f,0.0237f,0.0009f),Vector3D(-0.0515f,-0.0860f,0.0000f),Vector3D(0.0000f,0.0643f,0.0268f),Vector3D(-0.0705f,-0.1041f,-0.0167f),Vector3D(-0.1191f,-0.1434f,0.0000f),Vector3D(0.0508f,0.0410f,0.0000f),Vector3D(-0.1390f,-0.1242f,-0.0032f),Vector3D(0.0597f,0.0469f,0.0000f),Vector3D(-0.0737f,-0.1027f,-0.0173f),Vector3D(0.0677f,0.0590f,0.0096f),Vector3D(-0.0893f,-0.1116f,-0.0309f),Vector3D(0.0780f,0.0645f,0.0000f),Vector3D(-0.0530f,-0.1266f,-0.0494f),Vector3D(0.0726f,0.0424f,-0.0122f),Vector3D(-0.0713f,-0.1144f,-0.0233f),Vector3D(0.0140f,0.0368f,0.0145f)};
    Vector3D vrc_v_thVectors[18] = {Vector3D(55.7137f,-22.2539f,-30.6447f),Vector3D(57.3329f,-23.1836f,-30.8233f),Vector3D(49.2026f,-12.0649f,-27.9191f),Vector3D(46.8795f,-13.8555f,-27.8181f),Vector3D(44.0447f,-5.3543f,-25.3489f),Vector3D(38.7850f,-7.6427f,-25.5255f),Vector3D(-8.1507f,-7.0605f,0.0000f),Vector3D(-1.5652f,-2.5408f,0.0000f),Vector3D(-1.6069f,-3.8519f,-7.0329f),Vector3D(5.0344f,-0.3199f,-6.8186f),Vector3D(13.2976f,-1.1604f,-11.9691f),Vector3D(15.6842f,0.8370f,-12.3657f),Vector3D(18.4484f,-5.6751f,-19.0777f),Vector3D(27.8347f,-3.1722f,-19.0476f),Vector3D(26.4203f,-8.8531f,-22.8275f),Vector3D(32.1776f,-8.6533f,-22.3755f),Vector3D(34.2168f,-3.3388f,-23.0582f),Vector3D(40.8266f,-2.1968f,-23.3941f)};
    Vector3D vrc_v_nnVectors[18] = {Vector3D(10.3832f,-4.9453f,-5.7070f),Vector3D(10.3832f,-6.4953f,-6.0773f),Vector3D(9.2577f,-1.5436f,-4.6158f),Vector3D(7.5258f,-5.7149f,-5.6158f),Vector3D(8.4137f,-0.1044f,-4.5801f),Vector3D(5.3768f,-3.8705f,-5.1054f),Vector3D(-5.7003f,-4.9747f,0.0000f),Vector3D(0.9587f,0.5786f,0.0000f),Vector3D(-3.8337f,-3.8842f,-1.1310f),Vector3D(2.0397f,1.1999f,-1.0434f),Vector3D(-1.0585f,-3.0941f,-1.9226f),Vector3D(3.5898f,1.6312f,-1.4451f),Vector3D(0.9537f,-4.1197f,-3.8531f),Vector3D(9.7005f,-0.6937f,-3.1317f),Vector3D(2.9793f,-4.6032f,-5.0208f),Vector3D(6.3255f,-1.0398f,-3.8029f),Vector3D(4.3005f,-3.2232f,-4.8067f),Vector3D(7.4736f,0.0000f,-4.0987f)};
    Vector3D vrc_v_ssVectors[18] = {Vector3D(55.7137f,-22.2539f,-30.6447f),Vector3D(57.3329f,-23.1836f,-30.8233f),Vector3D(49.2026f,-12.0649f,-27.9191f),Vector3D(46.8795f,-13.8555f,-27.8181f),Vector3D(44.0447f,-5.3543f,-25.3489f),Vector3D(38.7850f,-7.6427f,-25.5255f),Vector3D(-8.1507f,-7.0605f,0.0000f),Vector3D(-1.5652f,-2.5408f,0.0000f),Vector3D(-1.6069f,-3.8519f,-7.0329f),Vector3D(5.0344f,-0.3199f,-6.8186f),Vector3D(13.2976f,-1.1604f,-11.9691f),Vector3D(15.6842f,0.8370f,-12.3657f),Vector3D(18.4484f,-5.6751f,-19.0777f),Vector3D(27.8347f,-3.1722f,-19.0476f),Vector3D(26.4203f,-8.8531f,-22.8275f),Vector3D(32.1776f,-8.6533f,-22.3755f),Vector3D(34.2168f,-3.3388f,-23.0582f),Vector3D(40.8266f,-2.1968f,-23.3941f)};
    Vector3D vrc_v_rrVectors[18] = {Vector3D(10.3832f,-4.9453f,-5.7070f),Vector3D(10.3832f,-6.4953f,-6.0773f),Vector3D(9.2577f,-1.5436f,-4.6158f),Vector3D(7.5258f,-5.7149f,-5.6158f),Vector3D(8.4137f,-0.1044f,-4.5801f),Vector3D(5.3768f,-3.8705f,-5.1054f),Vector3D(-5.7003f,-4.9747f,0.0000f),Vector3D(0.9587f,0.5786f,0.0000f),Vector3D(-3.8337f,-3.8842f,-1.1310f),Vector3D(2.0397f,1.1999f,-1.0434f),Vector3D(-1.0585f,-3.0941f,-1.9226f),Vector3D(3.5898f,1.6312f,-1.4451f),Vector3D(0.9537f,-4.1197f,-3.8531f),Vector3D(9.7005f,-0.6937f,-3.1317f),Vector3D(2.9793f,-4.6032f,-5.0208f),Vector3D(6.3255f,-1.0398f,-3.8029f),Vector3D(4.3005f,-3.2232f,-4.8067f),Vector3D(7.4736f,0.0000f,-4.0987f)};
    Vector3D vrc_v_ddVectors[18] = {Vector3D(10.3832f,-4.9453f,-5.7070f),Vector3D(10.3832f,-6.4953f,-6.0773f),Vector3D(9.2577f,-1.5436f,-4.6158f),Vector3D(7.5258f,-5.7149f,-5.6158f),Vector3D(8.4137f,-0.1044f,-4.5801f),Vector3D(5.3768f,-3.8705f,-5.1054f),Vector3D(-5.7003f,-4.9747f,0.0000f),Vector3D(0.9587f,0.5786f,0.0000f),Vector3D(-3.8337f,-3.8842f,-1.1310f),Vector3D(2.0397f,1.1999f,-1.0434f),Vector3D(-1.0585f,-3.0941f,-1.9226f),Vector3D(3.5898f,1.6312f,-1.4451f),Vector3D(0.9537f,-4.1197f,-3.8531f),Vector3D(9.7005f,-0.6937f,-3.1317f),Vector3D(2.9793f,-4.6032f,-5.0208f),Vector3D(6.3255f,-1.0398f,-3.8029f),Vector3D(4.3005f,-3.2232f,-4.8067f),Vector3D(7.4736f,0.0000f,-4.0987f)};
    Vector3D vrc_v_kkVectors[18] = {Vector3D(10.3832f,-4.9453f,-5.7070f),Vector3D(10.3832f,-6.4953f,-6.0773f),Vector3D(9.2577f,-1.5436f,-4.6158f),Vector3D(7.5258f,-5.7149f,-5.6158f),Vector3D(8.4137f,-0.1044f,-4.5801f),Vector3D(5.3768f,-3.8705f,-5.1054f),Vector3D(-5.7003f,-4.9747f,0.0000f),Vector3D(0.9587f,0.5786f,0.0000f),Vector3D(-3.8337f,-3.8842f,-1.1310f),Vector3D(2.0397f,1.1999f,-1.0434f),Vector3D(-1.0585f,-3.0941f,-1.9226f),Vector3D(3.5898f,1.6312f,-1.4451f),Vector3D(0.9537f,-4.1197f,-3.8531f),Vector3D(9.7005f,-0.6937f,-3.1317f),Vector3D(2.9793f,-4.6032f,-5.0208f),Vector3D(6.3255f,-1.0398f,-3.8029f),Vector3D(4.3005f,-3.2232f,-4.8067f),Vector3D(7.4736f,0.0000f,-4.0987f)};
    Vector3D vrc_v_ffVectors[18] = {Vector3D(50.5221f,-19.7813f,-27.7912f),Vector3D(53.8863f,-20.9971f,-28.9628f),Vector3D(44.5737f,-11.2931f,-25.6112f),Vector3D(43.1167f,-10.9981f,-25.0102f),Vector3D(39.8379f,-6.9527f,-24.1192f),Vector3D(36.0966f,-5.7074f,-23.6100f),Vector3D(-3.1818f,-2.6147f,0.0000f),Vector3D(-2.0446f,-2.8302f,0.0000f),Vector3D(2.4288f,0.0487f,-6.4674f),Vector3D(4.0145f,-0.9198f,-6.2969f),Vector3D(16.6971f,2.3452f,-11.6713f),Vector3D(13.8893f,0.0214f,-11.6432f),Vector3D(18.1844f,-2.1488f,-17.6998f),Vector3D(22.9845f,-3.4401f,-17.4817f),Vector3D(24.2933f,-6.5516f,-20.3171f),Vector3D(28.7599f,-8.1333f,-20.4741f),Vector3D(32.3730f,-1.7273f,-20.7728f),Vector3D(37.0898f,-3.8473f,-22.1694f)};
    Vector3D vrc_v_ppVectors[18] = {Vector3D(50.5221f,-19.7813f,-27.7912f),Vector3D(53.8863f,-20.9971f,-28.9628f),Vector3D(44.5737f,-11.2931f,-25.6112f),Vector3D(43.1167f,-10.9981f,-25.0102f),Vector3D(39.8379f,-6.9527f,-24.1192f),Vector3D(36.0966f,-5.7074f,-23.6100f),Vector3D(-3.1818f,-2.6147f,0.0000f),Vector3D(-2.0446f,-2.8302f,0.0000f),Vector3D(2.4288f,0.0487f,-6.4674f),Vector3D(4.0145f,-0.9198f,-6.2969f),Vector3D(16.6971f,2.3452f,-11.6713f),Vector3D(13.8893f,0.0214f,-11.6432f),Vector3D(18.1844f,-2.1488f,-17.6998f),Vector3D(22.9845f,-3.4401f,-17.4817f),Vector3D(24.2933f,-6.5516f,-20.3171f),Vector3D(28.7599f,-8.1333f,-20.4741f),Vector3D(32.3730f,-1.7273f,-20.7728f),Vector3D(37.0898f,-3.8473f,-22.1694f)};
    Vector3D vrc_v_chVectors[18] = {Vector3D(50.5221f,-19.7813f,-27.7912f),Vector3D(52.1413f,-19.9360f,-27.7846f),Vector3D(44.5737f,-11.2931f,-25.6112f),Vector3D(43.1167f,-10.9981f,-25.0102f),Vector3D(39.8379f,-5.3022f,-23.0589f),Vector3D(36.0966f,-5.7074f,-22.9728f),Vector3D(-5.3006f,-4.5732f,0.0000f),Vector3D(-2.0446f,-2.8302f,0.0000f),Vector3D(0.3100f,-1.9098f,-6.4674f),Vector3D(4.0145f,-0.9198f,-6.2969f),Vector3D(13.8269f,0.3867f,-11.0078f),Vector3D(13.8893f,0.0214f,-11.6432f),Vector3D(17.9716f,-3.6153f,-17.1511f),Vector3D(22.9845f,-2.8253f,-17.4817f),Vector3D(24.9306f,-6.5516f,-20.3171f),Vector3D(29.0149f,-8.1333f,-20.4741f),Vector3D(32.0665f,-1.7273f,-20.6548f),Vector3D(37.0898f,-2.1968f,-21.3447f)};
    Vector3D vrc_v_ouVectors[18] = {Vector3D(41.5329f,-19.7813f,-22.8279f),Vector3D(49.2123f,-22.8400f,-25.6120f),Vector3D(41.4017f,-9.0964f,-22.2196f),Vector3D(40.1876f,-13.9021f,-22.4630f),Vector3D(39.5621f,-3.9489f,-23.0589f),Vector3D(33.1676f,-8.6115f,-22.9728f),Vector3D(-10.4177f,-9.2525f,0.0000f),Vector3D(4.2162f,2.6211f,0.0000f),Vector3D(-3.7964f,-5.6544f,-6.4674f),Vector3D(10.0717f,5.8024f,-4.1736f),Vector3D(9.7627f,-3.1048f,-10.8375f),Vector3D(20.2069f,7.9198f,-9.0634f),Vector3D(15.4620f,-7.5212f,-18.3048f),Vector3D(21.7707f,-2.0925f,-16.2415f),Vector3D(22.0016f,-9.4557f,-20.4349f),Vector3D(29.2406f,-4.1591f,-17.9281f),Vector3D(30.3579f,-4.6313f,-21.3640f),Vector3D(36.1608f,0.0000f,-20.6379f)};
    Vector3D vrc_v_ohVectors[18] = {Vector3D(41.5329f,-19.7813f,-22.8279f),Vector3D(41.5329f,-25.9811f,-24.3093f),Vector3D(37.0308f,-6.1748f,-18.4634f),Vector3D(30.1032f,-22.8592f,-22.4630f),Vector3D(33.6550f,-0.4173f,-18.3202f),Vector3D(21.5072f,-15.4820f,-20.4218f),Vector3D(-22.8011f,-19.8990f,0.0000f),Vector3D(3.8350f,2.3145f,0.0000f),Vector3D(-15.3348f,-15.5370f,-4.5241f),Vector3D(8.1590f,4.7995f,-4.1736f),Vector3D(-4.2340f,-12.3763f,-7.6903f),Vector3D(14.3593f,6.5249f,-5.7802f),Vector3D(3.8149f,-16.4784f,-15.4125f),Vector3D(14.9136f,-2.7747f,-12.5269f),Vector3D(11.9171f,-18.4128f,-20.0831f),Vector3D(25.3021f,-4.1591f,-15.2117f),Vector3D(17.2019f,-12.8928f,-19.2269f),Vector3D(29.8943f,0.0000f,-16.3948f)};
    Vector3D vrc_v_ihVectors[18] = {Vector3D(-1.2097f,-7.5390f,-0.4844f),Vector3D(1.0150f,-10.6264f,-1.0883f),Vector3D(-6.2079f,-2.3909f,1.6494f),Vector3D(-9.0888f,-5.9046f,2.7358f),Vector3D(-7.3105f,1.7397f,5.1746f),Vector3D(-11.1172f,-0.5831f,6.1909f),Vector3D(-11.3047f,-9.8536f,0.0000f),Vector3D(-2.4897f,-3.0050f,0.0000f),Vector3D(-9.1238f,-7.7668f,0.0557f),Vector3D(-1.0489f,-1.8323f,0.0000f),Vector3D(-4.5751f,-5.2331f,1.9684f),Vector3D(-1.5496f,0.0000f,2.0561f),Vector3D(-8.0493f,-5.0303f,0.9413f),Vector3D(1.2997f,0.0000f,-0.3553f),Vector3D(-8.1619f,-3.3666f,1.4302f),Vector3D(-1.8067f,0.0000f,1.5485f),Vector3D(-10.0850f,0.5141f,7.2497f),Vector3D(-6.6223f,2.7824f,5.0436f)};
    Vector3D vrc_v_eeVectors[18] = {Vector3D(-1.1700f,-14.4306f,-1.3944f),Vector3D(0.0000f,-22.1947f,-4.3495f),Vector3D(2.8776f,-6.0434f,-1.7126f),Vector3D(-8.8729f,-17.7731f,-2.0173f),Vector3D(2.8776f,-0.0088f,0.2740f),Vector3D(-10.2401f,-12.3874f,-1.1393f),Vector3D(-8.8729f,-8.2239f,0.0000f),Vector3D(2.8776f,2.0616f,0.0000f),Vector3D(-8.8729f,-8.2239f,-0.0149f),Vector3D(2.8776f,2.0616f,0.0000f),Vector3D(-8.8729f,-8.2239f,-0.0149f),Vector3D(2.8776f,2.0616f,0.0000f),Vector3D(-8.8729f,-8.2239f,-0.0149f),Vector3D(2.8776f,2.0616f,0.0000f),Vector3D(-8.8729f,-8.2239f,-0.0149f),Vector3D(2.8776f,2.0616f,0.0000f),Vector3D(-8.8729f,-8.2239f,-0.0149f),Vector3D(2.8776f,2.0616f,0.0000f)};
    Vector3D vrc_v_aaVectors[17] = {Vector3D(0.0000f,-9.1072f,-1.0137f),Vector3D(0.0000f,2.3650f,0.0896f),Vector3D(-5.1450f,-8.5993f,0.0045f),Vector3D(0.0000f,6.4290f,2.6851f),Vector3D(-7.0489f,-10.4099f,-1.6690f),Vector3D(-11.9073f,-14.3399f,0.0000f),Vector3D(5.0838f,4.0978f,0.0000f),Vector3D(-13.8950f,-12.4182f,-0.3235f),Vector3D(5.9699f,4.6809f,0.0000f),Vector3D(-7.3737f,-10.2708f,-1.7323f),Vector3D(6.7721f,5.9013f,0.9566f),Vector3D(-8.9346f,-11.1617f,-3.0909f),Vector3D(7.7971f,6.4411f,0.0000f),Vector3D(-5.3012f,-12.6539f,-4.9366f),Vector3D(7.2642f,4.2376f,-1.2217f),Vector3D(-7.1340f,-11.4447f,-2.3333f),Vector3D(1.3999f,3.6860f,1.4474f)};
    Vector3D LookDownVectors[41] = {Vector3D(0.0000f,1.9651f,0.0000f),Vector3D(-1.3824f,-0.4366f,1.2314f),Vector3D(-0.3478f,-0.7458f,0.9131f),Vector3D(-0.0675f,0.6679f,0.3004f),Vector3D(-0.2032f,-2.0200f,1.4330f),Vector3D(0.2056f,1.2564f,0.0814f),Vector3D(-0.7922f,0.6767f,0.5863f),Vector3D(-0.3141f,-1.1281f,1.0664f),Vector3D(-0.7620f,-0.5709f,0.9801f),Vector3D(0.5309f,0.1761f,0.1665f),Vector3D(-0.1113f,0.1166f,0.4351f),Vector3D(-0.6462f,-2.3766f,1.8816f),Vector3D(-0.5261f,0.5282f,0.4684f),Vector3D(-0.8626f,-1.9651f,1.6705f),Vector3D(0.0000f,1.9651f,0.0000f),Vector3D(0.4570f,-0.8116f,0.6738f),Vector3D(0.0000f,1.9651f,0.0000f),Vector3D(0.0000f,1.9651f,0.0000f),Vector3D(0.0000f,1.9651f,0.0000f),Vector3D(0.0000f,1.9651f,0.0000f),Vector3D(0.0000f,1.9651f,0.0000f),Vector3D(0.0000f,1.9651f,0.0000f),Vector3D(0.0000f,1.9651f,0.0000f),Vector3D(0.0000f,1.9651f,0.0000f),Vector3D(0.0000f,1.9651f,0.0000f),Vector3D(0.0000f,1.9651f,0.0000f),Vector3D(0.0000f,1.9651f,0.0000f),Vector3D(0.0000f,1.9651f,0.0000f),Vector3D(0.0000f,1.9651f,0.0000f),Vector3D(0.0000f,1.9651f,0.0000f),Vector3D(0.0000f,1.9651f,0.0000f),Vector3D(0.0000f,1.9651f,0.0000f),Vector3D(0.0000f,1.9651f,0.0000f),Vector3D(0.0000f,1.9651f,0.0000f),Vector3D(0.0000f,1.9651f,0.0000f),Vector3D(0.0000f,1.9651f,0.0000f),Vector3D(0.0000f,1.9651f,0.0000f),Vector3D(0.0000f,1.9651f,0.0000f),Vector3D(0.0000f,1.9651f,0.0000f),Vector3D(0.0000f,1.9651f,0.0000f),Vector3D(0.0000f,1.9651f,0.0000f)};
    Vector3D LookUpVectors[41] = {Vector3D(0.0000f,-1.1409f,0.0000f),Vector3D(0.0000f,1.9349f,-1.7761f),Vector3D(0.0000f,-1.1409f,0.0000f),Vector3D(0.0000f,-1.1409f,0.0000f),Vector3D(0.0000f,3.6837f,-2.0789f),Vector3D(0.0000f,-1.1409f,0.0000f),Vector3D(0.0000f,-1.1409f,0.0000f),Vector3D(0.0000f,-1.1409f,0.0000f),Vector3D(0.0000f,-1.1409f,0.0000f),Vector3D(0.0000f,-1.1409f,0.0000f),Vector3D(0.0000f,-1.1409f,0.0000f),Vector3D(-2.1400f,3.6837f,-1.6088f),Vector3D(0.0000f,-1.1409f,0.0000f),Vector3D(0.0000f,1.1409f,-1.3506f),Vector3D(0.0000f,-1.1409f,0.0000f),Vector3D(0.0000f,-1.1409f,0.0000f),Vector3D(0.0000f,-1.1409f,0.0000f),Vector3D(0.0000f,-1.1409f,0.0000f),Vector3D(0.0000f,-1.1409f,0.0000f),Vector3D(0.0000f,-1.1409f,0.0000f),Vector3D(0.0000f,-1.1409f,0.0000f),Vector3D(0.0000f,-1.1409f,0.0000f),Vector3D(0.0000f,-1.1409f,0.0000f),Vector3D(0.0000f,-1.1409f,0.0000f),Vector3D(0.0000f,-1.1409f,0.0000f),Vector3D(0.0000f,-1.1409f,0.0000f),Vector3D(0.0000f,-1.1409f,0.0000f),Vector3D(0.0000f,-1.1409f,0.0000f),Vector3D(0.0000f,-1.1409f,0.0000f),Vector3D(0.0000f,-1.1409f,0.0000f),Vector3D(0.0000f,-1.1409f,0.0000f),Vector3D(0.0000f,-1.1409f,0.0000f),Vector3D(0.0000f,-1.1409f,0.0000f),Vector3D(0.0000f,-1.1409f,0.0000f),Vector3D(0.0000f,-1.1409f,0.0000f),Vector3D(0.0000f,-1.1409f,0.0000f),Vector3D(0.0000f,-1.1409f,0.0000f),Vector3D(0.0000f,-1.1409f,0.0000f),Vector3D(0.0000f,-1.1409f,0.0000f),Vector3D(0.0000f,-1.1409f,0.0000f),Vector3D(0.0000f,-1.1409f,0.0000f)};
    Vector3D BlinkVectors[41] = {Vector3D(0.0000f,-0.0210f,0.0000f),Vector3D(-13.8244f,-24.0375f,12.3138f),Vector3D(-3.4777f,-27.1298f,9.1312f),Vector3D(-0.6750f,-12.9923f,3.0040f),Vector3D(-2.0319f,-39.8720f,14.3298f),Vector3D(2.0556f,-7.1069f,0.8142f),Vector3D(-7.9220f,-12.9051f,5.8626f),Vector3D(-3.1409f,-30.9533f,10.6644f),Vector3D(-7.6205f,-25.3806f,9.8006f),Vector3D(5.3085f,-17.9106f,1.6652f),Vector3D(-1.1131f,-18.5057f,4.3507f),Vector3D(-6.4618f,-43.4383f,18.8162f),Vector3D(-5.2613f,-14.3898f,4.6838f),Vector3D(-8.6257f,-39.3234f,16.7054f),Vector3D(0.0000f,-0.0210f,0.0000f),Vector3D(4.5701f,-27.7888f,6.7381f),Vector3D(0.0000f,-0.0210f,0.0000f),Vector3D(0.0000f,-0.1121f,-0.0101f),Vector3D(0.0000f,0.0027f,0.0009f),Vector3D(-0.0515f,-0.1070f,0.0000f),Vector3D(0.0000f,0.0433f,0.0268f),Vector3D(-0.0705f,-0.1252f,-0.0167f),Vector3D(0.0000f,-0.0210f,0.0000f),Vector3D(0.0000f,-0.0210f,0.0000f),Vector3D(0.0000f,-0.0210f,0.0000f),Vector3D(0.0000f,-0.0210f,0.0000f),Vector3D(0.0000f,-0.0210f,0.0000f),Vector3D(0.0000f,-0.0210f,0.0000f),Vector3D(0.0000f,-0.0210f,0.0000f),Vector3D(-0.1191f,-0.1644f,0.0000f),Vector3D(0.0508f,0.0200f,0.0000f),Vector3D(-0.1390f,-0.1452f,-0.0032f),Vector3D(0.0597f,0.0259f,0.0000f),Vector3D(-0.0737f,-0.1237f,-0.0173f),Vector3D(0.0677f,0.0380f,0.0096f),Vector3D(-0.0893f,-0.1326f,-0.0309f),Vector3D(0.0780f,0.0435f,0.0000f),Vector3D(-0.0530f,-0.1476f,-0.0494f),Vector3D(0.0726f,0.0214f,-0.0122f),Vector3D(-0.0713f,-0.1354f,-0.0233f),Vector3D(0.0140f,0.0158f,0.0145f)};
    Vector3D BiggerNoseVectors[8] = {Vector3D(8.4117f,22.0785f,0.0000f),Vector3D(9.9468f,17.5824f,0.0000f),Vector3D(6.3111f,17.0042f,0.0000f),Vector3D(9.8417f,10.3621f,0.0000f),Vector3D(-1.1415f,23.0352f,0.0000f),Vector3D(-3.6689f,19.0258f,0.0000f),Vector3D(2.5732f,18.9604f,0.0000f),Vector3D(3.7327f,24.6146f,0.0000f)};
    Vector3D MoveEyeVectors[15] = {Vector3D(-6.2779f,4.9326f,0.0000f),Vector3D(-6.2779f,4.9326f,0.0000f),Vector3D(-6.2779f,4.9326f,0.0000f),Vector3D(-6.2779f,4.9326f,0.0000f),Vector3D(-6.2779f,4.9326f,0.0000f),Vector3D(-6.2779f,4.9326f,0.0000f),Vector3D(-6.2779f,4.9326f,0.0000f),Vector3D(-6.2779f,4.9326f,0.0000f),Vector3D(-6.2779f,4.9326f,0.0000f),Vector3D(-6.2779f,4.9326f,0.0000f),Vector3D(-6.2779f,4.9326f,0.0000f),Vector3D(-6.2779f,4.9326f,0.0000f),Vector3D(-6.2779f,4.9326f,0.0000f),Vector3D(-6.2779f,4.9326f,0.0000f),Vector3D(-6.2779f,4.9326f,0.0000f)};
    Vector3D HideBlushVectors[12] = {Vector3D(29.3262f,48.2032f,0.0000f),Vector3D(22.4307f,32.4422f,0.0000f),Vector3D(13.0726f,31.4571f,0.0000f),Vector3D(15.5353f,58.7927f,0.0000f),Vector3D(6.1772f,60.7628f,0.0000f),Vector3D(3.2220f,32.6885f,0.0000f),Vector3D(-11.5540f,36.3825f,0.0000f),Vector3D(1.0056f,61.9941f,0.0000f),Vector3D(-7.3674f,63.4717f,0.0000f),Vector3D(-20.4195f,40.0765f,0.0000f),Vector3D(-26.5762f,42.7854f,0.0000f),Vector3D(-24.8523f,61.7478f,0.0000f)};

    Morph morphs[26] = {
        Morph(4, FrownIndexes, FrownVectors),
        Morph(41, DoubtIndexes, DoubtVectors),
        Morph(41, SurprisedIndexes, SurprisedVectors),
        Morph(41, SadnessIndexes, SadnessVectors),
        Morph(41, AngerIndexes, AngerVectors),
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
        Morph(17, vrc_v_aaIndexes, vrc_v_aaVectors),
        Morph(41, LookDownIndexes, LookDownVectors),
        Morph(41, LookUpIndexes, LookUpVectors),
        Morph(41, BlinkIndexes, BlinkVectors),
        Morph(8, BiggerNoseIndexes, BiggerNoseVectors),
        Morph(15, MoveEyeIndexes, MoveEyeVectors),
        Morph(12, HideBlushIndexes, HideBlushVectors)
    };

public:
    NukudeFace(){}

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
