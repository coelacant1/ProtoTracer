#include "Engine.h"

void RenderingEngine::Rasterize(Scene* scene, CameraManager* cameraManager) {
    for (int i = 0; i < cameraManager->GetCameraCount(); i++) {
        Rasterizer::Rasterize(scene, cameraManager->GetCameras()[i]);

        if (scene->UseEffect()) {
            scene->GetEffect()->ApplyEffect(cameraManager->GetCameras()[i]->GetPixelGroup());
        }
    }
}

void RenderingEngine::DisplayWhite(CameraManager* cameraManager) {
    for (int i = 0; i < cameraManager->GetCameraCount(); i++) {
        DisplayTest::FillWhite(cameraManager->GetCameras()[i]);
    }
}
