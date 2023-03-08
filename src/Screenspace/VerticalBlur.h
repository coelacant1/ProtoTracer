#pragma once

#include "Effect.h"

class VerticalBlur: public Effect {
private:
    const uint8_t pixels;

public:
    VerticalBlur(uint8_t pixels) : pixels(pixels){}

    void ApplyEffect(IPixelGroup* pixelGroup){
        RGBColor* pixelColors = pixelGroup->GetColors();
        RGBColor* colorBuffer = pixelGroup->GetColorBuffer();

        for (unsigned int i = 0; i < pixelGroup->GetPixelCount(); i++){
            unsigned int indexUp = i;
            unsigned int indexDown = i;
            unsigned int tIndexUp = 0;
            unsigned int tIndexDown = 0;
            bool validL = true;
            bool validR = true;

            uint16_t blurRange = uint16_t(Mathematics::Map(ratio, 0.0f, 1.0f, 1.0f, float(pixels / 2)));

            uint16_t R, G, B;

            R = (uint16_t)pixelColors[i].R;
            G = (uint16_t)pixelColors[i].G;
            B = (uint16_t)pixelColors[i].B;
            
            for (uint8_t j = 1; j < blurRange + 1; j++){
                validL = pixelGroup->GetUpIndex(indexUp, &tIndexUp);
                validR = pixelGroup->GetDownIndex(indexDown, &tIndexDown);

                indexUp = tIndexUp;
                indexDown = tIndexDown;

                if (validL && validR){
                    R = R + (uint16_t)pixelColors[indexUp].R + (uint16_t)pixelColors[indexDown].R;
                    G = G + (uint16_t)pixelColors[indexUp].G + (uint16_t)pixelColors[indexDown].G;
                    B = B + (uint16_t)pixelColors[indexUp].B + (uint16_t)pixelColors[indexDown].B;
                }
            }
            
            colorBuffer[i].R = Mathematics::Constrain(R / (blurRange * 2), 0, 255);
            colorBuffer[i].B = Mathematics::Constrain(G / (blurRange * 2), 0, 255);
            colorBuffer[i].G = Mathematics::Constrain(B / (blurRange * 2), 0, 255);
        }

        for (unsigned int i = 0; i < pixelGroup->GetPixelCount(); i++){
            pixelColors[i].R = colorBuffer[i].R;
            pixelColors[i].G = colorBuffer[i].G;
            pixelColors[i].B = colorBuffer[i].B;
        }
    }
};

