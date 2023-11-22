#pragma once

#include <Arduino.h>
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

    void RenderStartTimer(){
        previousRenderTime = micros();
    }
 
    void RenderEndTimer(){
        renderTime = ((float)(micros() - previousRenderTime)) / 1000000.0f;
    }

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

        controller->Display();

        displayTime = ((float)(micros() - previousDisplayTime)) / 1000000.0f;
        
        frameTime = ((float)(micros() - previousFrame)) / 1000000.0f;
        previousFrame = micros();
    }
};
