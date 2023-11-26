#include "Fisheye.h"

Fisheye::Fisheye(float amplitude) : amplitude(amplitude) {}

void Fisheye::SetPosition(Vector2D offset) {
    this->offset = offset;
}

void Fisheye::SetAmplitude(float amplitude) {
    this->amplitude = amplitude;
}

void Fisheye::ApplyEffect(IPixelGroup* pixelGroup) {
    RGBColor* pixelColors = pixelGroup->GetColors();
    RGBColor* colorBuffer = pixelGroup->GetColorBuffer();
    Vector2D mid = pixelGroup->GetCenterCoordinate();
    float halfWidth = 48.0f; // fGenSize.Update();
    unsigned int tIndex = 0;

    amplitude = fGenWarp.Update() * ratio;

    offset.X = fGenX.Update() * ratio;
    offset.Y = fGenY.Update() * ratio;

    for (unsigned int i = 0; i < pixelGroup->GetPixelCount(); i++) {
        Vector2D pos = pixelGroup->GetCoordinate(i) + offset;
        Vector2D dif = pos - mid;
        float distance = fabsf(pos.CalculateEuclideanDistance(mid));

        float r = distance / halfWidth;
        float theta = atan2(dif.Y, dif.X);
        float newDistance = powf(r, amplitude);

        int offsetX = (int)(newDistance * cosf(theta));
        int offsetY = (int)(newDistance * sinf(theta));

        // Use this function to find the index of the pixel at the offset x y pixel
        if (pixelGroup->GetOffsetXYIndex(i, &tIndex, offsetX, offsetY)) {
            colorBuffer[i].R = pixelColors[tIndex].R; // copy the current pixel color into the buffer
            colorBuffer[i].G = pixelColors[tIndex].G;
            colorBuffer[i].B = pixelColors[tIndex].B;
        } else {
            colorBuffer[i].R = 0; // copy the current pixel color into the buffer
            colorBuffer[i].G = 0;
            colorBuffer[i].B = 0;
        }
    }

    for (unsigned int i = 0; i < pixelGroup->GetPixelCount(); i++) {
        pixelColors[i].R = colorBuffer[i].R;
        pixelColors[i].G = colorBuffer[i].G;
        pixelColors[i].B = colorBuffer[i].B;
    }
}
