#pragma once

#include "Pixels\IPixelGroup.h"

class CameraBase {
protected:

public:
    CameraBase() {}

    virtual Vector2D GetCameraCenterCoordinate() = 0;

    virtual IPixelGroup* GetPixelGroup() = 0;
};
