#pragma once

#include "..\CameraManager.h"
#include "..\..\Camera.h"
#include "..\..\Pixels\PixelGroup.h"
#include "..\..\Pixels\PixelGroups\P3HUB75.h"
#include "..\..\..\Utils\Math\Transform.h"

class DualP3HUB75CameraManager : public CameraManager {
private:
    CameraLayout cameraLayout;
    Transform camTransform1;
    Transform camTransform2;
    PixelGroup<2048> camPixelsLeft;
    PixelGroup<2048> camPixelsRight;
    Camera<2048> camLeft;
    Camera<2048> camRight;

public:
    DualP3HUB75CameraManager() 
        : cameraLayout(CameraLayout::ZForward, CameraLayout::YUp),
          camTransform1(Vector3D(), Vector3D(0, 0.0f, -500.0f), Vector3D(1, 1, 1)),
          camTransform2(Vector3D(), Vector3D(0, 0.0f, -500.0f), Vector3D(1, 1, 1)),
          camPixelsLeft(P3HUB75),
          camPixelsRight(P3HUB75),
          camLeft(&camTransform1, &cameraLayout, &camPixelsLeft),
          camRight(&camTransform2, &cameraLayout, &camPixelsRight),
          CameraManager(new CameraBase*[2]{ &camLeft, &camRight }, 2) {
    }

};
