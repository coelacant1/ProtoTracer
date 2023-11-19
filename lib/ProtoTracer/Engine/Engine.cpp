#include "RenderingEngine.h"

void RenderingEngine::Render(Scene* scene, CameraManager* cameraManager) {
    for (int i = 0; i < cameraManager->GetCameraCount(); i++) {
        Rasterizer::Rasterize(scene, cameraManager->GetCameras()[i])

        if (scene->UseEffect()) {
            scene->GetEffect()->ApplyEffect(cameraManager->GetCameras()[i]->GetPixelGroup());
        }
    }
}
