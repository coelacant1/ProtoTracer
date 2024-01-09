#include "GlitchX.h"

GlitchX::GlitchX(uint8_t pixels) : pixels(pixels) {}

void GlitchX::ApplyEffect(IPixelGroup* pixelGroup) {
    RGBColor* pixelColors = pixelGroup->GetColors();
    RGBColor* colorBuffer = pixelGroup->GetColorBuffer();

    for (uint16_t i = 0; i < pixelGroup->GetPixelCount(); i++) {
        uint16_t index = i;
        uint16_t tIndex = 0;
        bool valid = true;
        int blurRange = Mathematics::Map(ratio, 0.0f, 1.0f, 1.0f, float(pixels / 2));
        int randX = random(-blurRange, blurRange);
        int randSkip = random(1, blurRange);

        valid = pixelGroup->GetOffsetXIndex(index, &tIndex, randX);

        for (int j = 0; j < randSkip; j++) {
            if (randSkip < blurRange / 2 && valid) {
                colorBuffer[i].R = (uint16_t)pixelColors[tIndex].B;
                colorBuffer[i].G = (uint16_t)pixelColors[tIndex].R;
                colorBuffer[i].B = (uint16_t)pixelColors[tIndex].G;
            } else if (valid) {
                colorBuffer[i].R = (uint16_t)pixelColors[tIndex].R;
                colorBuffer[i].G = (uint16_t)pixelColors[tIndex].G;
                colorBuffer[i].B = (uint16_t)pixelColors[tIndex].B;
            } else {
                colorBuffer[i].R = 0;
                colorBuffer[i].B = 0;
                colorBuffer[i].G = 0;
            }

            if (j > 0) i++;

            if (i >= pixelGroup->GetPixelCount()) break;
        }
    }

    for (uint16_t i = 0; i < pixelGroup->GetPixelCount(); i++) {
        pixelColors[i].R = colorBuffer[i].R;
        pixelColors[i].G = colorBuffer[i].G;
        pixelColors[i].B = colorBuffer[i].B;
    }
}
