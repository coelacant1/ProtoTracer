#pragma once

#include "Effect.h"
#include "..\Signals\FunctionGenerator.h"

class ShiftR : public Effect {
private:
    const uint8_t pixels;
    FunctionGenerator fGenPhase1 = FunctionGenerator(FunctionGenerator::Sawtooth, 0.0f, 1.0f, 4.5f);
    FunctionGenerator fGenPhase2 = FunctionGenerator(FunctionGenerator::Sawtooth, 0.0f, 1.0f, 3.2f);
    FunctionGenerator fGenRotation = FunctionGenerator(FunctionGenerator::Sawtooth, 0.0f, 360.0f, 3.7f);

public:
    ShiftR(uint8_t pixels) : pixels(pixels){}

    void ApplyEffect(IPixelGroup* pixelGroup) override{
        unsigned int pixelCount = pixelGroup->GetPixelCount();
        RGBColor* pixelColors = pixelGroup->GetColors();
        RGBColor* colorBuffer = pixelGroup->GetColorBuffer();

        float rotation = fGenRotation.Update();

        for (unsigned int i = 0; i < pixelCount; i++){
            unsigned int indexR, indexG, indexB;
            bool validR, validG, validB;

            uint8_t range = (uint8_t)Mathematics::Map(ratio, 0.0f, 1.0f, 0.0f, (float)pixels);

            validR = pixelGroup->GetRadialIndex(i, &indexR, range, rotation);
            validG = pixelGroup->GetRadialIndex(i, &indexG, range, rotation + 120.0f);
            validB = pixelGroup->GetRadialIndex(i, &indexB, range, rotation + 240.0f);

            if(validR) colorBuffer[i].R = pixelColors[indexR].R;
            else colorBuffer[i].R = 0;
            
            if(validG) colorBuffer[i].G = pixelColors[indexG].G;
            else colorBuffer[i].G = 0;
            
            if(validB) colorBuffer[i].B = pixelColors[indexB].B;
            else colorBuffer[i].B = 0;
        }
        
        for (unsigned int i = 0; i < pixelCount; i++){
            pixelColors[i].R = colorBuffer[i].R;
            pixelColors[i].G = colorBuffer[i].G;
            pixelColors[i].B = colorBuffer[i].B;
        }
    }
};
