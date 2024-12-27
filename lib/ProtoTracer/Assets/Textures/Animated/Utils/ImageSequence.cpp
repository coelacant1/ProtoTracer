// ImageSequence.cpp
#include "ImageSequence.h"

ImageSequence::ImageSequence(Image* image, const uint8_t** data, unsigned int imageCount, float fps) {
    this->startTime = millis();
    this->image = image;
    this->data = data;
    this->imageCount = imageCount;
    this->fps = fps;
    this->frameTime = ((float)imageCount) / fps;
}

void ImageSequence::SetFPS(float fps) {
    this->fps = fps;
}

void ImageSequence::SetSize(Vector2D size) {
    image->SetSize(size);
}

void ImageSequence::SetPosition(Vector2D offset) {
    image->SetPosition(offset);
}

void ImageSequence::SetRotation(float angle) {
    image->SetRotation(angle);
}

void ImageSequence::SetHueAngle(float hueAngle) {
    image->SetHueAngle(hueAngle);
}

void ImageSequence::Reset() {
    startTime = millis();
}

void ImageSequence::Update() {
    float currentTime = fmod((millis() - startTime) / 1000.0f, frameTime) / frameTime; // Normalize time to ratio

    currentFrame = (unsigned int)Mathematics::Map(currentTime, 0.0f, 1.0f, 0.0f, float(imageCount - 1));

    image->SetData(data[currentFrame]);
}

RGBColor ImageSequence::GetRGB(Vector3D intersection, Vector3D normal, Vector3D uvw) {
    return image->GetRGB(intersection, normal, uvw);
}
