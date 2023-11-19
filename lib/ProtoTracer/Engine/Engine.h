#pragma once

#include "..\Camera\CameraManager\CameraManager.h"
#include "..\Scene\Scene.h"
#include "..\Renderer\Rasterizer\Rasterizer.h"
#include "..\Renderer\DisplayTest\DisplayTest.h"

class RenderingEngine {
public:
    static void Rasterize(Scene* scene, CameraManager* cameraManager);
    
    static void DisplayWhite(CameraManager* cameraManager);
};
