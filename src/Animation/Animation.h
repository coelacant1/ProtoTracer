#pragma once

#include "..\Render\Scene.h"

class Animation{
protected:
    float fade = 0.0f;
    
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

    virtual void FadeIn(float stepRatio) = 0;
    virtual void FadeOut(float stepRatio) = 0;
    virtual void Update(float ratio) = 0;
};
