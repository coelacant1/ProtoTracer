#include "Project.h"

Project::Project(CameraManager* cameras, Controller* controller, uint8_t numObjects) 
    : cameras(cameras), controller(controller), scene(numObjects) {
        
    previousAnimationTime = micros();
    previousRenderTime = micros();
    previousDisplayTime = micros();
}

void Project::RenderStartTimer() {
    previousRenderTime = micros();
}

void Project::RenderEndTimer() {
    renderTime = ((float)(micros() - previousRenderTime)) / 1000000.0f;
}

float Project::GetAnimationTime() {
    return animationTime;
}

float Project::GetRenderTime() {
    return renderTime;
}

float Project::GetDisplayTime() {
    return displayTime;
}

float Project::GetFrameRate() {
    return avgFPS.Filter(1.0f / (renderTime + animationTime + displayTime));
}

void Project::Animate(float ratio) {
    previousAnimationTime = micros();

    Update(ratio);

    animationTime = ((float)(micros() - previousAnimationTime)) / 1000000.0f;
}

void Project::Render() {
    previousRenderTime = micros();

    RenderingEngine::Rasterize(&scene, cameras);
    //RenderingEngine::DisplayWhite(cameras);

    renderTime = ((float)(micros() - previousRenderTime)) / 1000000.0f;
}

void Project::Display() {
    previousDisplayTime = micros();

    controller->Display();

    displayTime = ((float)(micros() - previousDisplayTime)) / 1000000.0f;
}
