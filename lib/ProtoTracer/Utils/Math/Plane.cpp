#include "Plane.h"
#include "Mathematics.h"

// Default constructor.
Plane::Plane() {}

// Parameterized constructor.
Plane::Plane(Vector3D centroid, Vector3D normal)
    : Centroid(centroid), Normal(normal) {}

// Convert Plane to a string representation.
String Plane::ToString() {
    String centroid = Centroid.ToString();
    String normal = Normal.ToString();

    return "[ " + centroid + ", " + normal + " ]";
}
