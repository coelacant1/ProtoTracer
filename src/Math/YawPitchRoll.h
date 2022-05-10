#pragma once

#include "Vector3D.h"

typedef struct YawPitchRoll {
private:
public:
    float Yaw = 0.0f;
    float Pitch = 0.0f;
    float Roll = 0.0f;

    YawPitchRoll() {}
    YawPitchRoll(const Vector3D& vector)
		: Yaw(vector.X),
		  Pitch(vector.Y),
		  Roll(vector.Z) {}
    YawPitchRoll(const YawPitchRoll &ypr) 
		: Yaw(ypr.Yaw),
		  Pitch(ypr.Pitch),
		  Roll(ypr.Roll) {}
    YawPitchRoll(const float yaw, const float pitch, const float roll) 
		: Yaw(yaw),
		  Pitch(pitch),
		  Roll(roll) {}

    String ToString() const {
        const String y = Mathematics::DoubleToCleanString(this->Yaw);
        const String p = Mathematics::DoubleToCleanString(this->Pitch);
        const String r = Mathematics::DoubleToCleanString(this->Roll);

        return "[" + y + ", " + p + ", " + r + "]";
    }
} YawPitchRoll;
