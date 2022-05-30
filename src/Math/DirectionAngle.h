#pragma once

#include "Vector3D.h"

class DirectionAngle {
public:
	float Rotation;
	Vector3D Direction;

	DirectionAngle(float rotation, float x, float y, float z) {
		Rotation = rotation;
		Direction = Vector3D(x, y, z);
	}

	DirectionAngle(float rotation, Vector3D direction) {
		Rotation = rotation;
		Direction = direction;
	}

	String ToString() {
		String r = Mathematics::DoubleToCleanString(Rotation);
		String x = Mathematics::DoubleToCleanString(Direction.X);
		String y = Mathematics::DoubleToCleanString(Direction.Y);
		String z = Mathematics::DoubleToCleanString(Direction.Z);

		return r + ": [" + x + " " + y + " " + z + "]";
	}
};
