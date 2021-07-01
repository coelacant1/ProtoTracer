#pragma once

#include "Mathematics.h"
#include "Vector3D.h"

typedef struct AxisAngle {
public:
	float Rotation;
	Vector3D Axis;

	AxisAngle(float rotation, float x, float y, float z);
	AxisAngle(float rotation, Vector3D axis);

	String ToString();
} AxisAngle;
