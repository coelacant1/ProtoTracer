#pragma once

#include "..\Utils\Math\Transform.h"
#include "CameraLayout.h"
#include "CameraBase.h"
#include "Pixels\PixelGroup.h"

template<size_t pixelCount>
class Camera : public CameraBase{
private:
    Transform* transform;
    CameraLayout* cameraLayout;
    PixelGroup<pixelCount>* pixelGroup;
    Quaternion rayDirection;
    Quaternion lookDirection;
    Quaternion lookOffset;
    bool is2D = false;

public:
    Camera(Transform* transform, PixelGroup<pixelCount>* pixelGroup){
        this->transform = transform;
        this->pixelGroup = pixelGroup;

        is2D = true;
    }

    Camera(Transform* transform, CameraLayout* cameraLayout, PixelGroup<pixelCount>* pixelGroup){
        this->transform = transform;
        this->pixelGroup = pixelGroup;
        this->cameraLayout = cameraLayout;

        transform->SetBaseRotation(cameraLayout->GetRotation());
    }

    Transform* GetTransform(){
        return transform;
    }

    bool Is2D(){
        return is2D;
    }

    PixelGroup<pixelCount>* GetPixelGroup(){
        return pixelGroup;
    }

    CameraLayout* GetCameraLayout(){
        return cameraLayout;
    }

    Vector2D GetCameraMinCoordinate(){
        Vector2D min;

        for(uint16_t i = 0; i < pixelGroup->GetPixelCount(); i++){
            if(cameraLayout->GetForwardAxis() == cameraLayout->XForward){
                min.X = pixelGroup->GetCoordinate(i).X < min.X ? pixelGroup->GetCoordinate(i).X : min.X;
                min.Y = pixelGroup->GetCoordinate(i).Y < min.Y ? pixelGroup->GetCoordinate(i).Y : min.Y;
            }
        }

        return min;
    }

    Vector2D GetCameraMaxCoordinate(){
        Vector2D max;

        for(uint16_t i = 0; i < pixelGroup->GetPixelCount(); i++){
            if(cameraLayout->GetForwardAxis() == cameraLayout->XForward){
                max.X = pixelGroup->GetCoordinate(i).X < max.X ? pixelGroup->GetCoordinate(i).X : max.X;
                max.Y = pixelGroup->GetCoordinate(i).Y < max.Y ? pixelGroup->GetCoordinate(i).Y : max.Y;
            }
        }

        return max;
    }

    Vector2D GetCameraCenterCoordinate(){
        Vector2D min, max;

        min = GetCameraMinCoordinate();
        max = GetCameraMaxCoordinate();

        return (min + max) / 2.0f;
    }

    void SetLookOffset(Quaternion lookOffset){
        this->lookOffset = lookOffset;
    }
    
};
