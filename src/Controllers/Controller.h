#pragma once

#include "..\Render\Camera.h"

class Controller {
private:
    long previousTime;
    Camera** cameras;
    uint8_t count = 0;
    float renderTime = 0.0f;

protected:
    Controller(Camera** cameras, uint8_t count){
        this->cameras = cameras;
        this->count = count;
        previousTime = micros();
    }

public:
    void Render(Scene* scene){
        previousTime = micros();

        for (int i = 0; i < count; i++){
            cameras[i]->Rasterize(scene);
        }

        renderTime = ((float)(micros() - previousTime)) / 1000000.0f;
    }

    virtual void Initialize() = 0;
    virtual void Display() = 0;

    float GetRenderTime(){
        return renderTime;
    }

};
