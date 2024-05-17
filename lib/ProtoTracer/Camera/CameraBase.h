#pragma once

#include "CameraLayout.h"
#include "Pixels/IPixelGroup.h"
#include "../Utils/Math/Transform.h"

class CameraBase {
protected:
    Transform* transform;
    CameraLayout* cameraLayout;
    Quaternion lookOffset;
    bool is2D = false;

public:
    CameraBase();

    virtual Vector2D GetCameraMinCoordinate() = 0;
    virtual Vector2D GetCameraMaxCoordinate() = 0;
    virtual Vector2D GetCameraCenterCoordinate() = 0;
    virtual IPixelGroup* GetPixelGroup() = 0;

    CameraLayout* GetCameraLayout();
    Transform* GetTransform();
    bool Is2D();
    void Set2D(bool is2D);
    void SetLookOffset(Quaternion lookOffset);
    Quaternion GetLookOffset();
};
