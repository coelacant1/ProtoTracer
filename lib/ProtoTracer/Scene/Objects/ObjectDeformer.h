#pragma once

#include "Object3D.h"

class ObjectDeformer {
public:
    enum Axis {
        XAxis,
        YAxis,
        ZAxis
    };

private:
    Object3D** objects;
    int objectCount = 0;

    bool CheckClipAxis(Vector3D base, bool positive, Axis valueCheckAxis);

public:
    ObjectDeformer(Object3D* object);
    ObjectDeformer(Object3D** objects, int objectCount);

    void PerspectiveDeform(float scaleRatio, Vector3D center, Axis axis);
    void SinusoidalDeform(float magnitude, float timeRatio, float periodModifier, float frequencyModifier, Axis axis);
    void DropwaveDeform(float magnitude, float timeRatio, float periodModifier, float frequencyModifier, Axis axis);
    void SineWaveSurfaceDeform(Vector3D offset, float magnitude, float timeRatio, float periodModifier, float frequencyModifier, Axis axis);
    void CosineInterpolationDeformer(float* pointMultiplier, int points, float scale, float minAxis, float maxAxis, Axis selectionAxis, Axis deformAxis);
    void AxisZeroClipping(bool positive, Axis clipAxis, Axis valueCheckAxis);
};
