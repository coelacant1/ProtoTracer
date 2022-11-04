#pragma once

#include "..\Render\Camera.h"

class Controller {
private:
    const float softStart = 3000000;//microseconds
    long previousTime;
    Camera** cameras;
    uint8_t count = 0;
    float renderTime = 0.0f;
    uint8_t maxBrightness;
    uint8_t maxAccentBrightness;
    bool isOn = false;

    void UpdateBrightness(){
        if (!isOn && previousTime < softStart){
            brightness = map(previousTime, 0, softStart, 0, maxBrightness);
            accentBrightness = map(previousTime, 0, softStart, 0, maxAccentBrightness);
        }
        else if (!isOn){
            brightness = maxBrightness;
            accentBrightness = maxAccentBrightness;
            isOn = true;
        }
    }

protected:
    uint8_t brightness;
    uint8_t accentBrightness;

    Controller(Camera** cameras, uint8_t count, uint8_t maxBrightness, uint8_t maxAccentBrightness){
        this->cameras = cameras;
        this->count = count;
        this->maxBrightness = maxBrightness;
        this->maxAccentBrightness = maxAccentBrightness;
        previousTime = micros();
    }

public:
    Camera** GetCameras(){
        return cameras;
    }

    uint8_t GetCameraCount(){
        return count;
    }

    void Render(Scene* scene){
        previousTime = micros();

        UpdateBrightness();

        for (int i = 0; i < count; i++){
            cameras[i]->Rasterize(scene);
        }

        renderTime = ((float)(micros() - previousTime)) / 1000000.0f;
    }

    void RenderCamera(Scene* scene, uint8_t cameraNum){
        previousTime = micros();

        UpdateBrightness();

        cameras[cameraNum]->Rasterize(scene);

        renderTime = ((float)(micros() - previousTime)) / 1000000.0f;
    }

    void SetBrightness(uint8_t maxBrightness){
        this->maxBrightness = maxBrightness;
        
        if(isOn){//past soft start
            this->brightness = maxBrightness;
        }
    }

    void SetAccentBrightness(uint8_t maxAccentBrightness){
        this->maxAccentBrightness = maxAccentBrightness;
        
        if(isOn){//past soft start
            this->accentBrightness = maxAccentBrightness;
        }
    }

    virtual void Initialize() = 0;
    virtual void Display() = 0;

    float GetRenderTime(){
        return renderTime;
    }

};
