#pragma once

#include "Utils/Morph.h"
#include "../../../Utils/Math/Rotation.h"
#include "../../../Scene/Materials/Static/SimpleMaterial.h"
#include "../../../Scene/Objects/Object3D.h"
#include "../../../Renderer/Utils/IndexGroup.h"

class Standby{
public:
    Vector3D* basisVertices = new Vector3D[88] {Vector3D(-178.2653f,0.0000f,-178.6021f),Vector3D(-177.8523f,0.0000f,-168.4787f),Vector3D(-168.6849f,0.0000f,-163.0079f),Vector3D(-155.5253f,0.0000f,-166.2608f),Vector3D(-156.0469f,0.0000f,-173.3787f),Vector3D(-164.3969f,0.0000f,-184.1520f),Vector3D(-160.9961f,0.0000f,-186.5178f),Vector3D(-158.1868f,0.0000f,-181.3426f),Vector3D(-150.3501f,0.0000f,-178.3854f),Vector3D(-152.7159f,0.0000f,-187.5528f),Vector3D(-165.5798f,0.0000f,-193.1715f),Vector3D(-172.8250f,0.0000f,-189.1793f),Vector3D(-172.1432f,0.0000f,-182.9650f),Vector3D(-162.7705f,0.0000f,-170.2531f),Vector3D(-168.0935f,0.0000f,-168.9223f),Vector3D(-170.6071f,0.0000f,-171.7317f),Vector3D(-170.6071f,0.0000f,-175.8718f),Vector3D(-146.9493f,0.0000f,-177.7940f),Vector3D(-143.6964f,0.0000f,-184.0041f),Vector3D(-118.8557f,0.0000f,-172.6188f),Vector3D(-121.2215f,0.0000f,-166.8523f),Vector3D(-130.5368f,0.0000f,-169.8095f),Vector3D(-139.7616f,0.0000f,-149.5156f),Vector3D(-147.8365f,0.0000f,-153.1012f),Vector3D(-139.1127f,0.0000f,-174.0974f),Vector3D(-129.7975f,0.0000f,-145.5603f),Vector3D(-108.0619f,0.0000f,-167.0001f),Vector3D(-98.5988f,0.0000f,-162.8600f),Vector3D(-101.2603f,0.0000f,-131.6614f),Vector3D(-109.6884f,0.0000f,-135.6536f),Vector3D(-106.5833f,0.0000f,-158.5720f),Vector3D(-113.5328f,0.0000f,-149.9961f),Vector3D(-105.9918f,0.0000f,-146.7432f),Vector3D(-107.7662f,0.0000f,-139.6458f),Vector3D(-118.5600f,0.0000f,-145.4124f),Vector3D(-121.5172f,0.0000f,-141.5680f),Vector3D(-98.5988f,0.0000f,-130.3306f),Vector3D(-85.7349f,0.0000f,-157.5370f),Vector3D(-78.0461f,0.0000f,-153.5448f),Vector3D(-75.0889f,0.0000f,-134.1750f),Vector3D(-69.1745f,0.0000f,-148.8132f),Vector3D(-60.8942f,0.0000f,-145.2646f),Vector3D(-73.1667f,0.0000f,-119.2410f),Vector3D(-80.2640f,0.0000f,-122.1982f),Vector3D(-84.4041f,0.0000f,-141.7159f),Vector3D(-90.4664f,0.0000f,-126.7819f),Vector3D(-67.6958f,0.0000f,-116.1359f),Vector3D(-55.1277f,0.0000f,-142.8988f),Vector3D(-39.1587f,0.0000f,-134.7664f),Vector3D(-35.1664f,0.0000f,-124.8597f),Vector3D(-42.1159f,0.0000f,-111.5523f),Vector3D(-52.0226f,0.0000f,-109.1865f),Vector3D(-67.6958f,0.0000f,-116.1359f),Vector3D(-56.4584f,0.0000f,-119.0932f),Vector3D(-51.4311f,0.0000f,-115.5445f),Vector3D(-47.8825f,0.0000f,-117.0231f),Vector3D(-43.8902f,0.0000f,-125.4512f),Vector3D(-45.3689f,0.0000f,-130.7742f),Vector3D(-49.6568f,0.0000f,-132.4006f),Vector3D(-56.4584f,0.0000f,-119.0932f),Vector3D(-38.7151f,0.0000f,-102.5327f),Vector3D(-28.3648f,0.0000f,-104.3071f),Vector3D(-20.8239f,0.0000f,-119.8325f),Vector3D(-15.6488f,0.0000f,-117.4667f),Vector3D(-14.6138f,0.0000f,-113.9180f),Vector3D(-18.0146f,0.0000f,-112.5873f),Vector3D(-24.0769f,0.0000f,-115.5445f),Vector3D(-26.4426f,0.0000f,-110.8129f),Vector3D(-19.7889f,0.0000f,-106.9686f),Vector3D(-18.6060f,0.0000f,-103.2720f),Vector3D(-22.3025f,0.0000f,-101.6456f),Vector3D(-28.3648f,0.0000f,-104.3071f),Vector3D(-38.7151f,0.0000f,-102.5327f),Vector3D(-20.3803f,0.0000f,-94.5482f),Vector3D(-10.6215f,0.0000f,-98.6883f),Vector3D(-13.4309f,0.0000f,-107.1164f),Vector3D(-6.1857f,0.0000f,-110.9608f),Vector3D(-9.2908f,0.0000f,-120.7196f),Vector3D(-26.1469f,0.0000f,-128.8520f),Vector3D(0.0245f,0.0000f,-116.8752f),Vector3D(2.8338f,0.0000f,-96.4704f),Vector3D(-1.8977f,0.0000f,-85.8244f),Vector3D(5.9389f,0.0000f,-81.6843f),Vector3D(11.1141f,0.0000f,-92.6260f),Vector3D(27.5266f,0.0000f,-102.9763f),Vector3D(19.5421f,0.0000f,-107.1164f),Vector3D(10.0790f,0.0000f,-100.9063f),Vector3D(9.0440f,0.0000f,-113.0309f)};
    IndexGroup* basisIndexes = new IndexGroup[74] {IndexGroup(80,87,79),IndexGroup(87,80,86),IndexGroup(80,84,86),IndexGroup(85,86,84),IndexGroup(84,80,83),IndexGroup(83,80,82),IndexGroup(80,81,82),IndexGroup(61,78,60),IndexGroup(62,78,61),IndexGroup(78,62,77),IndexGroup(62,63,77),IndexGroup(77,63,76),IndexGroup(63,64,76),IndexGroup(76,64,75),IndexGroup(64,65,75),IndexGroup(68,75,65),IndexGroup(66,68,65),IndexGroup(67,68,66),IndexGroup(69,75,68),IndexGroup(75,69,74),IndexGroup(74,69,73),IndexGroup(69,70,73),IndexGroup(73,70,72),IndexGroup(70,71,72),IndexGroup(53,54,52),IndexGroup(52,54,51),IndexGroup(54,55,51),IndexGroup(51,55,50),IndexGroup(50,55,49),IndexGroup(55,56,49),IndexGroup(49,56,48),IndexGroup(56,57,48),IndexGroup(48,57,47),IndexGroup(57,58,47),IndexGroup(47,58,46),IndexGroup(58,59,46),IndexGroup(41,42,40),IndexGroup(40,42,39),IndexGroup(42,43,39),IndexGroup(39,43,38),IndexGroup(43,44,38),IndexGroup(38,44,37),IndexGroup(37,44,36),IndexGroup(44,45,36),IndexGroup(28,29,27),IndexGroup(29,30,27),IndexGroup(27,30,26),IndexGroup(26,30,25),IndexGroup(30,31,25),IndexGroup(34,25,31),IndexGroup(35,25,34),IndexGroup(34,31,33),IndexGroup(31,32,33),IndexGroup(23,24,22),IndexGroup(22,24,21),IndexGroup(18,21,24),IndexGroup(18,24,17),IndexGroup(18,19,21),IndexGroup(20,21,19),IndexGroup(7,8,6),IndexGroup(8,9,6),IndexGroup(10,6,9),IndexGroup(11,6,10),IndexGroup(6,11,5),IndexGroup(11,12,5),IndexGroup(5,12,4),IndexGroup(12,13,4),IndexGroup(4,13,3),IndexGroup(3,13,2),IndexGroup(13,14,2),IndexGroup(2,14,1),IndexGroup(14,15,1),IndexGroup(1,15,0),IndexGroup(15,16,0)};
    StaticTriangleGroup<88,74> triangleGroup = StaticTriangleGroup<88,74>(&basisVertices[0], &basisIndexes[0]);
    TriangleGroup<88,74> triangleGroupMemory = TriangleGroup<88,74>(&triangleGroup);
    SimpleMaterial simpleMaterial = SimpleMaterial(RGBColor(128, 128, 128));
    Object3D basisObj = Object3D(&triangleGroup, &triangleGroupMemory, &simpleMaterial);

    static const uint8_t morphCount = 0;

public:
    Standby(){}

    Object3D* GetObject(){
        return &basisObj;
    }

    void Update(){
        basisObj.ResetVertices();
    }
};
