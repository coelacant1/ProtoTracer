#pragma once

#include "Arduino.h"
#include "..\Math\Rotation.h"
#include "Morph.h"
#include "..\Materials\SimpleMaterial.h"
#include "..\Render\IndexGroup.h"
#include "..\Render\Object3D.h"

class ProtoV2{
public:
    enum Morphs {
        Normal,
        Blink,
        Blush,
        Hideblush,
        Squint,
        Surprised,
        Happy,
        Sad,
        Talk,
        Whoop,
        Side1,
        Angry
    };

private:
    Vector3D basisVertices[127] = {Vector3D(56.7970f,65.6485f,100.3657f),Vector3D(265.6040f,113.6870f,120.6629f),Vector3D(0.0004f,36.6864f,100.3657f),Vector3D(25.5105f,62.8138f,100.3657f),Vector3D(138.5981f,54.2008f,100.3657f),Vector3D(59.8961f,82.5324f,100.3657f),Vector3D(67.4447f,60.4256f,100.3657f),Vector3D(127.6587f,50.9754f,100.3657f),Vector3D(362.8445f,156.2135f,132.5050f),Vector3D(342.6352f,172.1410f,129.0108f),Vector3D(53.7112f,10.5470f,100.3657f),Vector3D(61.6425f,19.3488f,100.3657f),Vector3D(74.0517f,16.1934f,100.3657f),Vector3D(109.1484f,2.9522f,103.3504f),Vector3D(0.4180f,68.3681f,100.3657f),Vector3D(11.4699f,69.3140f,100.3657f),Vector3D(102.1251f,36.2238f,100.3657f),Vector3D(115.1132f,43.1149f,100.3657f),Vector3D(125.5374f,39.5571f,100.3657f),Vector3D(116.0074f,29.1581f,100.3657f),Vector3D(97.4502f,23.2294f,100.3657f),Vector3D(79.9170f,25.9259f,100.3657f),Vector3D(3.1495f,57.0935f,100.3657f),Vector3D(367.4674f,193.9299f,100.3657f),Vector3D(73.6454f,91.6986f,100.3657f),Vector3D(106.5359f,100.5952f,99.9804f),Vector3D(90.3603f,60.6952f,100.6078f),Vector3D(122.7116f,101.6735f,100.0833f),Vector3D(132.1474f,97.3600f,100.3657f),Vector3D(139.5554f,72.8059f,100.3657f),Vector3D(114.8933f,61.2344f,100.5554f),Vector3D(50.7299f,72.2878f,100.6819f),Vector3D(48.5921f,59.8008f,100.2717f),Vector3D(135.6521f,61.5040f,100.3657f),Vector3D(372.0064f,188.4831f,100.3657f),Vector3D(349.7860f,210.8045f,100.3657f),Vector3D(366.4290f,196.8849f,100.3657f),Vector3D(248.1125f,107.9205f,100.3657f),Vector3D(345.8522f,212.9227f,100.3657f),Vector3D(244.7839f,113.3673f,100.3657f),Vector3D(245.3891f,166.0197f,100.3657f),Vector3D(41.5637f,59.8864f,98.8013f),Vector3D(352.0348f,180.9181f,100.3657f),Vector3D(367.5153f,159.3168f,132.9836f),Vector3D(122.1321f,18.4863f,106.6460f),Vector3D(346.0129f,174.5942f,129.3391f),Vector3D(372.1899f,186.6211f,132.4324f),Vector3D(18.7762f,7.0365f,100.3657f),Vector3D(40.2835f,6.5204f,100.3657f),Vector3D(21.8732f,1.8748f,100.3657f),Vector3D(87.3543f,-14.4367f,100.3657f),Vector3D(252.8591f,101.7578f,103.3504f),Vector3D(277.9875f,75.5938f,103.3504f),Vector3D(364.3916f,151.1221f,103.3504f),Vector3D(83.3986f,84.8471f,100.1636f),Vector3D(88.7427f,96.8208f,100.1915f),Vector3D(114.2466f,80.7352f,100.4623f),Vector3D(113.9403f,71.8718f,100.4727f),Vector3D(136.1913f,89.8114f,100.3657f),Vector3D(37.9127f,42.3725f,-0.0000f),Vector3D(46.5398f,39.4069f,-0.0000f),Vector3D(53.0100f,53.1562f,-0.0000f),Vector3D(45.7310f,55.3130f,-0.0000f),Vector3D(60.8283f,50.9995f,-0.0000f),Vector3D(55.1668f,38.5981f,-0.0000f),Vector3D(67.8377f,49.6515f,-0.0000f),Vector3D(62.9850f,37.2502f,-0.0000f),Vector3D(76.1951f,49.3819f,-0.0000f),Vector3D(71.6120f,36.9806f,-0.0000f),Vector3D(84.0134f,48.5731f,-0.0000f),Vector3D(80.2390f,36.1718f,-0.0000f),Vector3D(89.4052f,47.7643f,-0.0000f),Vector3D(86.9789f,35.0934f,-0.0000f),Vector3D(93.9883f,34.8238f,-0.0000f),Vector3D(96.9539f,46.9556f,-0.0000f),Vector3D(88.5156f,333.0924f,-0.0000f),Vector3D(83.7102f,211.3551f,-0.0000f),Vector3D(154.1897f,210.5542f,-0.0000f),Vector3D(154.1897f,333.0924f,-0.0000f),Vector3D(96.5247f,419.5899f,-0.0000f),Vector3D(96.5247f,368.3321f,-0.0000f),Vector3D(131.7644f,420.3908f,-0.0000f),Vector3D(129.3617f,370.7348f,-0.0000f),Vector3D(172.6104f,428.3998f,-0.0000f),Vector3D(188.6285f,326.6851f,-0.0000f),Vector3D(239.8863f,430.0016f,-0.0000f),Vector3D(246.2935f,345.1059f,-0.0000f),Vector3D(-46.0361f,365.1285f,-0.0000f),Vector3D(-73.2668f,196.9389f,-0.0000f),Vector3D(42.0633f,193.7353f,-0.0000f),Vector3D(79.7057f,363.5267f,-0.0000f),Vector3D(-44.4343f,508.4901f,-0.0000f),Vector3D(-204.6148f,511.6937f,-0.0000f),Vector3D(-214.2257f,363.5267f,-0.0000f),Vector3D(-130.9318f,357.1195f,-0.0000f),Vector3D(-134.2278f,431.8267f,-0.0000f),Vector3D(87.7147f,558.9470f,-0.0000f),Vector3D(98.9274f,454.0287f,-0.0000f),Vector3D(179.8186f,467.6441f,-0.0000f),Vector3D(171.8095f,573.3632f,-0.0000f),Vector3D(130.0132f,517.0163f,-0.0000f),Vector3D(175.6664f,522.4520f,-0.0000f),Vector3D(126.5239f,565.6000f,-0.0000f),Vector3D(136.4246f,460.3401f,-0.0000f),Vector3D(93.1139f,508.4258f,-0.0000f),Vector3D(216.2898f,382.4399f,-0.0000f),Vector3D(243.0140f,388.5588f,-0.0000f),Vector3D(180.9761f,375.2776f,-0.0000f),Vector3D(115.4618f,396.3075f,-0.0000f),Vector3D(115.8807f,420.0298f,-0.0000f),Vector3D(130.5710f,395.7268f,-0.0000f),Vector3D(96.5247f,395.0800f,-0.0000f),Vector3D(114.7858f,369.6683f,-0.0000f),Vector3D(117.2751f,282.6317f,-0.0000f),Vector3D(114.9435f,211.0002f,-0.0000f),Vector3D(154.1897f,277.9946f,-0.0000f),Vector3D(118.6662f,333.0924f,-0.0000f),Vector3D(86.4037f,279.5915f,-0.0000f),Vector3D(-6.8385f,288.8715f,-0.0000f),Vector3D(60.0452f,274.8454f,-0.0000f),Vector3D(-58.9986f,285.0660f,-0.0000f),Vector3D(9.5718f,364.4201f,-0.0000f),Vector3D(-17.0746f,195.3780f,-0.0000f),Vector3D(132.3952f,47.2461f,100.3657f),Vector3D(92.3680f,31.6994f,100.3657f),Vector3D(38.0854f,12.5826f,100.3657f),Vector3D(79.0373f,60.6952f,100.4931f)};
    IndexGroup basisIndexes[104] = {IndexGroup(1,8,9),IndexGroup(5,0,6),IndexGroup(16,124,20),IndexGroup(123,4,7),IndexGroup(18,7,17),IndexGroup(10,13,12),IndexGroup(43,46,45),IndexGroup(21,11,12),IndexGroup(2,3,22),IndexGroup(12,44,20),IndexGroup(11,10,12),IndexGroup(14,2,22),IndexGroup(15,14,22),IndexGroup(3,15,22),IndexGroup(21,12,20),IndexGroup(18,17,16),IndexGroup(19,18,16),IndexGroup(16,20,19),IndexGroup(42,34,23),IndexGroup(31,41,32),IndexGroup(6,24,5),IndexGroup(24,54,55),IndexGroup(54,26,25),IndexGroup(26,27,25),IndexGroup(56,28,27),IndexGroup(56,26,57),IndexGroup(57,30,29),IndexGroup(5,31,0),IndexGroup(31,32,0),IndexGroup(32,6,0),IndexGroup(30,33,29),IndexGroup(40,39,38),IndexGroup(35,36,37),IndexGroup(11,125,48),IndexGroup(11,48,10),IndexGroup(47,49,48),IndexGroup(50,10,48),IndexGroup(51,52,53),IndexGroup(24,6,54),IndexGroup(54,25,55),IndexGroup(57,29,58),IndexGroup(58,28,56),IndexGroup(56,57,58),IndexGroup(59,60,61),IndexGroup(59,61,62),IndexGroup(63,64,65),IndexGroup(64,66,65),IndexGroup(67,68,69),IndexGroup(68,70,69),IndexGroup(71,72,73),IndexGroup(73,74,71),IndexGroup(114,77,113),IndexGroup(113,115,78),IndexGroup(81,109,108),IndexGroup(82,108,112),IndexGroup(85,83,105),IndexGroup(105,86,106),IndexGroup(122,89,118),IndexGroup(93,95,92),IndexGroup(90,118,119),IndexGroup(90,91,87),IndexGroup(94,87,91),IndexGroup(95,93,94),IndexGroup(95,91,92),IndexGroup(103,98,100),IndexGroup(99,100,101),IndexGroup(102,96,100),IndexGroup(100,98,101),IndexGroup(100,99,102),IndexGroup(97,100,104),IndexGroup(100,97,103),IndexGroup(100,96,104),IndexGroup(107,84,105),IndexGroup(105,84,86),IndexGroup(106,85,105),IndexGroup(105,83,107),IndexGroup(82,110,108),IndexGroup(111,80,108),IndexGroup(109,79,108),IndexGroup(110,81,108),IndexGroup(108,79,111),IndexGroup(108,80,112),IndexGroup(116,75,113),IndexGroup(76,113,117),IndexGroup(113,76,114),IndexGroup(113,77,115),IndexGroup(113,78,116),IndexGroup(113,75,117),IndexGroup(90,121,118),IndexGroup(88,118,120),IndexGroup(118,89,119),IndexGroup(118,87,120),IndexGroup(121,87,118),IndexGroup(118,88,122),IndexGroup(7,18,123),IndexGroup(124,21,20),IndexGroup(125,47,48),IndexGroup(54,126,26),IndexGroup(54,6,126),IndexGroup(57,26,30),IndexGroup(26,56,27),IndexGroup(49,50,48),IndexGroup(121,90,87),IndexGroup(91,95,94)};
    TriangleGroup triangleGroup = TriangleGroup(&basisVertices[0], &basisIndexes[0], 127, 104);
    SimpleMaterial simpleMaterial = SimpleMaterial(RGBColor(128, 128, 128));
    Object3D basisObj = Object3D(&triangleGroup, &simpleMaterial);

    static const byte morphCount = 12;
    int NormalIndexes[16] = {59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74};
    int BlinkIndexes[13] = {0,5,24,25,27,28,29,31,54,55,56,57,58};
    int BlushIndexes[18] = {0,4,5,6,7,24,25,26,27,28,30,32,33,55,56,57,58,126};
    int HideblushIndexes[16] = {59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74};
    int SquintIndexes[20] = {4,5,7,16,17,18,19,20,24,25,27,28,31,44,54,55,56,58,123,124};
    int SurprisedIndexes[23] = {4,5,6,7,16,17,18,19,24,25,26,27,28,29,30,31,32,33,41,55,58,123,126};
    int HappyIndexes[20] = {0,4,5,6,7,18,19,24,25,26,27,28,30,32,33,55,57,58,123,126};
    int SadIndexes[29] = {0,4,6,7,12,13,16,17,18,19,20,21,24,25,26,27,28,29,30,32,33,44,50,55,56,57,123,124,126};
    int TalkIndexes[18] = {4,7,10,11,12,13,16,17,18,19,20,21,44,47,50,123,124,125};
    int WhoopIndexes[34] = {0,4,5,6,7,10,11,12,13,16,17,18,19,20,21,24,25,26,27,28,29,30,31,32,33,41,48,50,55,58,123,124,125,126};
    int Side1Indexes[6] = {9,37,38,42,45,53};
    int AngryIndexes[25] = {4,5,6,7,16,17,18,19,24,25,26,27,28,29,30,31,32,33,41,54,55,58,123,124,126};

    Vector3D NormalVectors[16] = {Vector3D(29.5887f,2.7041f,0.0000f),Vector3D(20.9418f,5.6785f,0.0000f),Vector3D(14.4566f,-8.1122f,0.0000f),Vector3D(21.7524f,-10.2754f,0.0000f),Vector3D(6.6203f,-5.9489f,0.0000f),Vector3D(12.2949f,6.4898f,0.0000f),Vector3D(-0.4053f,-4.5969f,0.0000f),Vector3D(4.4586f,7.8418f,0.0000f),Vector3D(-8.7820f,-4.3265f,0.0000f),Vector3D(-4.1884f,8.1122f,0.0000f),Vector3D(-16.6183f,-3.5153f,0.0000f),Vector3D(-12.8353f,8.9234f,0.0000f),Vector3D(-22.0227f,-2.7041f,0.0000f),Vector3D(-19.5907f,10.0050f,0.0000f),Vector3D(-26.6163f,10.2754f,0.0000f),Vector3D(-29.5887f,-1.8928f,0.0000f)};
    Vector3D BlinkVectors[13] = {Vector3D(0.6728f,-1.4485f,0.0000f),Vector3D(2.6959f,-16.1757f,0.0000f),Vector3D(-5.1223f,-25.3419f,0.0000f),Vector3D(-9.1662f,-32.3513f,0.0000f),Vector3D(-9.4358f,-32.6209f,0.0000f),Vector3D(-9.9750f,-27.7682f,0.0000f),Vector3D(-4.7121f,-3.7533f,0.0000f),Vector3D(0.8088f,-7.8182f,0.0000f),Vector3D(-1.1261f,-18.2208f,0.0000f),Vector3D(-1.0784f,-29.3858f,0.0000f),Vector3D(-7.1715f,-14.1089f,0.0000f),Vector3D(-1.4733f,-6.3239f,0.0000f),Vector3D(-7.2790f,-20.2196f,0.0000f)};
    Vector3D BlushVectors[18] = {Vector3D(2.1926f,6.3464f,0.0000f),Vector3D(2.0803f,8.8211f,0.0000f),Vector3D(4.6579f,0.8233f,0.0000f),Vector3D(0.1233f,15.9745f,0.0000f),Vector3D(-1.2687f,-2.2420f,0.0000f),Vector3D(4.8197f,-0.6918f,0.0000f),Vector3D(-0.2485f,-5.6469f,0.0000f),Vector3D(7.0580f,26.4166f,0.0000f),Vector3D(-3.6723f,-8.8119f,0.0000f),Vector3D(-3.3703f,-7.2807f,0.0000f),Vector3D(7.2778f,20.6873f,0.0000f),Vector3D(3.4419f,7.0933f,0.0000f),Vector3D(-9.8891f,25.5613f,0.0000f),Vector3D(1.3151f,-2.5681f,0.0000f),Vector3D(-2.3948f,7.4893f,0.0000f),Vector3D(-2.0694f,13.4967f,0.0000f),Vector3D(1.3962f,-6.9194f,0.0000f),Vector3D(-2.6588f,19.8782f,0.0000f)};
    Vector3D HideblushVectors[16] = {Vector3D(29.5887f,2.7041f,0.0000f),Vector3D(20.9418f,5.6785f,0.0000f),Vector3D(14.4566f,-8.1122f,0.0000f),Vector3D(21.7524f,-10.2754f,0.0000f),Vector3D(6.6203f,-5.9489f,0.0000f),Vector3D(12.2949f,6.4898f,0.0000f),Vector3D(-0.4053f,-4.5969f,0.0000f),Vector3D(4.4586f,7.8418f,0.0000f),Vector3D(-8.7820f,-4.3265f,0.0000f),Vector3D(-4.1884f,8.1122f,0.0000f),Vector3D(-16.6183f,-3.5153f,0.0000f),Vector3D(-12.8353f,8.9234f,0.0000f),Vector3D(-22.0227f,-2.7041f,0.0000f),Vector3D(-19.5907f,10.0050f,0.0000f),Vector3D(-26.6163f,10.2754f,0.0000f),Vector3D(-29.5887f,-1.8928f,0.0000f)};
    Vector3D SquintVectors[20] = {Vector3D(8.2810f,-24.0694f,0.0000f),Vector3D(3.4088f,-9.8051f,0.0000f),Vector3D(7.8975f,-20.0353f,0.0000f),Vector3D(9.7068f,-5.8228f,0.0000f),Vector3D(11.0072f,-12.1747f,0.0000f),Vector3D(2.2006f,-18.0527f,0.0000f),Vector3D(0.4077f,-7.6537f,0.0000f),Vector3D(-0.4459f,-3.8818f,0.0000f),Vector3D(-1.1743f,-17.3537f,0.0000f),Vector3D(-5.2182f,-24.3632f,0.0000f),Vector3D(-4.1398f,-24.9024f,0.0000f),Vector3D(-3.0614f,-20.3193f,0.0000f),Vector3D(1.7913f,-4.4132f,0.0000f),Vector3D(-0.8644f,-8.5745f,0.0000f),Vector3D(-0.4132f,-9.4238f,0.0000f),Vector3D(3.6784f,-20.8584f,0.0000f),Vector3D(21.3096f,-3.6944f,0.0000f),Vector3D(3.6784f,-12.7706f,0.0000f),Vector3D(3.1610f,-25.7418f,0.0000f),Vector3D(4.3666f,-3.7248f,0.0000f)};
    Vector3D SurprisedVectors[23] = {Vector3D(11.5161f,-25.6870f,0.0000f),Vector3D(-5.4878f,7.1794f,0.0000f),Vector3D(-4.4094f,-6.3004f,0.0000f),Vector3D(7.3583f,-16.2609f,0.0000f),Vector3D(9.7068f,-2.3181f,0.0000f),Vector3D(10.4680f,-8.6700f,0.0000f),Vector3D(5.7053f,-13.4696f,0.0000f),Vector3D(2.8340f,-4.9578f,0.0000f),Vector3D(-2.7918f,9.3361f,0.0000f),Vector3D(1.7913f,12.5712f,0.0000f),Vector3D(-0.0959f,-6.8395f,0.0000f),Vector3D(-0.3655f,11.4929f,0.0000f),Vector3D(2.0609f,6.9098f,0.0000f),Vector3D(3.0103f,5.5828f,0.0000f),Vector3D(0.9825f,-7.9179f,0.0000f),Vector3D(-6.5661f,6.3706f,0.0000f),Vector3D(0.6940f,-4.0580f,0.0000f),Vector3D(2.6001f,-0.3693f,0.0000f),Vector3D(-0.9047f,-3.6044f,0.0000f),Vector3D(0.9825f,12.0321f,0.0000f),Vector3D(5.2960f,3.9442f,0.0000f),Vector3D(8.0137f,-21.4283f,0.0000f),Vector3D(-3.0614f,-6.8395f,0.0000f)};
    Vector3D HappyVectors[20] = {Vector3D(1.9249f,6.5396f,0.0000f),Vector3D(2.8891f,15.2913f,0.0000f),Vector3D(0.1737f,-2.7956f,0.0000f),Vector3D(-0.6351f,14.7280f,0.0000f),Vector3D(3.5840f,5.3066f,0.0000f),Vector3D(3.2790f,1.8972f,0.0000f),Vector3D(-1.2099f,2.5908f,0.0000f),Vector3D(0.7129f,-4.6828f,0.0000f),Vector3D(-3.6006f,-8.1875f,0.0000f),Vector3D(-3.3310f,21.4679f,0.0000f),Vector3D(-8.7645f,-10.7835f,0.0000f),Vector3D(-9.3037f,-8.6267f,0.0000f),Vector3D(-0.6467f,19.5008f,0.0000f),Vector3D(3.9291f,5.9170f,0.0000f),Vector3D(-6.2966f,15.5368f,0.0000f),Vector3D(-0.0959f,-6.0308f,0.0000f),Vector3D(-13.7009f,11.3696f,0.0000f),Vector3D(-3.0614f,-5.7612f,0.0000f),Vector3D(3.4306f,1.4872f,0.0000f),Vector3D(-2.7918f,18.2327f,0.0000f)};
    Vector3D SadVectors[29] = {Vector3D(2.9608f,4.3238f,0.0000f),Vector3D(1.5412f,-47.7937f,0.0000f),Vector3D(6.3744f,13.9192f,0.0000f),Vector3D(4.2962f,-32.5940f,0.0000f),Vector3D(-1.3024f,-2.6201f,0.0000f),Vector3D(-19.1536f,-18.6519f,0.0000f),Vector3D(7.0108f,-10.9451f,0.0000f),Vector3D(8.5808f,-20.8017f,0.0000f),Vector3D(2.7398f,-26.6798f,0.0000f),Vector3D(0.9468f,-13.5848f,0.0000f),Vector3D(1.9804f,-8.4649f,0.0000f),Vector3D(4.6858f,-1.9952f,0.0000f),Vector3D(0.9825f,-3.0652f,0.0000f),Vector3D(-1.7135f,-5.7612f,0.0000f),Vector3D(2.3305f,18.7719f,0.0000f),Vector3D(-0.0959f,-7.3787f,0.0000f),Vector3D(-1.7135f,-3.3348f,0.0000f),Vector3D(-2.3816f,9.6267f,0.0000f),Vector3D(2.8696f,23.6246f,0.0000f),Vector3D(2.0419f,4.2994f,0.0000f),Vector3D(-4.6790f,21.1983f,0.0000f),Vector3D(-18.9272f,-29.0637f,0.0000f),Vector3D(-8.1433f,-4.4981f,0.0000f),Vector3D(0.4433f,-3.3348f,0.0000f),Vector3D(-2.9539f,5.4718f,0.0000f),Vector3D(9.2146f,13.5264f,0.0000f),Vector3D(3.1610f,-38.4127f,0.0000f),Vector3D(3.8274f,-7.2295f,0.0000f),Vector3D(5.0264f,16.8848f,0.0000f)};
    Vector3D TalkVectors[18] = {Vector3D(-22.5661f,-2.3127f,0.0000f),Vector3D(-25.1653f,0.4395f,0.0000f),Vector3D(-13.6190f,-3.3450f,0.0000f),Vector3D(-28.2964f,18.3951f,0.0000f),Vector3D(-13.6190f,-3.3450f,0.0000f),Vector3D(-22.3940f,-11.9480f,0.0000f),Vector3D(-35.5342f,8.4027f,0.0000f),Vector3D(-34.5317f,6.0327f,0.0000f),Vector3D(-22.5661f,-7.6465f,0.0000f),Vector3D(-22.5661f,-7.6465f,0.0000f),Vector3D(-22.5661f,-7.6465f,0.0000f),Vector3D(-27.4295f,15.1081f,0.0000f),Vector3D(-22.3940f,-11.9480f,0.0000f),Vector3D(-16.1674f,29.4026f,0.0000f),Vector3D(-8.7750f,-8.6029f,0.0000f),Vector3D(-22.5661f,-7.6465f,0.0000f),Vector3D(-36.1736f,10.1732f,0.0000f),Vector3D(-15.4962f,25.9510f,0.0000f)};
    Vector3D WhoopVectors[34] = {Vector3D(6.4589f,0.5687f,0.0000f),Vector3D(12.0661f,-26.0075f,0.0000f),Vector3D(1.9687f,-1.0130f,0.0000f),Vector3D(12.0408f,-19.2485f,0.0000f),Vector3D(10.0218f,-23.2458f,0.0000f),Vector3D(0.2706f,-3.6840f,0.0000f),Vector3D(1.8453f,-2.9799f,0.0000f),Vector3D(2.1880f,-5.3889f,0.0000f),Vector3D(2.7965f,15.5033f,0.0000f),Vector3D(4.0234f,-13.3630f,0.0000f),Vector3D(8.8880f,-17.7037f,0.0000f),Vector3D(11.6794f,-18.3193f,0.0000f),Vector3D(11.0079f,-10.0070f,0.0000f),Vector3D(3.8295f,-8.2516f,0.0000f),Vector3D(1.4233f,-7.2385f,0.0000f),Vector3D(-3.4339f,4.6594f,0.0000f),Vector3D(-0.8510f,9.4420f,0.0000f),Vector3D(13.7016f,-22.7641f,0.0000f),Vector3D(-1.7244f,6.0451f,0.0000f),Vector3D(1.3598f,3.4031f,0.0000f),Vector3D(-0.0201f,-1.7199f,0.0000f),Vector3D(4.7027f,-19.5936f,0.0000f),Vector3D(10.4393f,-0.7380f,0.0000f),Vector3D(22.3150f,-13.9867f,0.0000f),Vector3D(-2.8405f,-10.3573f,0.0000f),Vector3D(22.1559f,-3.8708f,0.0000f),Vector3D(0.9465f,-1.9759f,0.0000f),Vector3D(6.9698f,29.6463f,0.0000f),Vector3D(-0.6786f,9.7386f,0.0000f),Vector3D(1.2574f,0.9821f,0.0000f),Vector3D(12.0090f,-23.6898f,0.0000f),Vector3D(4.5064f,-9.7661f,0.0000f),Vector3D(2.2172f,-1.5463f,0.0000f),Vector3D(12.0409f,-22.5322f,0.0000f)};
    Vector3D Side1Vectors[6] = {Vector3D(-15.6437f,-24.2227f,0.0000f),Vector3D(95.3387f,83.5246f,0.0000f),Vector3D(-83.2365f,-55.1285f,0.0000f),Vector3D(9.3392f,6.8693f,0.0000f),Vector3D(16.0926f,-0.3404f,0.0000f),Vector3D(-81.6585f,-51.1199f,0.0000f)};
    Vector3D AngryVectors[25] = {Vector3D(7.7693f,-18.1663f,0.0000f),Vector3D(-11.9306f,-6.3283f,0.0000f),Vector3D(-5.7299f,-6.8675f,0.0000f),Vector3D(3.6114f,-11.1666f,0.0000f),Vector3D(0.5680f,-2.8853f,0.0000f),Vector3D(7.5299f,-3.5757f,0.0000f),Vector3D(1.4193f,-9.9929f,0.0000f),Vector3D(-2.5305f,-2.8290f,0.0000f),Vector3D(-12.2002f,-12.2594f,0.0000f),Vector3D(-7.6171f,-14.6858f,0.0000f),Vector3D(-2.2252f,-9.5635f,0.0000f),Vector3D(-8.9651f,-13.6074f,0.0000f),Vector3D(5.8626f,-6.8675f,0.0000f),Vector3D(-0.7366f,-7.1161f,0.0000f),Vector3D(-10.8522f,-10.3722f,0.0000f),Vector3D(-4.6516f,-5.5195f,0.0000f),Vector3D(2.8782f,-3.0076f,0.0000f),Vector3D(-3.3036f,-6.3283f,0.0000f),Vector3D(5.3234f,1.7595f,0.0000f),Vector3D(-6.3169f,-9.4518f,0.0000f),Vector3D(-4.1124f,-13.3378f,0.0000f),Vector3D(3.1667f,-10.6418f,0.0000f),Vector3D(2.9188f,-16.0644f,0.0000f),Vector3D(1.1589f,-1.3264f,0.0000f),Vector3D(-3.0340f,-8.4851f,0.0000f)};

    Morph morphs[12] = {
        Morph(16, NormalIndexes, NormalVectors),
        Morph(13, BlinkIndexes, BlinkVectors),
        Morph(18, BlushIndexes, BlushVectors),
        Morph(16, HideblushIndexes, HideblushVectors),
        Morph(20, SquintIndexes, SquintVectors),
        Morph(23, SurprisedIndexes, SurprisedVectors),
        Morph(20, HappyIndexes, HappyVectors),
        Morph(29, SadIndexes, SadVectors),
        Morph(18, TalkIndexes, TalkVectors),
        Morph(34, WhoopIndexes, WhoopVectors),
        Morph(6, Side1Indexes, Side1Vectors),
        Morph(25, AngryIndexes, AngryVectors)
    };

public:
    ProtoV2(){}

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
