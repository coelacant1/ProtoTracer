#pragma once

#include "KeyFrame.h"
#include "..\Utils\Math\Mathematics.h"
#include "..\Physics\Utils\DampedSpring.h"
#include "..\Utils\Filter\RampFilter.h"

class IEasyEaseAnimator {
public:
    enum InterpolationMethod{
        Cosine,
        Bounce,
        Linear,
        Overshoot
    };

    virtual void SetConstants(uint16_t dictionaryValue, float springConstant, float damping) = 0;

    virtual float GetValue(uint16_t dictionaryValue) = 0;
    virtual float GetTarget(uint16_t dictionaryValue) = 0;

    virtual void AddParameter(float* parameter, uint16_t dictionaryValue, uint16_t frames, float basis, float goal) = 0;
    virtual void AddParameterFrame(uint16_t dictionaryValue, float value) = 0;
    virtual void SetInterpolationMethod(uint16_t dictionaryValue, InterpolationMethod interpMethod) = 0;
    virtual void Reset() = 0;
    virtual void SetParameters() = 0;
    virtual void Update() = 0;
};
