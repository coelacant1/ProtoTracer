#pragma once

#include "..\CameraBase.h"

class CameraManager {
protected:
    CameraBase** cameras;
    uint8_t count;

public:
    CameraManager(CameraBase** cameras, uint8_t count) {
        this->cameras = cameras;
        this->count = count;
    }

    CameraBase** GetCameras() {
        return cameras;
    }

    uint8_t GetCameraCount() {
        return count;
    }

};
