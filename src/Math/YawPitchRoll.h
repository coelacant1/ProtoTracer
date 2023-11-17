#pragma once

#include "Vector3D.h"

class YawPitchRoll {
public:
    float Yaw;
    float Pitch;
    float Roll;

    YawPitchRoll();
    YawPitchRoll(Vector3D vector);
    YawPitchRoll(const YawPitchRoll& ypr);
    YawPitchRoll(float yaw, float pitch, float roll);

    String ToString() const;
};
