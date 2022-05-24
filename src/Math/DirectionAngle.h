#pragma once

#include "Vector3D.h"

typedef struct DirectionAngle {
public:
    float Rotation;
    Vector3D Direction;

    DirectionAngle(const float rotation, const float x, const float y, const float z)
        : Rotation(rotation),
          Direction(Vector3D(x, y, z)) {}

    DirectionAngle(const float rotation, const Vector3D &direction)
        : Rotation(rotation),
          Direction(direction) {}

    String ToString() const {
        const String r = Mathematics::DoubleToCleanString(Rotation);
        const String x = Mathematics::DoubleToCleanString(Direction.X);
        const String y = Mathematics::DoubleToCleanString(Direction.Y);
        const String z = Mathematics::DoubleToCleanString(Direction.Z);

        return r + ": [" + x + " " + y + " " + z + "]";
    }
} DirectionAngle;
