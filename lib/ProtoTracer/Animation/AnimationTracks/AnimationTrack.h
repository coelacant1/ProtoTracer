#pragma once

#include "..\KeyFrameTrack.h"

template<size_t maxParameters, size_t maxKeyFrames>
class AnimationTrack{
protected:
    KeyFrameTrack<maxParameters, maxKeyFrames> track;

private:
    virtual void AddKeyFrames() = 0;

public:
    AnimationTrack();
    AnimationTrack(float min, float max, KeyFrameInterpolation::InterpolationMethod interpMethod);

    void Play();
    void Pause();
    void RestartTime();
    void PrintTime();
    void Reset();
    float GetParameterValue();
    float Update();
    void AddParameter(float* parameter);
};

#include "AnimationTrack.tpp"