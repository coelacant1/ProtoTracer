#pragma once

#include "..\CameraManager.h"
#include "..\..\Camera.h"
#include "..\..\Pixels\PixelGroup.h"
#include "..\..\Pixels\PixelGroups\WS35Pixels.h"
#include "..\..\..\Utils\Math\Transform.h"

class WS35CameraManager : public CameraManager {
private:
    CameraLayout cameraLayout;
    Transform camTransform;
    PixelGroup<571> camPixels;
    Camera<571> cam;

public:
    WS35CameraManager() 
        : cameraLayout(CameraLayout::ZForward, CameraLayout::YUp),
          camTransform(Vector3D(), Vector3D(0, 0, -500.0f), Vector3D(1, 1, 1)),
          camPixels(WS35Pixels, IPixelGroup::ZEROTOMAX),
          cam(&camTransform, &cameraLayout, &camPixels),
          CameraManager(new CameraBase*[1]{ &camRght }, 1) {
    }

};
