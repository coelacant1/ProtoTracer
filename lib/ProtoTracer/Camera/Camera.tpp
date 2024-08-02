#pragma once

#include <Arduino.h>

template<size_t pixelCount>
Camera<pixelCount>::Camera(Transform* transform, PixelGroup<pixelCount>* pixelGroup) {
    this->transform = transform;
    this->pixelGroup = pixelGroup;

    Set2D(true);
}

template<size_t pixelCount>
Camera<pixelCount>::Camera(Transform* transform, CameraLayout* cameraLayout, PixelGroup<pixelCount>* pixelGroup) {
    this->transform = transform;
    this->pixelGroup = pixelGroup;
    this->cameraLayout = cameraLayout;

    transform->SetBaseRotation(cameraLayout->GetRotation());

    Set2D(false);
}

template<size_t pixelCount>
PixelGroup<pixelCount>* Camera<pixelCount>::GetPixelGroup() {
    return pixelGroup;
}

template<size_t pixelCount>
Vector2D Camera<pixelCount>::GetCameraMinCoordinate() {
    if(!calculatedMin){
        for(uint16_t i = 0; i < pixelGroup->GetPixelCount(); i++){
            minC.X = pixelGroup->GetCoordinate(i).X < minC.X ? pixelGroup->GetCoordinate(i).X : minC.X;
            minC.Y = pixelGroup->GetCoordinate(i).Y < minC.Y ? pixelGroup->GetCoordinate(i).Y : minC.Y;
        }

        calculatedMin = true;
    }

    return minC;
}

template<size_t pixelCount>
Vector2D Camera<pixelCount>::GetCameraMaxCoordinate() {
    if(!calculatedMax){
        for(uint16_t i = 0; i < pixelGroup->GetPixelCount(); i++){
            maxC.X = pixelGroup->GetCoordinate(i).X > maxC.X ? pixelGroup->GetCoordinate(i).X : maxC.X;
            maxC.Y = pixelGroup->GetCoordinate(i).Y > maxC.Y ? pixelGroup->GetCoordinate(i).Y : maxC.Y;
        }

        calculatedMax = true;
    }

    return maxC;
}

template<size_t pixelCount>
Vector2D Camera<pixelCount>::GetCameraCenterCoordinate() {
    return (GetCameraMinCoordinate() + GetCameraMaxCoordinate()) / 2.0f;
}

template<size_t pixelCount>
Vector3D Camera<pixelCount>::GetCameraTransformMin() {
    Vector2D minV2 = GetCameraMinCoordinate();

    return transform->GetRotation().RotateVector(Vector3D(minV2.X, minV2.Y, 0) * transform->GetScale()) + transform->GetPosition();
}

template<size_t pixelCount>
Vector3D Camera<pixelCount>::GetCameraTransformMax() {
    Vector2D maxV2 = GetCameraMaxCoordinate();

    return transform->GetRotation().RotateVector(Vector3D(maxV2.X, maxV2.Y, 0) * transform->GetScale()) + transform->GetPosition();
}

template<size_t pixelCount>
Vector3D Camera<pixelCount>::GetCameraTransformCenter() {
    return (GetCameraTransformMin() + GetCameraTransformMax()) / 2.0f;
}
