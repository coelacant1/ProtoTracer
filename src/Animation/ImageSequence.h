#pragma once

#include "Arduino.h"
#include "..\Materials\Image.h"
#include "..\Materials\Material.h"

class ImageSequence : public Material{
private:
    Image* image;
    const uint8_t** data;
    unsigned long startTime = 0;
    unsigned int imageCount = 0;
    float fps = 24.0f;
    float frameTime = 0.0f;
    unsigned int currentFrame = 0;

protected:
    ImageSequence(Image* image, const uint8_t** data, unsigned int imageCount, float fps){
        this->startTime = millis();
        this->image = image;
        this->data = data;
        this->imageCount = imageCount;
        this->fps = fps;
        this->frameTime = ((float)imageCount) / fps;
    }

public:
    void SetFPS(float fps){
        this->fps = fps;
    }
    
    void SetSize(Vector2D size){
        image->SetSize(size);
    }

    void SetPosition(Vector2D offset){
        image->SetPosition(offset);
    }

    void SetRotation(float angle){
        image->SetRotation(angle);
    }

    void SetHueAngle(float hueAngle){
        image->SetHueAngle(hueAngle);
    }

    void Reset(){
        startTime = millis();
    }

    void Update(){
        float currentTime = fmod((millis() - startTime) / 1000.0f, frameTime) / frameTime;//normalize time to ratio

        currentFrame = (unsigned int)Mathematics::Map(currentTime, 0.0f, 1.0f, 0, imageCount - 1);

        image->SetData(data[currentFrame]);
    }

    RGBColor GetRGB(Vector3D intersection, Vector3D normal, Vector3D uvw){
        return image->GetRGB(intersection, normal, uvw);
    }
};
