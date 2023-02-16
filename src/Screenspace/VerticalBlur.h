#pragma once

#include "Effect.h"

class VerticalBlur: public Effect {
private:
    const uint8_t pixels;

public:
    VerticalBlur(uint8_t pixels) : pixels(pixels){}

    void ApplyEffect(PixelGroup* pixelGroup){
        RGBColor** pixelColors = pixelGroup->GetColors();

        for (unsigned int i = 0; i < pixelGroup->GetPixelCount(); i++){
            unsigned int indices[pixels + 1];
            bool valid[pixels];

            indices[0] = i;

            uint8_t blurRange = uint8_t(Mathematics::Map(ratio, 0.0f, 1.0f, 1.0f, float(pixels)));

            for (uint8_t j = 1; j < blurRange + 1; j++){
                valid[j] = pixelGroup->GetUpIndex(indices[j - 1], &indices[j]);
            }

            uint16_t R = 0, G = 0, B = 0;

            for (uint8_t j = 1; j < blurRange + 1; j++){
                if (valid[j]){
                    R = R + pixelColors[indices[j]]->R;
                    G = G + pixelColors[indices[j]]->G;
                    B = B + pixelColors[indices[j]]->B;
                }
            }

            pixelColors[i]->R = R / blurRange;
            pixelColors[i]->B = G / blurRange;
            pixelColors[i]->G = B / blurRange;
        }
    }
};

