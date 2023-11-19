#pragma once

#include "Arduino.h"
#include "..\..\Math\Rotation.h"
#include "..\Morph.h"
#include "..\..\Materials\SimpleMaterial.h"
#include "..\..\Render\IndexGroup.h"
#include "..\..\Render\Object3D.h"

class TamamoSec{
public:
    enum Morphs {
        H,
        L
    };

private:
    Vector3D basisVertices[77] = {Vector3D(-9.9328f,0.0000f,-17.0066f),Vector3D(-1.3247f,0.0000f,-15.4148f),Vector3D(-25.7534f,0.0000f,-10.4534f),Vector3D(10.8492f,0.0000f,-3.2409f),Vector3D(-32.3069f,0.0000f,5.3674f),Vector3D(10.8492f,0.0000f,13.9757f),Vector3D(-25.7534f,0.0000f,21.1882f),Vector3D(-1.3247f,0.0000f,26.1497f),Vector3D(-9.9328f,0.0000f,27.7414f),Vector3D(-18.5410f,0.0000f,26.1497f),Vector3D(5.8876f,0.0000f,21.1882f),Vector3D(-30.7150f,0.0000f,13.9757f),Vector3D(12.4412f,0.0000f,5.3674f),Vector3D(-30.7150f,0.0000f,-3.2409f),Vector3D(5.8876f,0.0000f,-10.4534f),Vector3D(-18.5410f,0.0000f,-15.4148f),Vector3D(-7.9609f,0.0000f,-23.9313f),Vector3D(19.6629f,0.0000f,5.0704f),Vector3D(19.0995f,0.0000f,-0.6455f),Vector3D(17.4329f,0.0000f,-6.1417f),Vector3D(14.7255f,0.0000f,-11.2071f),Vector3D(11.0810f,0.0000f,-15.6469f),Vector3D(6.6417f,0.0000f,-19.2904f),Vector3D(1.5765f,0.0000f,-21.9980f),Vector3D(-3.9197f,0.0000f,-23.6651f),Vector3D(-11.2431f,0.0000f,-27.7019f),Vector3D(22.8395f,0.0000f,1.3582f),Vector3D(22.5007f,0.0000f,-1.0841f),Vector3D(20.6194f,0.0000f,-7.2876f),Vector3D(17.5637f,0.0000f,-13.0050f),Vector3D(13.4502f,0.0000f,-18.0161f),Vector3D(8.4396f,0.0000f,-22.1286f),Vector3D(2.7225f,0.0000f,-25.1847f),Vector3D(-4.6689f,0.0000f,-27.2148f),Vector3D(46.5290f,0.0000f,-8.9082f),Vector3D(35.3922f,0.0000f,-32.5182f),Vector3D(39.1044f,0.0000f,-27.1725f),Vector3D(26.3134f,0.0000f,-9.5486f),Vector3D(22.7474f,0.0000f,-16.2203f),Vector3D(17.9473f,0.0000f,-22.0679f),Vector3D(44.4501f,0.0000f,-3.4141f),Vector3D(47.2714f,0.0000f,-3.4141f),Vector3D(47.5684f,0.0000f,1.3376f),Vector3D(47.5684f,0.0000f,5.4954f),Vector3D(42.2227f,0.0000f,-21.3814f),Vector3D(44.8956f,0.0000f,-15.2933f),Vector3D(28.6455f,0.0000f,-11.1489f),Vector3D(24.8396f,0.0000f,-18.2695f),Vector3D(20.0135f,0.0000f,-23.9165f),Vector3D(44.7471f,0.0000f,1.6346f),Vector3D(-8.1156f,0.0000f,-19.4510f),Vector3D(-11.3823f,0.0000f,-19.4510f),Vector3D(28.7101f,0.0000f,-37.7153f),Vector3D(21.5826f,0.0000f,-30.4393f),Vector3D(24.4039f,0.0000f,-28.0635f),Vector3D(27.5222f,0.0000f,-24.3512f),Vector3D(30.1950f,0.0000f,-20.6390f),Vector3D(32.5709f,0.0000f,-16.3327f),Vector3D(34.5012f,0.0000f,-11.7295f),Vector3D(35.6891f,0.0000f,-6.8293f),Vector3D(29.8980f,0.0000f,-6.6808f),Vector3D(27.2252f,0.0000f,-3.8595f),Vector3D(38.9559f,0.0000f,-4.1565f),Vector3D(43.5591f,0.0000f,-8.9082f),Vector3D(42.0743f,0.0000f,-14.2539f),Vector3D(39.9953f,0.0000f,-19.8965f),Vector3D(36.8771f,0.0000f,-25.0936f),Vector3D(33.1648f,0.0000f,-30.1424f),Vector3D(29.3040f,0.0000f,-33.4091f),Vector3D(26.1858f,0.0000f,-30.1424f),Vector3D(29.7495f,0.0000f,-26.1331f),Vector3D(32.2739f,0.0000f,-22.5693f),Vector3D(34.9467f,0.0000f,-18.1146f),Vector3D(37.0255f,0.0000f,-12.4720f),Vector3D(38.3620f,0.0000f,-7.7203f),Vector3D(32.5709f,0.0000f,-30.5878f),Vector3D(34.6497f,0.0000f,-33.1121f)};
    IndexGroup basisIndexes[71] = {IndexGroup(13,4,2),IndexGroup(4,11,2),IndexGroup(15,2,11),IndexGroup(11,6,15),IndexGroup(15,6,0),IndexGroup(6,9,0),IndexGroup(0,9,1),IndexGroup(1,9,8),IndexGroup(14,1,8),IndexGroup(14,8,7),IndexGroup(3,14,7),IndexGroup(10,3,7),IndexGroup(10,12,3),IndexGroup(10,5,12),IndexGroup(25,51,50),IndexGroup(25,50,16),IndexGroup(16,33,25),IndexGroup(33,16,24),IndexGroup(32,33,24),IndexGroup(24,23,32),IndexGroup(32,23,31),IndexGroup(23,22,31),IndexGroup(31,22,30),IndexGroup(22,21,30),IndexGroup(30,21,29),IndexGroup(21,20,29),IndexGroup(29,20,28),IndexGroup(20,19,28),IndexGroup(28,19,27),IndexGroup(19,18,27),IndexGroup(27,18,26),IndexGroup(18,17,26),IndexGroup(43,26,17),IndexGroup(26,43,49),IndexGroup(43,42,49),IndexGroup(49,42,40),IndexGroup(42,41,40),IndexGroup(40,41,63),IndexGroup(41,34,63),IndexGroup(45,63,34),IndexGroup(63,45,64),IndexGroup(45,44,64),IndexGroup(64,44,65),IndexGroup(44,36,65),IndexGroup(65,36,66),IndexGroup(36,76,66),IndexGroup(66,76,75),IndexGroup(67,68,35),IndexGroup(52,35,68),IndexGroup(53,52,68),IndexGroup(68,69,53),IndexGroup(53,69,54),IndexGroup(69,70,54),IndexGroup(54,70,55),IndexGroup(70,71,55),IndexGroup(55,71,56),IndexGroup(71,72,56),IndexGroup(56,72,57),IndexGroup(72,73,57),IndexGroup(57,73,58),IndexGroup(73,74,58),IndexGroup(58,74,59),IndexGroup(74,62,59),IndexGroup(62,61,59),IndexGroup(59,61,60),IndexGroup(61,37,60),IndexGroup(60,37,46),IndexGroup(37,38,46),IndexGroup(46,38,47),IndexGroup(38,39,47),IndexGroup(48,47,39)};
    TriangleGroup triangleGroup = TriangleGroup(&basisVertices[0], &basisIndexes[0], 77, 71);
    SimpleMaterial simpleMaterial = SimpleMaterial(RGBColor(128, 128, 128));
    Object3D basisObj = Object3D(&triangleGroup, &simpleMaterial);

    static const byte morphCount = 2;
    int HIndexes[77] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76};
    int LIndexes[77] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76};

    Vector3D HVectors[77] = {Vector3D(-8.6025f,0.0000f,23.7484f),Vector3D(-19.1169f,0.0000f,15.1098f),Vector3D(17.8493f,0.0000f,26.7294f),Vector3D(-26.5251f,0.0000f,-10.6074f),Vector3D(38.6621f,0.0000f,10.1331f),Vector3D(-13.5788f,0.0000f,-34.0306f),Vector3D(41.6428f,0.0000f,-16.3192f),Vector3D(12.1384f,0.0000f,-41.4389f),Vector3D(25.0467f,0.0000f,-37.1315f),Vector3D(35.5612f,0.0000f,-28.4928f),Vector3D(-1.4049f,0.0000f,-40.1123f),Vector3D(42.9695f,0.0000f,-2.7756f),Vector3D(-22.2178f,0.0000f,-23.5161f),Vector3D(30.0232f,0.0000f,20.6477f),Vector3D(-25.1984f,0.0000f,2.9363f),Vector3D(4.3059f,0.0000f,28.0559f),Vector3D(-11.2626f,0.0000f,6.7526f),Vector3D(-4.1661f,0.0000f,15.9514f),Vector3D(0.2269f,0.0000f,17.7167f),Vector3D(6.9618f,0.0000f,14.3114f),Vector3D(6.2490f,0.0000f,1.4898f),Vector3D(1.6132f,0.0000f,-4.1744f),Vector3D(-3.1915f,0.0000f,-5.0005f),Vector3D(-7.6743f,0.0000f,-2.5532f),Vector3D(-9.3634f,0.0000f,1.7930f),Vector3D(-9.9782f,0.0000f,8.0350f),Vector3D(-12.4453f,0.0000f,18.4562f),Vector3D(-3.6446f,0.0000f,12.4741f),Vector3D(5.1613f,0.0000f,1.2582f),Vector3D(5.8264f,0.0000f,-0.4102f),Vector3D(1.6003f,0.0000f,-5.1062f),Vector3D(-3.5273f,0.0000f,-5.4982f),Vector3D(-9.6408f,0.0000f,-2.5477f),Vector3D(-10.1835f,0.0000f,2.5358f),Vector3D(-65.0250f,0.0000f,29.3694f),Vector3D(25.3970f,0.0000f,10.9517f),Vector3D(-67.8785f,0.0000f,29.8187f),Vector3D(-1.7717f,0.0000f,-10.2180f),Vector3D(7.3292f,0.0000f,8.4624f),Vector3D(13.7515f,0.0000f,29.1255f),Vector3D(-54.9612f,0.0000f,24.7540f),Vector3D(-59.3538f,0.0000f,27.6872f),Vector3D(-52.4964f,0.0000f,24.9070f),Vector3D(-42.0297f,0.0000f,20.2340f),Vector3D(-69.0298f,0.0000f,31.1827f),Vector3D(-68.1073f,0.0000f,31.3786f),Vector3D(-1.2572f,0.0000f,-9.7208f),Vector3D(8.3374f,0.0000f,9.8957f),Vector3D(14.5911f,0.0000f,30.2592f),Vector3D(-45.4157f,0.0000f,21.3541f),Vector3D(-14.5694f,0.0000f,8.2895f),Vector3D(-14.8459f,0.0000f,7.1770f),Vector3D(26.3516f,0.0000f,18.6971f),Vector3D(30.8892f,0.0000f,12.7031f),Vector3D(24.6294f,0.0000f,11.6581f),Vector3D(25.4440f,0.0000f,24.1535f),Vector3D(11.3110f,0.0000f,24.8445f),Vector3D(5.6089f,0.0000f,4.4649f),Vector3D(-1.1144f,0.0000f,-10.7387f),Vector3D(-11.7454f,0.0000f,-25.9647f),Vector3D(-10.5861f,0.0000f,-22.6344f),Vector3D(-12.0554f,0.0000f,-24.7928f),Vector3D(-15.4037f,0.0000f,-33.1766f),Vector3D(-59.9822f,0.0000f,27.1750f),Vector3D(-62.6532f,0.0000f,28.3451f),Vector3D(-63.8842f,0.0000f,28.3196f),Vector3D(-62.1958f,0.0000f,27.7559f),Vector3D(26.1871f,0.0000f,4.9996f),Vector3D(14.9811f,0.0000f,14.9132f),Vector3D(19.5672f,0.0000f,15.3509f),Vector3D(19.3608f,0.0000f,23.9391f),Vector3D(11.5741f,0.0000f,22.5729f),Vector3D(6.2681f,0.0000f,5.2154f),Vector3D(-1.4395f,0.0000f,-11.7933f),Vector3D(-11.9961f,0.0000f,-26.9126f),Vector3D(-57.7142f,0.0000f,26.2318f),Vector3D(-63.1590f,0.0000f,28.0454f)};
    Vector3D LVectors[77] = {Vector3D(5.5720f,0.0000f,19.5242f),Vector3D(-4.3198f,0.0000f,9.2730f),Vector3D(32.7190f,0.0000f,25.8140f),Vector3D(-8.9220f,0.0000f,-18.3631f),Vector3D(56.3634f,0.0000f,11.0660f),Vector3D(7.3655f,0.0000f,-41.1590f),Vector3D(62.6531f,0.0000f,-16.0817f),Vector3D(35.0016f,0.0000f,-45.7612f),Vector3D(47.9051f,0.0000f,-39.7253f),Vector3D(57.7970f,0.0000f,-29.4741f),Vector3D(20.7583f,0.0000f,-46.0151f),Vector3D(62.3993f,0.0000f,-1.8379f),Vector3D(-2.8861f,0.0000f,-31.2671f),Vector3D(46.1119f,0.0000f,20.9580f),Vector3D(-9.1758f,0.0000f,-4.1194f),Vector3D(18.4756f,0.0000f,25.5601f),Vector3D(-0.5642f,0.0000f,31.8859f),Vector3D(-10.3875f,0.0000f,-35.1834f),Vector3D(-15.0490f,0.0000f,-27.0823f),Vector3D(-18.0418f,0.0000f,-18.2282f),Vector3D(-19.2491f,0.0000f,-8.9599f),Vector3D(-18.6238f,0.0000f,0.3664f),Vector3D(-16.1928f,0.0000f,9.3905f),Vector3D(-12.0476f,0.0000f,17.7674f),Vector3D(-6.3474f,0.0000f,25.1743f),Vector3D(-1.3280f,0.0000f,33.8629f),Vector3D(-18.1055f,0.0000f,-33.2734f),Vector3D(-19.9673f,0.0000f,-29.7191f),Vector3D(-23.3452f,0.0000f,-19.7254f),Vector3D(-24.7079f,0.0000f,-9.2644f),Vector3D(-24.0021f,0.0000f,1.2622f),Vector3D(-21.2583f,0.0000f,11.4476f),Vector3D(-16.5796f,0.0000f,20.9026f),Vector3D(-8.7134f,0.0000f,30.5832f),Vector3D(-16.2946f,0.0000f,-19.8439f),Vector3D(-60.3472f,0.0000f,39.2680f),Vector3D(2.4330f,0.0000f,14.9560f),Vector3D(-22.3811f,0.0000f,-29.8504f),Vector3D(-9.3083f,0.0000f,-25.5804f),Vector3D(5.3806f,0.0000f,-19.4445f),Vector3D(-18.2083f,0.0000f,-30.8230f),Vector3D(-21.7849f,0.0000f,-27.6362f),Vector3D(-27.1355f,0.0000f,-33.5564f),Vector3D(-32.7502f,0.0000f,-37.4531f),Vector3D(-5.0284f,0.0000f,0.3379f),Vector3D(-11.1005f,0.0000f,-10.3662f),Vector3D(-23.3772f,0.0000f,-25.5793f),Vector3D(-10.9447f,0.0000f,-20.6738f),Vector3D(2.8576f,0.0000f,-14.6948f),Vector3D(-28.5386f,0.0000f,-37.1813f),Vector3D(-19.4802f,0.0000f,34.4713f),Vector3D(-17.1412f,0.0000f,31.2238f),Vector3D(-45.5546f,0.0000f,41.3684f),Vector3D(-39.4354f,0.0000f,28.8014f),Vector3D(-42.2222f,0.0000f,22.7372f),Vector3D(-44.4647f,0.0000f,14.2566f),Vector3D(-45.9781f,0.0000f,6.1193f),Vector3D(-46.5474f,0.0000f,-2.7613f),Vector3D(-46.1585f,0.0000f,-11.7845f),Vector3D(-44.3254f,0.0000f,-20.7216f),Vector3D(-32.6693f,0.0000f,-26.3123f),Vector3D(-32.3352f,0.0000f,-31.0379f),Vector3D(-47.6124f,0.0000f,-27.6153f),Vector3D(-11.3030f,0.0000f,-22.5687f),Vector3D(-5.4048f,0.0000f,-13.2866f),Vector3D(0.7389f,0.0000f,-2.4062f),Vector3D(6.5579f,0.0000f,8.1170f),Vector3D(-58.9300f,0.0000f,33.8696f),Vector3D(-49.4975f,0.0000f,34.9083f),Vector3D(-46.7416f,0.0000f,24.7665f),Vector3D(-49.4845f,0.0000f,15.4563f),Vector3D(-50.8692f,0.0000f,7.6766f),Vector3D(-51.8101f,0.0000f,-1.6760f),Vector3D(-50.8631f,0.0000f,-12.5153f),Vector3D(-49.3875f,0.0000f,-21.3238f),Vector3D(29.7615f,0.0000f,7.0723f),Vector3D(29.3907f,0.0000f,12.7243f)};

    Morph morphs[2] = {
        Morph(77, HIndexes, HVectors),
        Morph(77, LIndexes, LVectors)
    };

public:
    TamamoSec(){}

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
