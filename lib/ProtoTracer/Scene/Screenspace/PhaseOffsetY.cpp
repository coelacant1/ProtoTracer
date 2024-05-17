#include "PhaseOffsetY.h"
#include "../../Utils/Math/Mathematics.h"

PhaseOffsetY::PhaseOffsetY(uint8_t pixels) : pixels(pixels) {}

void PhaseOffsetY::ApplyEffect(IPixelGroup* pixelGroup) {
    if (ratio <= 0.001f) return;

    RGBColor* pixelColors = pixelGroup->GetColors();

    for (uint16_t i = 0; i < pixelGroup->GetPixelCount(); i++) {
        float range = (pixels - 1) * ratio + 1;
        float coordX = pixelGroup->GetCoordinate(i).X / 10.0f;
        float mpiR = 2.0f * Mathematics::MPI * fGenPhase.Update();
        float sineR = sinf(coordX + mpiR * 8.0f);
        float sineG = sinf(coordX + mpiR * 8.0f + 2.0f * Mathematics::MPI * 0.333f);
        float sineB = sinf(coordX + mpiR * 8.0f + 2.0f * Mathematics::MPI * 0.666f);

        uint8_t blurRangeR = Mathematics::Constrain(uint8_t(Mathematics::Map(sineR, -1.0f, 1.0f, 1.0f, range)), uint8_t(1), uint8_t(range));
        uint8_t blurRangeG = Mathematics::Constrain(uint8_t(Mathematics::Map(sineG, -1.0f, 1.0f, 1.0f, range)), uint8_t(1), uint8_t(range));
        uint8_t blurRangeB = Mathematics::Constrain(uint8_t(Mathematics::Map(sineB, -1.0f, 1.0f, 1.0f, range)), uint8_t(1), uint8_t(range));

        uint16_t indexR = 0, indexG = 0, indexB = 0;

        bool validR = pixelGroup->GetOffsetYIndex(i, &indexR, blurRangeR);
        bool validG = pixelGroup->GetOffsetYIndex(i, &indexG, blurRangeG);
        bool validB = pixelGroup->GetOffsetYIndex(i, &indexB, blurRangeB);

        if (validR)
            pixelColors[i].R = pixelColors[indexR].R;
        else
            pixelColors[i].R = 0;

        if (validG)
            pixelColors[i].G = pixelColors[indexG].G;
        else
            pixelColors[i].G = 0;

        if (validB)
            pixelColors[i].B = pixelColors[indexB].B;
        else
            pixelColors[i].B = 0;
    }
}
