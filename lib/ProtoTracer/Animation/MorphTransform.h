#pragma once

#include "IEasyEaseAnimator.h"
#include "../Utils/Math/Vector3D.h"

template<size_t maxMorphs>
class MorphTransform {
private:
    IEasyEaseAnimator* eEA;
    uint16_t dictionary[maxMorphs];
    uint16_t currentMorphs = 0;
    Vector3D positionOffsets[maxMorphs];
    Vector3D scaleOffsets[maxMorphs];
    Vector3D rotationOffsets[maxMorphs];

public:
    MorphTransform(IEasyEaseAnimator* eEA);

    void AddMorph(uint16_t dictionaryValue, Vector3D positionOffset);
    void AddMorph(uint16_t dictionaryValue, Vector3D positionOffset, Vector3D scaleOffset);
    void AddMorph(uint16_t dictionaryValue, Vector3D positionOffset, Vector3D scaleOffset, Vector3D rotationOffset);

    void SetMorphPositionOffset(uint16_t dictionaryValue, Vector3D positionOffset);
    void SetMorphScaleOffset(uint16_t dictionaryValue, Vector3D scaleOffset);
    void SetMorphRotationOffset(uint16_t dictionaryValue, Vector3D rotationOffset);

    Vector3D GetPositionOffset();
    Vector3D GetScaleOffset();
    Vector3D GetRotationOffset();
};

#include "MorphTransform.tpp"