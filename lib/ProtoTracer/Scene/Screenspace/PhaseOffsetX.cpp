#include "PhaseOffsetX.h"
#include "../../Utils/Math/Mathematics.h"

PhaseOffsetX::PhaseOffsetX(uint8_t pixels) : pixels(pixels) {}

void PhaseOffsetX::ApplyEffect(IPixelGroup* pixelGroup) {
    if (ratio <= 0.001f) return;

    RGBColor* pixelColors = pixelGroup->GetColors();
    RGBColor* colorBuffer = pixelGroup->GetColorBuffer();

    for (uint16_t i = 0; i < pixelGroup->GetPixelCount(); i++) {
        float range = ((pixels - 1) * ratio + 1) / 2.0f;
        float coordY = pixelGroup->GetCoordinate(i).Y / 10.0f;
        float mpiR = 2.0f * Mathematics::MPI * fGenPhase.Update();
        float sineR = sinf(coordY + mpiR * 8.0f);
        float sineG = sinf(coordY + mpiR * 8.0f + 2.0f * Mathematics::MPI * 0.333f);
        float sineB = sinf(coordY + mpiR * 8.0f + 2.0f * Mathematics::MPI * 0.666f);

        int8_t blurRangeR = Mathematics::Constrain(int8_t(Mathematics::Map(sineR, -1.0f, 1.0f, -range, range)), int8_t(-range), int8_t(range));
        int8_t blurRangeG = Mathematics::Constrain(int8_t(Mathematics::Map(sineG, -1.0f, 1.0f, -range, range)), int8_t(-range), int8_t(range));
        int8_t blurRangeB = Mathematics::Constrain(int8_t(Mathematics::Map(sineB, -1.0f, 1.0f, -range, range)), int8_t(-range), int8_t(range));

        uint16_t indexR = 0, indexG = 0, indexB = 0;

        bool validR = pixelGroup->GetOffsetXIndex(i, &indexR, blurRangeR);
        bool validG = pixelGroup->GetOffsetXIndex(i, &indexG, blurRangeG);
        bool validB = pixelGroup->GetOffsetXIndex(i, &indexB, blurRangeB);

        if (validR)
            colorBuffer[i].R = pixelColors[indexR].R;
        else
            colorBuffer[i].R = 0;

        if (validG)
            colorBuffer[i].G = pixelColors[indexG].G;
        else
            colorBuffer[i].G = 0;

        if (validB)
            colorBuffer[i].B = pixelColors[indexB].B;
        else
            colorBuffer[i].B = 0;
    }

    for (uint16_t i = 0; i < pixelGroup->GetPixelCount(); i++) {
        pixelColors[i].R = colorBuffer[i].R;
        pixelColors[i].G = colorBuffer[i].G;
        pixelColors[i].B = colorBuffer[i].B;
    }
}
