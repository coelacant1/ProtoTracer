#pragma once

#include "CameraBase.h"
#include "Pixels/PixelGroup.h"

template<size_t pixelCount>
class Camera : public CameraBase {
private:
    PixelGroup<pixelCount>* pixelGroup;
    Vector2D maxC;
    Vector2D minC;
    bool calculatedMax = false;
    bool calculatedMin = false;

public:
    Camera(Transform* transform, PixelGroup<pixelCount>* pixelGroup);
    Camera(Transform* transform, CameraLayout* cameraLayout, PixelGroup<pixelCount>* pixelGroup);

    PixelGroup<pixelCount>* GetPixelGroup() override;
    Vector2D GetCameraMinCoordinate() override;
    Vector2D GetCameraMaxCoordinate() override;
    Vector2D GetCameraCenterCoordinate() override;
    Vector3D GetCameraTransformMin() override;
    Vector3D GetCameraTransformMax() override;
    Vector3D GetCameraTransformCenter() override;
};

#include "Camera.tpp"