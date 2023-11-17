#pragma once

#include "Vector3D.h"

class AxisAngle {
public:
    float Rotation;
    Vector3D Axis;

    // Constructor with individual components.
    AxisAngle(float rotation, float x, float y, float z);

    // Constructor with Vector3D.
    AxisAngle(float rotation, Vector3D axis);

    // Method to convert AxisAngle to a string representation.
    String ToString();
};
