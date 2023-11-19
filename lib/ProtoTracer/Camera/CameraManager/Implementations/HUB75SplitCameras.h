#pragma once

#include "..\CameraManager.h"
#include "..\..\Camera.h"
#include "..\..\Pixels\PixelGroup.h"
#include "..\..\Pixels\PixelGroups\P3HUB75.h"
#include "..\..\..\Utils\Math\Transform.h"

class DualP3HUB75CameraManager : public CameraManager {
private:
    CameraLayout cameraLayout = CameraLayout(CameraLayout::ZForward, CameraLayout::YUp);
    Transform camTransform1 = Transform(Vector3D(), Vector3D(0, 0.0f, -500.0f), Vector3D(1, 1, 1));
    Transform camTransform2 = Transform(Vector3D(), Vector3D(0, 0.0f, -500.0f), Vector3D(1, 1, 1));
    PixelGroup<2048> camPixelsLeft = PixelGroup<2048>(P3HUB75);
    PixelGroup<2048> camPixelsRight = PixelGroup<2048>(P3HUB75);
    Camera<2048> camLeft = Camera<2048>(&camTransform1, &cameraLayout, &camPixelsLeft);
    Camera<2048> camRight = Camera<2048>(&camTransform2, &cameraLayout, &camPixelsRight);

public:
    DualP3HUB75CameraManager() : CameraManager(new CameraBase*[2]{ &camLeft, &camRight }, 2) {}
};
