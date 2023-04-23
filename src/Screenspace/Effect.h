#pragma once

#include "..\Render\IPixelGroup.h"

class Effect {
protected:
    float ratio = 0.0f;

public:
    Effect(){}

    void SetRatio(float ratio){
        this->ratio = Mathematics::Constrain(ratio, 0.0f, 1.0f);
    }

    virtual void ApplyEffect(IPixelGroup* pixelGroup) = 0;

};
