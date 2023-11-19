#pragma once

#include "..\CameraManager.h"
#include "..\..\Camera.h"
#include "..\..\Pixels\PixelGroup.h"
#include "..\..\Pixels\PixelGroups\P3HUB75.h"
#include "..\..\..\Utils\Math\Transform.h"

class HUB75DeltaCameraManager : public CameraManager {
private:
    CameraLayout cameraLayout;
    Transform camTransform;
    PixelGroup<2048> camPixels;
    Camera<2048> camMain;

public:
    HUB75DeltaCameraManager() 
        : cameraLayout(CameraLayout::ZForward, CameraLayout::YUp),
          camTransform(Vector3D(), Vector3D(0, 0, -500.0f), Vector3D(1, 1, 1)),
          camPixels(P3HUB75),
          camMain(&camTransform, &cameraLayout, &camPixels),
          CameraManager(new CameraBase*[1]{ &camMain }, 1) {
    }
};
