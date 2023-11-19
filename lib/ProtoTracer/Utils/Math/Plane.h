#pragma once

#include "Vector3D.h"

class Plane {
public:
    Vector3D Centroid;
    Vector3D Normal;

    // Default constructor.
    Plane();

    // Parameterized constructor.
    Plane(Vector3D centroid, Vector3D normal);

    // Convert Plane to a string representation.
    String ToString();
};
