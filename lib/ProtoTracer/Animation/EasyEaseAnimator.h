#pragma once

#include "IEasyEaseAnimator.h"

template<size_t maxParameters>
class EasyEaseAnimator : public IEasyEaseAnimator {
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

    void SetConstants(uint16_t dictionaryValue, float springConstant, float damping) override;

    float GetValue(uint16_t dictionaryValue) override;
    float GetTarget(uint16_t dictionaryValue) override;

    void AddParameter(float* parameter, uint16_t dictionaryValue, uint16_t frames, float basis, float goal) override;
    void AddParameterFrame(uint16_t dictionaryValue, float value) override;
    void SetInterpolationMethod(uint16_t dictionaryValue, InterpolationMethod interpMethod) override;
    void Reset() override;
    void SetParameters() override;
    void Update() override;
};

#include "EasyEaseAnimator.tpp"
