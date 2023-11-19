#include "AxisAngle.h"
#include "Mathematics.h"

// Constructor with individual components.
AxisAngle::AxisAngle(float rotation, float x, float y, float z) : Rotation(rotation), Axis(x, y, z) {}

// Constructor with Vector3D.
AxisAngle::AxisAngle(float rotation, Vector3D axis) : Rotation(rotation), Axis(axis) {}

// Convert AxisAngle to a string representation.
String AxisAngle::ToString() {
    String r = Mathematics::DoubleToCleanString(Rotation);
    String x = Mathematics::DoubleToCleanString(Axis.X);
    String y = Mathematics::DoubleToCleanString(Axis.Y);
    String z = Mathematics::DoubleToCleanString(Axis.Z);

    return r + ": [" + x + " " + y + " " + z + "]";
}
