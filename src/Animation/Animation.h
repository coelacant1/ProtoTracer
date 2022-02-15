#pragma once

#include "Arduino.h"
#include "..\Render\Scene.h"

class Animation{
protected:
    long previousTime;
    float fade = 0.0f;
    float animationTime = 0.0f;
    
    Scene* scene;

    Animation(int numObjects){
        scene = new Scene(numObjects);
    }

public:
    Scene* GetScene(){
        return scene;
    }

    ~Animation(){
        delete scene;
    }

    float GetAnimationTime(){
        return animationTime;
    }

    virtual void FadeIn(float stepRatio) = 0;
    virtual void FadeOut(float stepRatio) = 0;
    virtual void Update(float ratio) = 0;

    void UpdateTime(float ratio){
        previousTime = micros();

        Update(ratio);

        animationTime = ((float)(micros() - previousTime)) / 1000000.0f;
    }
};
