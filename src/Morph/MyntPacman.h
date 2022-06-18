#pragma once

#include "Arduino.h"
#include "..\Math\Rotation.h"
#include "Morph.h"
#include "..\Materials\SimpleMaterial.h"
#include "..\Render\IndexGroup.h"
#include "..\Render\Object3D.h"

class MyntPacman{
public:
    enum Morphs {
        MouthClosed
    };

private:
    Vector3D basisVertices[31] = {Vector3D(140.0694f,41.1122f,7.2577f),Vector3D(139.5453f,46.4337f,7.2577f),Vector3D(137.9930f,51.5507f,7.2577f),Vector3D(135.4724f,56.2666f,7.2577f),Vector3D(132.0801f,60.4001f,7.2577f),Vector3D(127.9466f,63.7923f,7.2577f),Vector3D(123.2308f,66.3130f,7.2577f),Vector3D(118.1137f,67.8653f,7.2577f),Vector3D(112.7922f,68.3894f,7.2577f),Vector3D(107.4707f,67.8653f,7.2577f),Vector3D(102.3537f,66.3130f,7.2577f),Vector3D(97.6379f,63.7924f,7.2577f),Vector3D(93.5044f,60.4001f,7.2577f),Vector3D(90.1121f,56.2666f,7.2577f),Vector3D(87.5914f,51.5507f,7.2577f),Vector3D(112.3228f,41.1770f,7.2577f),Vector3D(112.3228f,41.1756f,7.2577f),Vector3D(87.5914f,30.6737f,7.2577f),Vector3D(90.1121f,25.9578f,7.2577f),Vector3D(93.5044f,21.8243f,7.2577f),Vector3D(97.6378f,18.4321f,7.2577f),Vector3D(102.3537f,15.9114f,7.2577f),Vector3D(107.4707f,14.3592f,7.2577f),Vector3D(112.7922f,13.8350f,7.2577f),Vector3D(118.1137f,14.3592f,7.2577f),Vector3D(123.2308f,15.9114f,7.2577f),Vector3D(127.9466f,18.4321f,7.2577f),Vector3D(132.0801f,21.8243f,7.2577f),Vector3D(135.4724f,25.9578f,7.2577f),Vector3D(137.9931f,30.6737f,7.2577f),Vector3D(139.5453f,35.7907f,7.2577f)};
    IndexGroup basisIndexes[28] = {IndexGroup(12,13,16),IndexGroup(13,14,16),IndexGroup(16,11,12),IndexGroup(16,10,11),IndexGroup(16,9,10),IndexGroup(16,8,9),IndexGroup(16,7,8),IndexGroup(16,6,7),IndexGroup(16,5,6),IndexGroup(16,4,5),IndexGroup(16,3,4),IndexGroup(2,3,16),IndexGroup(1,2,16),IndexGroup(0,1,16),IndexGroup(30,0,16),IndexGroup(29,30,16),IndexGroup(28,29,16),IndexGroup(27,28,16),IndexGroup(26,27,16),IndexGroup(25,26,16),IndexGroup(24,25,16),IndexGroup(23,24,16),IndexGroup(22,23,16),IndexGroup(21,22,16),IndexGroup(20,21,16),IndexGroup(19,20,16),IndexGroup(18,19,16),IndexGroup(17,18,16)};
    TriangleGroup triangleGroup = TriangleGroup(&basisVertices[0], &basisIndexes[0], 31, 28);
    SimpleMaterial simpleMaterial = SimpleMaterial(RGBColor(128, 128, 128));
    Object3D basisObj = Object3D(&triangleGroup, &simpleMaterial);

    static const byte morphCount = 1;
    int MouthClosedIndexes[4] = {13,14,17,18};

    Vector3D MouthClosedVectors[4] = {Vector3D(-2.3078f,-3.3848f,0.0000f),Vector3D(-2.3078f,-10.1544f,0.0000f),Vector3D(-2.1540f,10.7699f,0.0000f),Vector3D(-2.6155f,4.4618f,0.0000f)};

    Morph morphs[1] = {
        Morph(4, MouthClosedIndexes, MouthClosedVectors)
    };

public:
    MyntPacman(){}

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
