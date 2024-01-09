#pragma once

#include "..\CameraManager.h"
#include "..\..\Camera.h"
#include "..\..\Pixels\PixelGroup.h"
//#include "..\..\Pixels\PixelGroups\P3HUB75.h"
#include "..\..\Pixels\PixelGroups\DeltaDisplayL.h"
#include "..\..\Pixels\PixelGroups\DeltaDisplayR.h"
#include "..\..\..\Utils\Math\Transform.h"

class HUB75DeltaCameraManager : public CameraManager {
private:
    CameraLayout cameraLayout = CameraLayout(CameraLayout::ZForward, CameraLayout::YUp);
    Transform camTransform = Transform(Vector3D(), Vector3D(0, 0, -500.0f), Vector3D(1, 1, 1));
    Transform camSideTransformL = Transform(Vector3D(), Vector3D(204.0f, 0, -500.0f), Vector3D(1, 1, 1));
    Transform camSideTransformR = Transform(Vector3D(0, 0, 0), Vector3D(204.0f, 0, -500.0f), Vector3D(1, 1, 1));
    PixelGroup<2048> camPixels = PixelGroup<2048>(Vector2D(192.0f, 96.0f), Vector2D(0.0f, 0.0f), 64);
    PixelGroup<88> camSidePixelsL = PixelGroup<88>(DeltaDisplayL);
    PixelGroup<88> camSidePixelsR = PixelGroup<88>(DeltaDisplayR);
    Camera<2048> camMain = Camera<2048>(&camTransform, &cameraLayout, &camPixels);
    Camera<88> camSidePanelsL = Camera<88>(&camSideTransformL, &cameraLayout, &camSidePixelsL);
    Camera<88> camSidePanelsR = Camera<88>(&camSideTransformR, &cameraLayout, &camSidePixelsR);

public:
    HUB75DeltaCameraManager() : CameraManager(new CameraBase*[3]{ &camMain, &camSidePanelsL, &camSidePanelsR }, 3) {}
};
