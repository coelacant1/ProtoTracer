#pragma once

#include "..\CameraManager.h"
#include "..\..\Camera.h"
#include "..\..\Pixels\PixelGroup.h"
#include "..\..\Pixels\PixelGroups\P3HUB75.h"
#include "..\..\..\Utils\Math\Transform.h"

class HUB75DeltaCameraManager : public CameraManager {
private:
    CameraLayout cameraLayout = CameraLayout(CameraLayout::ZForward, CameraLayout::YUp);
    Transform camTransform = Transform(Vector3D(), Vector3D(0, 0, -500.0f), Vector3D(1, 1, 1));
    PixelGroup<2048> camPixels = PixelGroup<2048>(P3HUB75);
    Camera<2048> camMain = Camera<2048>(&camTransform, &cameraLayout, &camPixels);

public:
    HUB75DeltaCameraManager() : CameraManager(new CameraBase*[1]{ &camMain }, 1) {}
};
