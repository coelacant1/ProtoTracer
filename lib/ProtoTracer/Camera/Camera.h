#pragma once

#include "CameraBase.h"
#include "Pixels\PixelGroup.h"

template<size_t pixelCount>
class Camera : public CameraBase{
private:
    PixelGroup<pixelCount>* pixelGroup;

public:
    Camera(Transform* transform, PixelGroup<pixelCount>* pixelGroup){
        this->transform = transform;
        this->pixelGroup = pixelGroup;

        Set2D(true);
    }

    Camera(Transform* transform, CameraLayout* cameraLayout, PixelGroup<pixelCount>* pixelGroup){
        this->transform = transform;
        this->pixelGroup = pixelGroup;
        this->cameraLayout = cameraLayout;

        transform->SetBaseRotation(cameraLayout->GetRotation());

        Set2D(false);
    }

    PixelGroup<pixelCount>* GetPixelGroup() override {
        return pixelGroup;
    }

    Vector2D GetCameraMinCoordinate() override {
        Vector2D min;

        for(uint16_t i = 0; i < pixelGroup->GetPixelCount(); i++){
            if(cameraLayout->GetForwardAxis() == cameraLayout->XForward){
                min.X = pixelGroup->GetCoordinate(i).X < min.X ? pixelGroup->GetCoordinate(i).X : min.X;
                min.Y = pixelGroup->GetCoordinate(i).Y < min.Y ? pixelGroup->GetCoordinate(i).Y : min.Y;
            }
        }

        return min;
    }

    Vector2D GetCameraMaxCoordinate() override {
        Vector2D max;

        for(uint16_t i = 0; i < pixelGroup->GetPixelCount(); i++){
            if(cameraLayout->GetForwardAxis() == cameraLayout->XForward){
                max.X = pixelGroup->GetCoordinate(i).X < max.X ? pixelGroup->GetCoordinate(i).X : max.X;
                max.Y = pixelGroup->GetCoordinate(i).Y < max.Y ? pixelGroup->GetCoordinate(i).Y : max.Y;
            }
        }

        return max;
    }

    Vector2D GetCameraCenterCoordinate() override {
        Vector2D min, max;

        min = GetCameraMinCoordinate();
        max = GetCameraMaxCoordinate();

        return (min + max) / 2.0f;
    }

};
