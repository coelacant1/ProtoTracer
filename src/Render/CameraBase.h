#pragma once

#include "IPixelGroup.h"
#include "Scene.h"

class CameraBase {
protected:

public:
    CameraBase() {}

    virtual void Rasterize(Scene* scene) = 0;

    virtual Vector2D GetCameraCenterCoordinate() = 0;

    virtual IPixelGroup* GetPixelGroup() = 0;
};
