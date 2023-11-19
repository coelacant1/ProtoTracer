#pragma once

#include "..\CameraManager.h"
#include "..\..\Camera.h"
#include "..\..\Pixels\PixelGroup.h"
#include "..\..\Pixels\PixelGroups\P3HUB75.h"
#include "..\..\Pixels\PixelGroups\DeltaDisplay.h"
#include "..\..\..\Utils\Math\Transform.h"

class HUB75DeltaCameraManager : public CameraManager {
private:
    CameraLayout cameraLayout;
    Transform camTransform;
    Transform camSideTransform;
    PixelGroup<2048> camPixels;
    PixelGroup<88> camSidePixels;
    Camera<2048> camMain;
    Camera<88> camSidePanels;

public:
    HUB75DeltaCameraManager() 
        : cameraLayout(CameraLayout::ZForward, CameraLayout::YUp),
          camTransform(Vector3D(), Vector3D(0, 0, -500.0f), Vector3D(1, 1, 1)),
          camSideTransform(Vector3D(), Vector3D(204.0f, 0, -500.0f), Vector3D(1, 1, 1)),
          camPixels(P3HUB75),
          camSidePixels(DeltaDisplay),
          camMain(&camTransform, &cameraLayout, &camPixels),
          camSidePanels(&camSideTransform, &cameraLayout, &camSidePixels),
          CameraManager(new CameraBase*[2]{ &camMain, &camSidePanels }, 2) {
    }
};
