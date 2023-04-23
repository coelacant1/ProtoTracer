#pragma once

#include "Effect.h"
#include "Arduino.h"
#include "..\Signals\FunctionGenerator.h"

class Magnet: public Effect {
private:
    Vector2D offset = Vector2D(0.0f, 0.0f);
    float amplitude;
    FunctionGenerator fGenSize = FunctionGenerator(FunctionGenerator::Sine, 1.0f, 5000.0f, 2.3f);
    FunctionGenerator fGenX = FunctionGenerator(FunctionGenerator::Sine, -96.0f, 96.0f, 2.7f);
    FunctionGenerator fGenY = FunctionGenerator(FunctionGenerator::Sine, -96.0f, 96.0f, 1.7f);
    FunctionGenerator fGenWarp = FunctionGenerator(FunctionGenerator::Sine, 1.0f, 100.0f, 3.7f);

public:
    Magnet(float amplitude = 0.5f) : amplitude(amplitude) {}

    void SetPosition(Vector2D offset){
        this->offset = offset;
    }

    void SetAmplitude(float amplitude) {
        this->amplitude = amplitude;
    }

    void ApplyEffect(IPixelGroup* pixelGroup) override {
        RGBColor* pixelColors = pixelGroup->GetColors();
        RGBColor* colorBuffer = pixelGroup->GetColorBuffer();
        Vector2D mid = pixelGroup->GetCenterCoordinate();
        unsigned int tIndex = 0;

        //amplitude = fGenWarp.Update() * ratio;

        //offset.X = 65.0f;//fGenX.Update() * ratio;
        //offset.Y = -50.0f;//fGenY.Update() * ratio;

        for (unsigned int i = 0; i < pixelGroup->GetPixelCount(); i++){
            Vector2D pos = pixelGroup->GetCoordinate(i) + offset;
            Vector2D dif = pos - mid + Vector2D(0.0f, 50.0f);
            float distance = fabsf(pos.CalculateEuclideanDistance(mid));
        
            float theta = atan2(dif.Y, dif.X);
            float newDistance = (1.0f / distance) * 0.5f * amplitude * 4.0f;// * 10000.0f;//fGenSize.Update();

            int offsetX = (int)(newDistance * cosf(theta));
            int offsetY = (int)(newDistance * sinf(theta));

            // Use this function to find the index of the pixel at the offset x y pixel
            if(pixelGroup->GetOffsetXYIndex(i, &tIndex, offsetX, offsetY)){
                colorBuffer[i].R = pixelColors[tIndex].R;// copy the current pixel color into the buffer
                colorBuffer[i].G = pixelColors[tIndex].G;
                colorBuffer[i].B = pixelColors[tIndex].B;
            }
            else{
                colorBuffer[i].R = 0;// copy the current pixel color into the buffer
                colorBuffer[i].G = 0;
                colorBuffer[i].B = 0;
            }
        }

        for (unsigned int i = 0; i < pixelGroup->GetPixelCount(); i++){
            pixelColors[i].R = colorBuffer[i].R;
            pixelColors[i].G = colorBuffer[i].G;
            pixelColors[i].B = colorBuffer[i].B;
        }
    }

};

