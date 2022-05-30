#pragma once

#include "Vector3D.h"

class YawPitchRoll {
public:
	float Yaw = 0.0f;
	float Pitch = 0.0f;
	float Roll = 0.0f;

	YawPitchRoll() {
		this->Yaw = 0.0;
		this->Pitch = 0.0;
		this->Roll = 0.0;
	}

	YawPitchRoll(Vector3D vector) {
		this->Yaw = vector.X;
		this->Pitch = vector.Y;
		this->Roll = vector.Z;
	}

	YawPitchRoll(const YawPitchRoll& ypr) {
		this->Yaw = ypr.Yaw;
		this->Pitch = ypr.Pitch;
		this->Roll = ypr.Roll;
	}

	YawPitchRoll(float yaw, float pitch, float roll) {
		this->Yaw = yaw;
		this->Pitch = pitch;
		this->Roll = roll;
	}

	String ToString() {
		String y = Mathematics::DoubleToCleanString(this->Yaw);
		String p = Mathematics::DoubleToCleanString(this->Pitch);
		String r = Mathematics::DoubleToCleanString(this->Roll);

		return "[" + y + ", " + p + ", " + r + "]";
	}

};
