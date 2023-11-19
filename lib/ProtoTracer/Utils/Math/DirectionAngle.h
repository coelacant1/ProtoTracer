#pragma once

#include "Vector3D.h"

class DirectionAngle {
public:
    float Rotation;
    Vector3D Direction;

    // Constructor with individual components.
    DirectionAngle(float rotation, float x, float y, float z);

    // Constructor with Vector3D.
    DirectionAngle(float rotation, Vector3D direction);

    // Method to convert DirectionAngle to a string representation.
    String ToString();
};
