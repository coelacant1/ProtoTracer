#pragma once

#include "Arduino.h"
#include "..\Math\Rotation.h"
#include "Morph.h"
#include "..\Materials\SimpleMaterial.h"
#include "..\Render\IndexGroup.h"
#include "..\Render\Object3D.h"

class MyntFood{
public:
    enum Morphs {
        Move
    };

private:
    Vector3D basisVertices[24] = {Vector3D(87.7171f,40.3649f,7.2577f),Vector3D(91.1713f,36.9106f,7.2577f),Vector3D(94.6255f,40.3649f,7.2577f),Vector3D(91.1713f,43.8191f,7.2577f),Vector3D(67.9357f,40.1817f,7.2577f),Vector3D(71.3899f,36.7275f,7.2577f),Vector3D(74.8441f,40.1817f,7.2577f),Vector3D(71.3899f,43.6359f,7.2577f),Vector3D(47.7880f,40.1817f,7.2577f),Vector3D(51.2422f,36.7275f,7.2577f),Vector3D(54.6964f,40.1817f,7.2577f),Vector3D(51.2422f,43.6359f,7.2577f),Vector3D(28.0066f,40.1817f,7.2577f),Vector3D(31.4608f,36.7275f,7.2577f),Vector3D(34.9150f,40.1817f,7.2577f),Vector3D(31.4608f,43.6359f,7.2577f),Vector3D(7.8589f,40.3649f,7.2577f),Vector3D(11.3131f,36.9106f,7.2577f),Vector3D(14.7673f,40.3649f,7.2577f),Vector3D(11.3131f,43.8191f,7.2577f),Vector3D(-11.9225f,40.3649f,7.2577f),Vector3D(-8.4683f,36.9106f,7.2577f),Vector3D(-5.0141f,40.3649f,7.2577f),Vector3D(-8.4683f,43.8191f,7.2577f)};
    IndexGroup basisIndexes[12] = {IndexGroup(3,0,2),IndexGroup(7,6,4),IndexGroup(11,10,8),IndexGroup(15,12,14),IndexGroup(19,16,18),IndexGroup(23,22,20),IndexGroup(2,0,1),IndexGroup(4,6,5),IndexGroup(8,10,9),IndexGroup(14,12,13),IndexGroup(18,16,17),IndexGroup(20,22,21)};
    TriangleGroup triangleGroup = TriangleGroup(&basisVertices[0], &basisIndexes[0], 24, 12);
    SimpleMaterial simpleMaterial = SimpleMaterial(RGBColor(128, 128, 128));
    Object3D basisObj = Object3D(&triangleGroup, &simpleMaterial);

    static const byte morphCount = 1;
    int MoveIndexes[24] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23};

    Vector3D MoveVectors[24] = {Vector3D(19.9356f,0.0000f,0.0000f),Vector3D(19.9356f,0.0000f,0.0000f),Vector3D(19.9356f,0.0000f,0.0000f),Vector3D(19.9356f,0.0000f,0.0000f),Vector3D(19.9356f,0.0000f,0.0000f),Vector3D(19.9356f,0.0000f,0.0000f),Vector3D(19.9356f,0.0000f,0.0000f),Vector3D(19.9356f,0.0000f,0.0000f),Vector3D(19.9356f,0.0000f,0.0000f),Vector3D(19.9356f,0.0000f,0.0000f),Vector3D(19.9356f,0.0000f,0.0000f),Vector3D(19.9356f,0.0000f,0.0000f),Vector3D(19.9356f,0.0000f,0.0000f),Vector3D(19.9356f,0.0000f,0.0000f),Vector3D(19.9356f,0.0000f,0.0000f),Vector3D(19.9356f,0.0000f,0.0000f),Vector3D(19.9356f,0.0000f,0.0000f),Vector3D(19.9356f,0.0000f,0.0000f),Vector3D(19.9356f,0.0000f,0.0000f),Vector3D(19.9356f,0.0000f,0.0000f),Vector3D(19.9356f,0.0000f,0.0000f),Vector3D(19.9356f,0.0000f,0.0000f),Vector3D(19.9356f,0.0000f,0.0000f),Vector3D(19.9356f,0.0000f,0.0000f)};

    Morph morphs[1] = {
        Morph(24, MoveIndexes, MoveVectors)
    };

public:
    MyntFood(){}

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
