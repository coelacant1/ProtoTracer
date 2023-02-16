#pragma once

#include "Effect.h"

class RadialBlur: public Effect {
private:
    const uint8_t pixels;

public:
    RadialBlur(uint8_t pixels) : pixels(pixels){}

    void ApplyEffect(PixelGroup* pixelGroup){
        RGBColor** pixelColors = pixelGroup->GetColors();

        for (unsigned int i = 0; i < pixelGroup->GetPixelCount(); i++){
            unsigned int indices[pixels][pixels];
            bool valid[pixels][pixels];

            for (uint8_t j = 0; j < pixels; j++) {
                for (uint8_t k = 0; k < pixels; k++) {
                    indices[j][k] = 0;
                    valid[j][k] = false;
                }
            }

            uint8_t blurRange = uint8_t(Mathematics::Map(ratio, 0.0f, 1.0f, 1.0f, float(pixels)));

            for (uint8_t j = 0; j < blurRange; j++){
                if(j == 0) valid[j][0] = pixelGroup->GetUpIndex(i, &indices[j][0]);
                else valid[j][0] = pixelGroup->GetUpIndex(indices[j - 1][0], &indices[j][0]);

                for(uint8_t k = 1; k < blurRange; k++){
                    if(j == 0) valid[j][k] = pixelGroup->GetRightIndex(indices[0][k], &indices[j][k]);
                    else valid[j][k] = pixelGroup->GetRightIndex(indices[j - 1][k], &indices[j][k]);
                }
            }

            uint16_t R = 0, G = 0, B = 0;

            for (uint8_t j = 0; j < blurRange; j++){
                for (uint8_t k = 0; k < blurRange; k++){
                    if (valid[j][k]){
                        R = R + pixelColors[indices[j][k]]->R;
                        G = G + pixelColors[indices[j][k]]->G;
                        B = B + pixelColors[indices[j][k]]->B;
                    }
                }
            }

            pixelColors[i]->R = R / (blurRange * blurRange);
            pixelColors[i]->B = G / (blurRange * blurRange);
            pixelColors[i]->G = B / (blurRange * blurRange);
        }
    }
};

