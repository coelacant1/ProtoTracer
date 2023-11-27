#pragma once

#include <Arduino.h>
#include "..\..\Engine\Engine.h"
#include "..\..\Scene\Scene.h"
#include "..\..\Camera\CameraManager\CameraManager.h"
#include "..\..\Controller\Controller.h"

class Project {
protected:
    CameraManager* cameras;
    Controller* controller;
    Scene scene;

    long previousAnimationTime = 0;
    long previousRenderTime = 0;
    long previousDisplayTime = 0;
    float fade = 0.0f;
    float animationTime = 0.0f;
    float renderTime = 0.0f;
    float displayTime = 0.0f;

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
