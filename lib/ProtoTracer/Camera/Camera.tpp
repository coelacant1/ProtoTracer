#pragma once

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
    Vector2D min;

    for(uint16_t i = 0; i < pixelGroup->GetPixelCount(); i++){
        if(cameraLayout->GetForwardAxis() == cameraLayout->XForward){
            min.X = pixelGroup->GetCoordinate(i).X < min.X ? pixelGroup->GetCoordinate(i).X : min.X;
            min.Y = pixelGroup->GetCoordinate(i).Y < min.Y ? pixelGroup->GetCoordinate(i).Y : min.Y;
        }
    }

    return min;
}

template<size_t pixelCount>
Vector2D Camera<pixelCount>::GetCameraMaxCoordinate() {
    Vector2D max;

    for(uint16_t i = 0; i < pixelGroup->GetPixelCount(); i++){
        if(cameraLayout->GetForwardAxis() == cameraLayout->XForward){
            max.X = pixelGroup->GetCoordinate(i).X < max.X ? pixelGroup->GetCoordinate(i).X : max.X;
            max.Y = pixelGroup->GetCoordinate(i).Y < max.Y ? pixelGroup->GetCoordinate(i).Y : max.Y;
        }
    }

    return max;
}

template<size_t pixelCount>
Vector2D Camera<pixelCount>::GetCameraCenterCoordinate() {
    Vector2D min, max;

    min = GetCameraMinCoordinate();
    max = GetCameraMaxCoordinate();

    return (min + max) / 2.0f;
}
