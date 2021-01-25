#include "DirectionAngle.h"

DirectionAngle::DirectionAngle(float rotation, float x, float y, float z) {
	Rotation = rotation;
	Direction = Vector3D(x, y, z);
}

DirectionAngle::DirectionAngle(float rotation, Vector3D direction) {
	Rotation = rotation;
	Direction = direction;
}

String DirectionAngle::ToString() {
	String r = Mathematics::DoubleToCleanString(Rotation);
	String x = Mathematics::DoubleToCleanString(Direction.X);
	String y = Mathematics::DoubleToCleanString(Direction.Y);
	String z = Mathematics::DoubleToCleanString(Direction.Z);

	return r + ": [" + x + " " + y + " " + z + "]";
}
