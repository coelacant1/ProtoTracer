#include "DirectionAngle.h"
#include "Mathematics.h"

// Constructor with individual components.
DirectionAngle::DirectionAngle(float rotation, float x, float y, float z) 
    : Rotation(rotation), Direction(x, y, z) {}

// Constructor with Vector3D.
DirectionAngle::DirectionAngle(float rotation, Vector3D direction) 
    : Rotation(rotation), Direction(direction) {}

// Convert DirectionAngle to a string representation.
String DirectionAngle::ToString() {
    String r = Mathematics::DoubleToCleanString(Rotation);
    String x = Mathematics::DoubleToCleanString(Direction.X);
    String y = Mathematics::DoubleToCleanString(Direction.Y);
    String z = Mathematics::DoubleToCleanString(Direction.Z);

    return r + ": [" + x + " " + y + " " + z + "]";
}
