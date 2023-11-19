#pragma once

#include "Arduino.h"
#include "..\Math\Rotation.h"
#include "Morph.h"
#include "..\Materials\SimpleMaterial.h"
#include "..\Render\IndexGroup.h"
#include "..\Render\Object3D.h"

class MyntZZZ{
public:
    enum Morphs {
        Smaller
    };

private:
    Vector3D basisVertices[30] = {Vector3D(151.2468f,42.6423f,7.4699f),Vector3D(151.2468f,46.8521f,7.4699f),Vector3D(123.8793f,42.8864f,7.4699f),Vector3D(123.7943f,46.3871f,7.4699f),Vector3D(123.3252f,66.0901f,7.4699f),Vector3D(123.3252f,70.2999f,7.4699f),Vector3D(151.3907f,66.0901f,7.4699f),Vector3D(151.3907f,70.2999f,7.4699f),Vector3D(112.5601f,69.2070f,7.4699f),Vector3D(112.5601f,64.9972f,7.4699f),Vector3D(84.4946f,69.2070f,7.4699f),Vector3D(84.4946f,64.9972f,7.4699f),Vector3D(84.9638f,45.2942f,7.4699f),Vector3D(85.0487f,41.7934f,7.4699f),Vector3D(112.4162f,45.7592f,7.4699f),Vector3D(112.4162f,41.5494f,7.4699f),Vector3D(89.8847f,45.1961f,7.4697f),Vector3D(107.7378f,64.6697f,7.4697f),Vector3D(128.7152f,46.2890f,7.4697f),Vector3D(146.5684f,65.7626f,7.4697f),Vector3D(132.3522f,73.6411f,7.4699f),Vector3D(132.3522f,77.8509f,7.4699f),Vector3D(104.9847f,73.8851f,7.4699f),Vector3D(104.8998f,77.3859f,7.4699f),Vector3D(104.4306f,97.0889f,7.4699f),Vector3D(104.4306f,101.2987f,7.4699f),Vector3D(132.4961f,97.0889f,7.4699f),Vector3D(132.4961f,101.2987f,7.4699f),Vector3D(109.8207f,77.2878f,7.4697f),Vector3D(127.6738f,96.7614f,7.4697f)};
    IndexGroup basisIndexes[24] = {IndexGroup(6,7,19),IndexGroup(7,5,19),IndexGroup(5,4,19),IndexGroup(10,11,17),IndexGroup(8,10,17),IndexGroup(9,8,17),IndexGroup(17,12,9),IndexGroup(9,12,16),IndexGroup(12,13,16),IndexGroup(15,16,14),IndexGroup(13,16,15),IndexGroup(19,3,6),IndexGroup(6,3,18),IndexGroup(3,2,18),IndexGroup(0,18,1),IndexGroup(2,18,0),IndexGroup(26,27,29),IndexGroup(27,25,29),IndexGroup(25,24,29),IndexGroup(29,23,26),IndexGroup(26,23,28),IndexGroup(23,22,28),IndexGroup(20,28,21),IndexGroup(22,28,20)};
    TriangleGroup triangleGroup = TriangleGroup(&basisVertices[0], &basisIndexes[0], 30, 24);
    SimpleMaterial simpleMaterial = SimpleMaterial(RGBColor(128, 128, 128));
    Object3D basisObj = Object3D(&triangleGroup, &simpleMaterial);

    static const byte morphCount = 1;
    int SmallerIndexes[30] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29};

    Vector3D SmallerVectors[30] = {Vector3D(-1.6226f,1.6178f,0.0000f),Vector3D(-1.6226f,1.1213f,0.0000f),Vector3D(1.6050f,1.5890f,0.0000f),Vector3D(1.6150f,1.1761f,0.0000f),Vector3D(1.6703f,-1.1475f,0.0000f),Vector3D(1.6703f,-1.6440f,0.0000f),Vector3D(-1.6396f,-1.1475f,0.0000f),Vector3D(-1.6396f,-1.6440f,0.0000f),Vector3D(-1.3958f,-1.3996f,0.0000f),Vector3D(-1.3958f,-0.9769f,0.0000f),Vector3D(1.4220f,-1.3996f,0.0000f),Vector3D(1.4220f,-0.9769f,0.0000f),Vector3D(1.3749f,1.0013f,0.0000f),Vector3D(1.3664f,1.3528f,0.0000f),Vector3D(-1.3814f,0.9546f,0.0000f),Vector3D(-1.3814f,1.3773f,0.0000f),Vector3D(0.8808f,1.0112f,0.0000f),Vector3D(-0.9117f,-0.9441f,0.0000f),Vector3D(1.0346f,1.1877f,0.0000f),Vector3D(-1.0708f,-1.1089f,0.0000f),Vector3D(-1.3092f,1.3054f,0.0000f),Vector3D(-1.3092f,0.9048f,0.0000f),Vector3D(1.2950f,1.2821f,0.0000f),Vector3D(1.3031f,0.9490f,0.0000f),Vector3D(1.3477f,-0.9259f,0.0000f),Vector3D(1.3477f,-1.3265f,0.0000f),Vector3D(-1.3229f,-0.9259f,0.0000f),Vector3D(-1.3229f,-1.3265f,0.0000f),Vector3D(0.8348f,0.9583f,0.0000f),Vector3D(-0.8640f,-0.8947f,0.0000f)};

    Morph morphs[1] = {
        Morph(30, SmallerIndexes, SmallerVectors)
    };

public:
    MyntZZZ(){}

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
