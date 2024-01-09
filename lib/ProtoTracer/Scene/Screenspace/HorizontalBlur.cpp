#include "HorizontalBlur.h"

HorizontalBlur::HorizontalBlur(uint8_t pixels) : pixels(pixels) {}

void HorizontalBlur::ApplyEffect(IPixelGroup* pixelGroup) {
    RGBColor* pixelColors = pixelGroup->GetColors();
    RGBColor* colorBuffer = pixelGroup->GetColorBuffer();

    for (uint16_t i = 0; i < pixelGroup->GetPixelCount(); i++) {
        uint16_t indexLeft = i;
        uint16_t indexRight = i;
        uint16_t tIndexLeft = 0;
        uint16_t tIndexRight = 0;
        bool validL = false;
        bool validR = false;

        uint16_t blurRange = uint16_t(Mathematics::Map(ratio, 0.0f, 1.0f, 1.0f, float(pixels / 2)));

        uint16_t R, G, B;

        R = (uint16_t)pixelColors[i].R;
        G = (uint16_t)pixelColors[i].G;
        B = (uint16_t)pixelColors[i].B;

        for (uint8_t j = 1; j < blurRange + 1; j++) {
            validL = pixelGroup->GetLeftIndex(indexLeft, &tIndexLeft);
            validR = pixelGroup->GetRightIndex(indexRight, &tIndexRight);

            indexLeft = tIndexLeft;
            indexRight = tIndexRight;

            if (validL && validR) {
                R = R + (uint16_t)pixelColors[indexLeft].R + (uint16_t)pixelColors[indexRight].R;
                G = G + (uint16_t)pixelColors[indexLeft].G + (uint16_t)pixelColors[indexRight].G;
                B = B + (uint16_t)pixelColors[indexLeft].B + (uint16_t)pixelColors[indexRight].B;
            }
        }

        colorBuffer[i].R = Mathematics::Constrain(R / (blurRange * 2), 0, 255);
        colorBuffer[i].B = Mathematics::Constrain(G / (blurRange * 2), 0, 255);
        colorBuffer[i].G = Mathematics::Constrain(B / (blurRange * 2), 0, 255);
    }

    for (uint16_t i = 0; i < pixelGroup->GetPixelCount(); i++) {
        pixelColors[i].R = colorBuffer[i].R;
        pixelColors[i].G = colorBuffer[i].G;
        pixelColors[i].B = colorBuffer[i].B;
    }
}
