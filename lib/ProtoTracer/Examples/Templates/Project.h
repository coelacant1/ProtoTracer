#pragma once

#include "..\..\Engine\Engine.h"
#include "..\..\Scene\Scene.h"
#include "..\..\Camera\CameraManager\CameraManager.h"
#include "..\..\Controller\Controller.h"

class Project{
protected:
    long previousTime;
    float fade = 0.0f;
    float animationTime = 0.0f;
    
    Scene scene;
    CameraManager* cameras;
    Controller* controller;
    
    void UpdateController(){
        controller->SetAccentBrightness(GetAccentBrightness() * 25 + 5);
        controller->SetBrightness(GetBrightness() * 25 + 5);

        controller->Display();
    }

public:
    Project(CameraManager* cameras, Controller* controller, uint8_t numObjects) : cameras(cameras), controller(controller), scene(numObjects) {}

    float GetAnimationTime(){
        return animationTime;
    }

    void Render(){
        RenderingEngine::Render(&scene, cameras);
    }


    virtual void Initialize() = 0;
    
    virtual uint8_t GetAccentBrightness() = 0;
    virtual uint8_t GetBrightness() = 0;
    virtual void FadeIn(float stepRatio) = 0;
    virtual void FadeOut(float stepRatio) = 0;
    virtual void Update(float ratio) = 0;

    void UpdateTime(float ratio){
        previousTime = micros();

        Update(ratio);

        animationTime = ((float)(micros() - previousTime)) / 1000000.0f;
    }
};
