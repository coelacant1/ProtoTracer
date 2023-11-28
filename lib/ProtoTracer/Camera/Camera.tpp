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
    GetCameraMinCoordinate();
    GetCameraMaxCoordinate();

    return (minC + maxC) / 2.0f;
}
