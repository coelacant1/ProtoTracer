#pragma once

#include "EulerOrder.h"
#include "Vector3D.h"

class EulerAngles {
public:
    Vector3D Angles;
    EulerOrder Order;

    // Default constructor.
    EulerAngles();

    // Constructor with angles and order.
    EulerAngles(Vector3D angles, EulerOrder order);

    // Method to convert EulerAngles to a string representation.
    String ToString();
};
