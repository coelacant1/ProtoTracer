#pragma once

#include "..\CameraManager.h"
#include "..\..\Camera.h"
#include "..\..\Pixels\PixelGroup.h"
#include "..\..\Pixels\PixelGroups\WS35Pixels.h"
#include "..\..\..\Utils\Math\Transform.h"

class WS35SplitCameraManager : public CameraManager {
private:
    CameraLayout cameraLayout = CameraLayout(CameraLayout::ZForward, CameraLayout::YUp);
    Transform camRghtTransform = Transform(Vector3D(), Vector3D(0, 0, -500.0f), Vector3D(1, 1, 1));
    Transform camLeftTransform = Transform(Vector3D(), Vector3D(0, 0, -500.0f), Vector3D(1, 1, 1));
    PixelGroup<571> camRghtPixels = PixelGroup<571>(WS35Pixels, IPixelGroup::ZEROTOMAX);
    PixelGroup<571> camLeftPixels = PixelGroup<571>(WS35Pixels, IPixelGroup::MAXTOZERO);
    Camera<571> camRght = Camera<571>(&camRghtTransform, &cameraLayout, &camRghtPixels);
    Camera<571> camLeft = Camera<571>(&camLeftTransform, &cameraLayout, &camLeftPixels);

public:
    WS35SplitCameraManager() : CameraManager(new CameraBase*[2]{ &camRght, &camLeft }, 2) {}
};
