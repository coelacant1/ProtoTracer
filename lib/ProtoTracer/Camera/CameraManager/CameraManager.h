#pragma once

#include "..\CameraBase.h"

class CameraManager {
protected:
    CameraBase** cameras;
    uint8_t count;

public:
    CameraManager(CameraBase** cameras, uint8_t count);

    CameraBase** GetCameras();
    uint8_t GetCameraCount();
};
