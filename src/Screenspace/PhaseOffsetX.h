#pragma once

#include "Effect.h"
#include "..\Signals\FunctionGenerator.h"

class PhaseOffsetX : public Effect {
private:
    const uint8_t pixels;
    FunctionGenerator fGenPhase = FunctionGenerator(FunctionGenerator::Sawtooth, 0.0f, 1.0f, 3.5f);

public:
    PhaseOffsetX(uint8_t pixels) : pixels(pixels){}

    void ApplyEffect(IPixelGroup* pixelGroup) override {
        RGBColor* pixelColors = pixelGroup->GetColors();

        for (unsigned int i = 0; i < pixelGroup->GetPixelCount(); i++){
            unsigned int indices[pixels + 1];
            bool valid[pixels];

            indices[0] = i;

            float range = (pixels - 1) * ratio + 1;
            float coordY = pixelGroup->GetCoordinate(i).Y / 10.0f;
            float mpiR = 2.0f * Mathematics::MPI * fGenPhase.Update();
            float sineR = sinf(coordY + mpiR * 8.0f);
            float sineG = sinf(coordY + mpiR * 8.0f + 2.0f * Mathematics::MPI * 0.333f);
            float sineB = sinf(coordY + mpiR * 8.0f + 2.0f * Mathematics::MPI * 0.666f);

            uint8_t blurRangeR = Mathematics::Constrain(uint8_t(Mathematics::Map(sineR, -1.0f, 1.0f, 1.0f, range)), uint8_t(1), uint8_t(range));
            uint8_t blurRangeG = Mathematics::Constrain(uint8_t(Mathematics::Map(sineG, -1.0f, 1.0f, 1.0f, range)), uint8_t(1), uint8_t(range));
            uint8_t blurRangeB = Mathematics::Constrain(uint8_t(Mathematics::Map(sineB, -1.0f, 1.0f, 1.0f, range)), uint8_t(1), uint8_t(range));
            
            uint8_t maxValue = Mathematics::Max(blurRangeR, blurRangeG, blurRangeB);

            for (uint8_t j = 1; j < maxValue + 1; j++){
                valid[j] = pixelGroup->GetRightIndex(indices[j - 1], &indices[j]);
            }

            if(valid[blurRangeR]) pixelColors[i].R = pixelColors[indices[blurRangeR]].R;
            else pixelColors[i].R = 0;
            
            if(valid[blurRangeG]) pixelColors[i].G = pixelColors[indices[blurRangeG]].G;
            else pixelColors[i].G = 0;
            
            if(valid[blurRangeB]) pixelColors[i].B = pixelColors[indices[blurRangeB]].B;
            else pixelColors[i].B = 0;
        }
    }

};

