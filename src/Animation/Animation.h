#pragma once

#include "..\Render\Scene.h"
#include "Arduino.h"

template <size_t numObjects>
class Animation {
protected:
    long previousTime;
    float fade = 0.0f;
    float animationTime = 0.0f;

    Scene scene = Scene(numObjects);

public:
    Animation() {}

    Scene *GetScene() {
        return &scene;
    }

    float GetAnimationTime() {
        return animationTime;
    }

    virtual void FadeIn(float stepRatio) = 0;
    virtual void FadeOut(float stepRatio) = 0;
    virtual void Update(float ratio) = 0;

    void UpdateTime(float ratio) {
        previousTime = micros();

        Update(ratio);

        animationTime = ((float)(micros() - previousTime)) / 1000000.0f;
    }
};
