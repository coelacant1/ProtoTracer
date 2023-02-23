#pragma once

#include "..\Render\IPixelGroup.h"

class Effect {
protected:
    float ratio = 0.0f;

public:
    Effect(){}

    void SetRatio(float ratio){
        this->ratio = ratio;
    }

    virtual void ApplyEffect(IPixelGroup* pixelGroup) = 0;

};
