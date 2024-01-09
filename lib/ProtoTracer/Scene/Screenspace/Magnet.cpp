#include "Magnet.h"

Magnet::Magnet(float amplitude) : amplitude(amplitude) {}

void Magnet::SetPosition(Vector2D offset) {
    this->offset = offset;
}

void Magnet::SetAmplitude(float amplitude) {
    this->amplitude = amplitude;
}

void Magnet::ApplyEffect(IPixelGroup* pixelGroup) {
    RGBColor* pixelColors = pixelGroup->GetColors();
    RGBColor* colorBuffer = pixelGroup->GetColorBuffer();
    Vector2D mid = pixelGroup->GetCenterCoordinate();
    uint16_t tIndex = 0;

    for (uint16_t i = 0; i < pixelGroup->GetPixelCount(); i++) {
        Vector2D pos = pixelGroup->GetCoordinate(i) + offset;
        Vector2D dif = pos - mid + Vector2D(0.0f, 50.0f);
        float distance = fabsf(pos.CalculateEuclideanDistance(mid));

        float theta = atan2f(dif.Y, dif.X);
        float newDistance = (1.0f / distance) * 0.5f * amplitude * 4.0f; // * 10000.0f;//fGenSize.Update();

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

    for (uint16_t i = 0; i < pixelGroup->GetPixelCount(); i++) {
        pixelColors[i].R = colorBuffer[i].R;
        pixelColors[i].G = colorBuffer[i].G;
        pixelColors[i].B = colorBuffer[i].B;
    }
}
