#pragma once

#include "Arduino.h"
#include "..\Math\Rotation.h"
#include "Morph.h"

class MorphExample{
public:
    enum Morphs {
        Neutral,
        Angry,
        Happy
    };

private:
    //Create basis object to morph from
    Vector3D basisVertices[8] = {Vector3D(0, 0, 0), Vector3D(0, 0, 0), Vector3D(0, 0, 0), Vector3D(0, 0, 0), Vector3D(0, 0, 0), Vector3D(0, 0, 0), Vector3D(0, 0, 0), Vector3D(0, 0, 0)};
    Vector3D basisIndexes[6] = {Vector3D(0, 0, 0), Vector3D(0, 0, 0), Vector3D(0, 0, 0), Vector3D(0, 0, 0), Vector3D(0, 0, 0), Vector3D(0, 0, 0)};

    Object3D basisObj = Object3D(8, 6, basisVertices, basisIndexes);

    //Create morph objects that reference some but not all 
    static const byte morphCount = 3;
    int neutralIndexes[6] = {0, 1, 2, 3, 4, 5};
    int angryIndexes[6]   = {0, 1, 2, 3, 4, 5};
    int happyIndexes[6]   = {0, 1, 2, 3, 4, 5};

    Vector3D neutralVectors[6] = {Vector3D(0, 0, 0), Vector3D(0, 0, 0), Vector3D(0, 0, 0), Vector3D(0, 0, 0), Vector3D(0, 0, 0), Vector3D(0, 0, 0)};
    Vector3D angryVectors[6]   = {Vector3D(0, 0, 0), Vector3D(0, 0, 0), Vector3D(0, 0, 0), Vector3D(0, 0, 0), Vector3D(0, 0, 0), Vector3D(0, 0, 0)};
    Vector3D happyVectors[6]   = {Vector3D(0, 0, 0), Vector3D(0, 0, 0), Vector3D(0, 0, 0), Vector3D(0, 0, 0), Vector3D(0, 0, 0), Vector3D(0, 0, 0)};

    Morph morphs[morphCount] = {
        Morph(6, neutralIndexes, neutralVectors),
        Morph(6, angryIndexes, angryVectors),
        Morph(6, happyIndexes, happyVectors)
    };

    //Set rotation and position
    Quaternion offsetRotation = Rotation(EulerAngles(Vector3D(7, 0, 0), EulerConstants::EulerOrderXYZR)).GetQuaternion();
    Vector3D offsetPosition = Vector3D(-110, 70, 0);
    
public:
    MorphExample(){}

    Object3D* GetObject(){
        return &basisObj;
    }

    void SetMorphWeight(Morphs morph, float weight){
        weight = Mathematics::Constrain(weight, 0.0f, 1.0f);
        
        morphs[morph].SetWeight(weight);
    }

    void Update(){
        basisObj.ResetVertices();

        for(int i = 0; i < morphCount; i++){
            if(morphs[i].GetWeight() > 0.0f){
                morphs[i].MorphObject3D(&basisObj);
            }
        }

        basisObj.Rotate(offsetRotation);
        basisObj.MoveRelative(offsetPosition);
    }
};
