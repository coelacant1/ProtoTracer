#pragma once

#include "..\Material.h"
#include "..\..\..\Utils\Math\Mathematics.h"
#include "GradientMaterial.h"

// Converts gif to RGB XY pixel matrix
class DepthMaterial : public Material {
public:
    enum Axis {
        X,
        Y,
        Z
    };

private:
    RGBColor spectrum[4] = { RGBColor(0, 255, 0), RGBColor(255, 0, 0), RGBColor(0, 255, 0), RGBColor(0, 0, 255) };
    GradientMaterial<4> gNoiseMat = GradientMaterial<4>(spectrum, 2.0f, false);
    Axis axis;
    float depth = 0.0f;
    float zOffset = 0.0f;

public:
    DepthMaterial(Axis axis, float depth, float zOffset);
    
    RGBColor GetRGB(const Vector3D& position, const Vector3D& normal, const Vector3D& uvw) override;
};
