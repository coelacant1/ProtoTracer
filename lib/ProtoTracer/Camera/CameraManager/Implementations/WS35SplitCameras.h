#pragma once

#include "..\CameraManager.h"
#include "..\..\Camera.h"
#include "..\..\Pixels\PixelGroup.h"
#include "..\..\Pixels\PixelGroups\WS35Pixels.h"
#include "..\..\..\Utils\Math\Transform.h"

class WS35SplitCameraManager : public CameraManager {
private:
    CameraLayout cameraLayout;
    Transform camRghtTransform;
    Transform camLeftTransform;
    PixelGroup<571> camRghtPixels;
    PixelGroup<571> camLeftPixels;
    Camera<571> camRght;
    Camera<571> camLeft;

public:
    WS35SplitCameraManager() 
        : cameraLayout(CameraLayout::ZForward, CameraLayout::YUp),
          camRghtTransform(Vector3D(), Vector3D(0, 0, -500.0f), Vector3D(1, 1, 1)),
          camLeftTransform(Vector3D(), Vector3D(0, 0, -500.0f), Vector3D(1, 1, 1)),
          camRghtPixels(WS35Pixels, IPixelGroup::ZEROTOMAX),
          camLeftPixels(WS35Pixels, IPixelGroup::MAXTOZERO),
          camRght(&camRghtTransform, &cameraLayout, &camRghtPixels),
          camLeft(&camLeftTransform, &cameraLayout, &camLeftPixels),
          CameraManager(new CameraBase*[2]{ &camRght, &camLeft }, 2) {
    }

};
