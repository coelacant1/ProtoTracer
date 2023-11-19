#pragma once

#include "Effect.h"
#include "..\..\Utils\Signals\FunctionGenerator.h"

class Test : public Effect {
private:
    FunctionGenerator fGenD = FunctionGenerator(FunctionGenerator::Sine, 0.0f, 255.0f, 0.5f);

public:
    Test(){}

    void ApplyEffect(IPixelGroup* pixelGroup){
        unsigned int pixelCount = pixelGroup->GetPixelCount();
        RGBColor* pixelColors = pixelGroup->GetColors();
        RGBColor* colorBuffer = pixelGroup->GetColorBuffer();

        for (unsigned int i = 0; i < pixelCount; i++){
            colorBuffer[i].R = 0;
            colorBuffer[i].G = 0;
            colorBuffer[i].B = 0;
        }

        for (unsigned int i = 0; i < pixelCount; i++){
            /////////////////////////////

            unsigned int leftIndex = i;
            unsigned int rightIndex = i;
            unsigned int upIndex = i;
            unsigned int downIndex = i;

            uint8_t d = fGenD.Update();

            bool validLeft = pixelGroup->GetLeftIndex(leftIndex, &leftIndex);
            bool validRight = pixelGroup->GetRightIndex(rightIndex, &rightIndex);
            bool validUp = pixelGroup->GetUpIndex(upIndex, &upIndex);
            bool validDown = pixelGroup->GetDownIndex(downIndex, &downIndex);

            if (validLeft){
                colorBuffer[leftIndex].R = 100;
            }
            if (validRight){
                colorBuffer[rightIndex].G = 100;
            }
            if (validUp){
                colorBuffer[upIndex].B = 100;
            }
            if (validDown){
                colorBuffer[downIndex].R = colorBuffer[downIndex].R == 100 ? 100 : d;
                colorBuffer[downIndex].G = colorBuffer[downIndex].G == 100 ? 100 : d;
                colorBuffer[downIndex].B = colorBuffer[downIndex].B == 100 ? 100 : d;
            }
        }

        //////////////////////////////////////
        for (unsigned int i = 0; i < pixelCount; i++){
            pixelColors[i].R = colorBuffer[i].R;
            pixelColors[i].G = colorBuffer[i].G;
            pixelColors[i].B = colorBuffer[i].B;
        }
    }
};

