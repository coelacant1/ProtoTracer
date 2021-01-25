#pragma once

#include "Vector3D.h"

typedef struct DirectionAngle {
public:
	float Rotation;
	Vector3D Direction;

	DirectionAngle(float rotation, float x, float y, float z);
	DirectionAngle(float rotation, Vector3D direction);

	String ToString();
} DirectionAngle;
