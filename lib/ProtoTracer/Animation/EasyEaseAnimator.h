#pragma once

#include "KeyFrame.h"
#include "..\Utils\Math\Mathematics.h"
#include "..\Physics\Utils\DampedSpring.h"
#include "..\Utils\Filter\RampFilter.h"

class EasyEaseInterpolation{
public:
    enum InterpolationMethod{
        Cosine,
        Bounce,
        Linear,
        Overshoot
    };
};

template<size_t maxParameters>
class EasyEaseAnimator : public EasyEaseInterpolation{
private:
    InterpolationMethod interpMethod;
    DampedSpring dampedSpring[maxParameters];
    RampFilter rampFilter[maxParameters];
    float* parameters[maxParameters];
    float parameterFrame[maxParameters];
    float previousSet[maxParameters];
    float basis[maxParameters];
    float goal[maxParameters];
    uint8_t interpolationMethods[maxParameters];
    uint16_t dictionary[maxParameters];
    uint16_t currentParameters = 0;
    bool isActive = true;

public:
    EasyEaseAnimator(InterpolationMethod interpMethod, float springConstant = 1.0f, float dampingConstant = 0.5f);

    void SetConstants(uint16_t dictionaryValue, float springConstant, float damping);

    float GetValue(uint16_t dictionaryValue);
    float GetTarget(uint16_t dictionaryValue);

    void AddParameter(float* parameter, uint16_t dictionaryValue, uint16_t frames, float basis, float goal);
    void AddParameterFrame(uint16_t dictionaryValue, float value);
    void SetInterpolationMethod(uint16_t dictionaryValue, InterpolationMethod interpMethod);
    void Reset();
    void SetParameters();
    void Update();
};

#include "EasyEaseAnimator.tpp"
