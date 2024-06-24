#pragma once

#include "../CameraManager.h"
#include "../../Camera.h"
#include "../../Pixels/PixelGroup.h"
#include "../../Pixels/PixelGroups/DeltaDisplayFursuitL.h"
#include "../../Pixels/PixelGroups/DeltaDisplayFursuitR.h"
#include "../../../Utils/Math/Transform.h"

class APA102CamerasV1 : public CameraManager {
private:
    CameraLayout cameraLayout = CameraLayout(CameraLayout::ZForward, CameraLayout::YUp);
    Transform camSideTransformL = Transform(Vector3D(0, 0, 0), Vector3D(0.0f, 0, -500.0f), Vector3D(1, 1, 1));
    Transform camSideTransformR = Transform(Vector3D(0, 0, 0), Vector3D(0.0f, 0, -500.0f), Vector3D(1, 1, 1));
    PixelGroup<88> camSidePixelsL = PixelGroup<88>(DeltaDisplayFursuitL);
    PixelGroup<88> camSidePixelsR = PixelGroup<88>(DeltaDisplayFursuitR);
    Camera<88> camSidePanelsL = Camera<88>(&camSideTransformL, &cameraLayout, &camSidePixelsL);
    Camera<88> camSidePanelsR = Camera<88>(&camSideTransformR, &cameraLayout, &camSidePixelsR);

public:
    APA102CamerasV1() : CameraManager(new CameraBase*[2]{ &camSidePanelsL, &camSidePanelsR }, 2) {}
};
