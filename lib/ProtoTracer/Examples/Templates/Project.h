#pragma once

#include <Arduino.h>
#include "..\..\Engine\Engine.h"
#include "..\..\Scene\Scene.h"
#include "..\..\Camera\CameraManager\CameraManager.h"
#include "..\..\Controller\Controller.h"

class Project {
protected:
    long previousFrame;
    long previousAnimationTime;
    long previousRenderTime;
    long previousDisplayTime;
    float fade;
    float frameTime;
    float animationTime;
    float renderTime;
    float displayTime;

    CameraManager* cameras;
    Controller* controller;
    Scene scene;

    virtual void Update(float ratio) = 0;

    void RenderStartTimer();
    void RenderEndTimer();

public:
    Project(CameraManager* cameras, Controller* controller, uint8_t numObjects);

    float GetAnimationTime();
    float GetRenderTime();
    float GetDisplayTime();
    float GetFrameRate();

    virtual void Initialize() = 0;

    void Animate(float ratio);
    void Render();
    void Display();
};
