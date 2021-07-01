#pragma once

#include "Vector3D.h"

typedef struct YawPitchRoll {
private:

public:
	float Yaw = 0.0f;
	float Pitch = 0.0f;
	float Roll = 0.0f;

	YawPitchRoll();
	YawPitchRoll(Vector3D vector);
	YawPitchRoll(const YawPitchRoll& ypr);
	YawPitchRoll(float yaw, float pitch, float roll);

	String ToString();
} YawPitchRoll;
