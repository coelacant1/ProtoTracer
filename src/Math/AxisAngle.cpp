#include "AxisAngle.h"

AxisAngle::AxisAngle(float rotation, float x, float y, float z) {
	Rotation = rotation;
	Axis = Vector3D(x, y, z);
}

AxisAngle::AxisAngle(float rotation, Vector3D axis) {
	Rotation = rotation;
	Axis = axis;
}

String AxisAngle::ToString() {
	String r = Mathematics::DoubleToCleanString(Rotation);
	String x = Mathematics::DoubleToCleanString(Axis.X);
	String y = Mathematics::DoubleToCleanString(Axis.Y);
	String z = Mathematics::DoubleToCleanString(Axis.Z);

	return r + ": [" + x + " " + y + " " + z + "]";
}
