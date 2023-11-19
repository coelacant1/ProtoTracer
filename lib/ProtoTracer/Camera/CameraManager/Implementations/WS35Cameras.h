#pragma once

#include "..\CameraManager.h"
#include "..\..\Camera.h"
#include "..\..\Pixels\PixelGroup.h"
#include "..\..\Pixels\PixelGroups\WS35Pixels.h"
#include "..\..\..\Utils\Math\Transform.h"

class WS35CameraManager : public CameraManager {
private:
    CameraLayout cameraLayout = CameraLayout(CameraLayout::ZForward, CameraLayout::YUp);
    Transform camTransform = Transform(Vector3D(), Vector3D(0, 0, -500.0f), Vector3D(1, 1, 1));
    PixelGroup<571> camPixels = PixelGroup<571>(WS35Pixels, IPixelGroup::ZEROTOMAX);
    Camera<571> cam = Camera<571>(&camTransform, &cameraLayout, &camPixels);

public:
    WS35CameraManager() : CameraManager(new CameraBase*[1]{ &cam }, 1) {}
};
