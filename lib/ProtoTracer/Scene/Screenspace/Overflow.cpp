#include "Overflow.h"

Overflow::Overflow(uint8_t pixels) : pixels(pixels) {}

void Overflow::ApplyEffect(IPixelGroup* pixelGroup) {
    RGBColor* pixelColors = pixelGroup->GetColors();

    for (unsigned int i = 0; i < pixelGroup->GetPixelCount(); i++) {
        pixelColors[i].R = pixelColors[i].R != 0 ? pixelColors[i].R + 100 : 0;
        pixelColors[i].G = pixelColors[i].G != 0 ? pixelColors[i].G + 100 : 0;
        pixelColors[i].B = pixelColors[i].B != 0 ? pixelColors[i].B + 100 : 0;
    }
}
