#pragma once

#include "Effect.h"
#include "..\..\Utils\Signals\FunctionGenerator.h"

class PhaseOffsetR : public Effect {
private:
    const uint8_t pixels;
    FunctionGenerator fGenPhase1 = FunctionGenerator(FunctionGenerator::Sawtooth, 0.0f, 1.0f, 4.5f);
    FunctionGenerator fGenPhase2 = FunctionGenerator(FunctionGenerator::Sawtooth, 0.0f, 1.0f, 3.2f);
    FunctionGenerator fGenRotation = FunctionGenerator(FunctionGenerator::Sawtooth, 0.0f, 360.0f, 3.7f);

public:
    PhaseOffsetR(uint8_t pixels) : pixels(pixels){}

    void ApplyEffect(IPixelGroup* pixelGroup) override{
        unsigned int pixelCount = pixelGroup->GetPixelCount();
        RGBColor* pixelColors = pixelGroup->GetColors();
        RGBColor* colorBuffer = pixelGroup->GetColorBuffer();

        float rotation = fGenRotation.Update();
        float range = (pixels - 1) * ratio + 1;
        float phase120 = 2.0f * Mathematics::MPI * 0.333f;
        float phase240 = 2.0f * Mathematics::MPI * 0.666f;
        float mpiR1R = 2.0f * Mathematics::MPI * 8.0f;
        float mpiR2R = 2.0f * Mathematics::MPI * 8.0f;
        float mpiR1G = mpiR1R + phase120;
        float mpiR2G = mpiR2R + phase120;
        float mpiR1B = mpiR1R + phase240;
        float mpiR2B = mpiR2R + phase240;

        for (unsigned int i = 0; i < pixelCount; i++){
            unsigned int indexR, indexG, indexB;
            bool validR, validG, validB;

            float coordX = pixelGroup->GetCoordinate(i).X / 10.0f;
            float coordY = pixelGroup->GetCoordinate(i).Y / 5.0f;
            float offset1 = fGenPhase1.Update();
            float offset2 = fGenPhase2.Update();
            float sineR = sinf(coordX + mpiR1R * offset1) + cosf(coordY + mpiR2R * offset2);
            float sineG = sinf(coordX + mpiR1G * offset1) + cosf(coordY + mpiR2G * offset2);
            float sineB = sinf(coordX + mpiR1B * offset1) + cosf(coordY + mpiR2B * offset2);

            uint8_t blurRangeR = Mathematics::Constrain(uint8_t(Mathematics::Map(sineR, -1.0f, 1.0f, 1.0f, range)), uint8_t(1), uint8_t(range));
            uint8_t blurRangeG = Mathematics::Constrain(uint8_t(Mathematics::Map(sineG, -1.0f, 1.0f, 1.0f, range)), uint8_t(1), uint8_t(range));
            uint8_t blurRangeB = Mathematics::Constrain(uint8_t(Mathematics::Map(sineB, -1.0f, 1.0f, 1.0f, range)), uint8_t(1), uint8_t(range));

            validR = pixelGroup->GetRadialIndex(i, &indexR, blurRangeR, rotation);
            validG = pixelGroup->GetRadialIndex(i, &indexG, blurRangeG, rotation + 120.0f);
            validB = pixelGroup->GetRadialIndex(i, &indexB, blurRangeB, rotation + 240.0f);

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

