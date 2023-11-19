#pragma once

#include "..\Camera\CameraManager\CameraManager.h"
#include "..\Scene\Scene.h"
#include "..\Renderer\Rasterizer\Rasterizer.h"

class RenderingEngine {
public:
    static void Render(Scene* scene, CameraManager* cameraManager);
    
};
