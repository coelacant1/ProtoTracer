#pragma once

#include "../CameraManager.h"
#include "../../Camera.h"
#include "../../Pixels/PixelGroup.h"
#include "../../Pixels/PixelGroups/WS35Pixels.h"
#include "../../../Utils/Math/Transform.h"

class WS35BetaCameraManager : public CameraManager {
private:
    CameraLayout cameraLayout = CameraLayout(CameraLayout::ZForward, CameraLayout::YUp);
    Transform camFTransform = Transform(Vector3D(), Vector3D(0, 0, -500.0f), Vector3D(1, 1, 1));
    //Transform camRTransform = Transform(Vector3D(0.0f, 0.0f, 0.0f), Vector3D(0.0f, 0.0f, -500.0f), Vector3D(1, 1, 1));
    Transform camRTransform = Transform(Vector3D(0.0f, 0.0f, -156.0f), Vector3D(383.36f, 222.97f, -500.0f), Vector3D(1, 1, 1));
    PixelGroup<571> camFPixels = PixelGroup<571>(WS35Pixels, IPixelGroup::ZEROTOMAX);
    PixelGroup<571> camRPixels = PixelGroup<571>(WS35Pixels, IPixelGroup::ZEROTOMAX);
    Camera<571> camF = Camera<571>(&camFTransform, &cameraLayout, &camFPixels);
    Camera<571> camR = Camera<571>(&camRTransform, &cameraLayout, &camRPixels);

public:
    WS35BetaCameraManager() : CameraManager(new CameraBase*[2]{ &camF, &camR }, 2) {}
};
