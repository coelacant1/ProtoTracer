#include "Test.h"

Test::Test() {}

void Test::ApplyEffect(IPixelGroup* pixelGroup) {
    uint16_t pixelCount = pixelGroup->GetPixelCount();
    RGBColor* pixelColors = pixelGroup->GetColors();
    RGBColor* colorBuffer = pixelGroup->GetColorBuffer();

    for (uint16_t i = 0; i < pixelCount; i++) {
        colorBuffer[i].R = 0;
        colorBuffer[i].G = 0;
        colorBuffer[i].B = 0;
    }

    for (uint16_t i = 0; i < pixelCount; i++) {
        uint16_t leftIndex = i;
        uint16_t rightIndex = i;
        uint16_t upIndex = i;
        uint16_t downIndex = i;

        uint8_t d = fGenD.Update();

        bool validLeft = pixelGroup->GetLeftIndex(leftIndex, &leftIndex);
        bool validRight = pixelGroup->GetRightIndex(rightIndex, &rightIndex);
        bool validUp = pixelGroup->GetUpIndex(upIndex, &upIndex);
        bool validDown = pixelGroup->GetDownIndex(downIndex, &downIndex);

        if (validLeft) {
            colorBuffer[leftIndex].R = 100;
        }
        if (validRight) {
            colorBuffer[rightIndex].G = 100;
        }
        if (validUp) {
            colorBuffer[upIndex].B = 100;
        }
        if (validDown) {
            colorBuffer[downIndex].R = colorBuffer[downIndex].R == 100 ? 100 : d;
            colorBuffer[downIndex].G = colorBuffer[downIndex].G == 100 ? 100 : d;
            colorBuffer[downIndex].B = colorBuffer[downIndex].B == 100 ? 100 : d;
        }
    }

    for (uint16_t i = 0; i < pixelCount; i++) {
        pixelColors[i].R = colorBuffer[i].R;
        pixelColors[i].G = colorBuffer[i].G;
        pixelColors[i].B = colorBuffer[i].B;
    }
}
