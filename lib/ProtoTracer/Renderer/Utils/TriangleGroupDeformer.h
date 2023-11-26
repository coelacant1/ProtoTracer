#pragma once

#include "TriangleGroup.h"

class TriangleGroupDeformer {
public:
    enum Axis {
        XAxis,
        YAxis,
        ZAxis
    };

private:
    TriangleGroup** objects;
    int objectCount = 0;

    bool CheckClipAxis(Vector3D base, bool positive, Axis valueCheckAxis);

public:
    TriangleGroupDeformer(TriangleGroup* object);
    TriangleGroupDeformer(TriangleGroup** objects, int objectCount);

    void SinusoidalDeform(float magnitude, float timeRatio, float periodModifier, float frequencyModifier, Axis axis);
    void DropwaveDeform(float magnitude, float timeRatio, float periodModifier, float frequencyModifier, Axis axis);
    void SineWaveSurfaceDeform(Vector3D offset, float magnitude, float timeRatio, float periodModifier, float frequencyModifier, Axis axis);
    void CosineInterpolationDeformer(float* pointMultiplier, int points, float scale, float minAxis, float maxAxis, Axis selectionAxis, Axis deformAxis);
    void AxisZeroClipping(bool positive, Axis clipAxis, Axis valueCheckAxis);
};
