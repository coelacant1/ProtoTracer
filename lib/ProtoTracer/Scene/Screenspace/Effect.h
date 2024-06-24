#pragma once

#include "../../Camera/Pixels/IPixelGroup.h"
#include "../../Utils/Math/Mathematics.h"

class Effect {
protected:
    float ratio = 0.0f;

public:
    Effect();

    void SetRatio(float ratio);

    virtual void ApplyEffect(IPixelGroup* pixelGroup) = 0;

};
