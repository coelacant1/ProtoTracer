#pragma once

#include "..\Render\PixelGroup.h"

class Effect {
protected:
    float ratio = 0.0f;

public:
    Effect(){}

    void SetRatio(float ratio){
        this->ratio = ratio;
    }

    virtual void ApplyEffect(PixelGroup* pixelGroup) = 0;

};
