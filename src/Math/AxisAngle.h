#pragma once

#include "Mathematics.h"
#include "Vector3D.h"

typedef struct AxisAngle {
public:
	float Rotation;
	Vector3D Axis;

	AxisAngle(const float rotation, const float x, const float y, const float z) 
		: Rotation(rotation),
		  Axis(Vector3D(x, y, z)){}

	AxisAngle(const float rotation, const Vector3D axis)
		: Rotation(rotation),
		  Axis(axis) {}

	String ToString() const {
		String r = Mathematics::DoubleToCleanString(Rotation);
		String x = Mathematics::DoubleToCleanString(Axis.X);
		String y = Mathematics::DoubleToCleanString(Axis.Y);
		String z = Mathematics::DoubleToCleanString(Axis.Z);

		return r + ": [" + x + " " + y + " " + z + "]";
	}
} AxisAngle;
