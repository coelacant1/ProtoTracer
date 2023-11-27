#pragma once

#include "KeyFrame.h"
#include "..\Utils\Math\Mathematics.h"

class KeyFrameInterpolation{
public:
    enum InterpolationMethod{
        Linear,
        Cosine,
        Step
    };
};

template<size_t maxParameters, size_t maxKeyFrames>
class KeyFrameTrack : public KeyFrameInterpolation{
private:
    InterpolationMethod interpMethod;
    float* parameters[maxParameters];
    KeyFrame keyFrames[maxKeyFrames];
    float min = 0.0f;
    float max = 0.0f;
    float startFrameTime = Mathematics::FLTMAX;//initialize to out of bounds
    float stopFrameTime = Mathematics::FLTMIN;//initialize to out of bounds
    uint8_t currentFrames = 0;
    uint8_t currentParameters = 0;
    bool isActive = true;
    float parameterValue = 0.0f;
    float currentTime = 0.0f;
    float timeOffset = 0.0f;

    void ShiftKeyFrameArray(int position);

public:
    KeyFrameTrack(float min, float max, InterpolationMethod interpMethod);

    float GetCurrentTime();

    void SetCurrentTime(float setTime);
    void Pause();
    void Play();
    void AddParameter(float* parameter);
    void AddKeyFrame(float time, float value);

    float GetParameterValue();

    void Reset();

    float Update();

};

#include "KeyFrameTrack.tpp"