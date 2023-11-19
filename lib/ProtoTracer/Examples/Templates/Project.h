#pragma once

#include "..\..\Engine\Engine.h"
#include "..\..\Scene\Scene.h"
#include "..\..\Camera\CameraManager\CameraManager.h"
#include "..\..\Controller\Controller.h"

class Project{
protected:
    long previousFrame;
    long previousAnimationTime;
    long previousRenderTime;
    long previousDisplayTime;
    float fade = 0.0f;
    float frameTime = 0.0f;
    float animationTime = 0.0f;
    float renderTime = 0.0f;
    float displayTime = 0.0f;
    
    CameraManager* cameras;
    Controller* controller;
    Scene scene;
    
    virtual void Update(float ratio) = 0;
    
    virtual uint8_t GetAccentBrightness() = 0;
    virtual uint8_t GetBrightness() = 0;

public:
    Project(CameraManager* cameras, Controller* controller, uint8_t numObjects) : cameras(cameras), controller(controller), scene(numObjects) {}

    float GetAnimationTime(){
        return animationTime;
    }

    float GetRenderTime(){
        return renderTime;
    }
    
    float GetDisplayTime(){
        return displayTime;
    }
    
    float GetFrameRate(){
        return 1.0f / frameTime;
    }

    virtual void Initialize() = 0;

    virtual void FadeIn(float stepRatio) = 0;
    virtual void FadeOut(float stepRatio) = 0;

    void Animate(float ratio){
        previousAnimationTime = micros();

        Update(ratio);

        animationTime = ((float)(micros() - previousAnimationTime)) / 1000000.0f;
    }

    void Render(){
        previousRenderTime = micros();

        RenderingEngine::Rasterize(&scene, cameras);
        //RenderingEngine::DisplayWhite(cameras);

        renderTime = ((float)(micros() - previousRenderTime)) / 1000000.0f;
    }

    void Display(){
        previousDisplayTime = micros();

        controller->SetAccentBrightness(GetAccentBrightness());
        controller->SetBrightness(GetBrightness());

        controller->Display();

        displayTime = ((float)(micros() - previousDisplayTime)) / 1000000.0f;
        
        frameTime = ((float)(micros() - previousFrame)) / 1000000.0f;
        previousFrame = micros();
    }
};
