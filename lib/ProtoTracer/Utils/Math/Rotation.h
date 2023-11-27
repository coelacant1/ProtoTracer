#pragma once

#include "AxisAngle.h"
#include "DirectionAngle.h"
#include "EulerAngles.h"
#include "EulerConstants.h"
#include "Quaternion.h"
#include "RotationMatrix.h"
#include "Vector3D.h"
#include "YawPitchRoll.h"

class Rotation {
private:
    Quaternion quaternionRotation;

    Quaternion AxisAngleToQuaternion(const AxisAngle& axisAngle);
    Quaternion DirectionAngleToQuaternion(const DirectionAngle& directionAngle);
    Quaternion RotationMatrixToQuaternion(const RotationMatrix& rM);
    Quaternion RotationMatrixToQuaternion(const Vector3D& X, const Vector3D& Y, const Vector3D& Z);
    Quaternion EulerAnglesToQuaternion(const EulerAngles& eulerAngles);
    Quaternion YawPitchRollToQuaternion(const YawPitchRoll& ypr);
    EulerAngles RotationMatrixToEulerAngles(const RotationMatrix& rM, const EulerOrder& order);
    RotationMatrix EulerAnglesToRotationMatrix(const EulerAngles& eulerAngles);
    Quaternion QuaternionFromDirectionVectors(const Vector3D& initial, const Vector3D& target);

public:
    Rotation();
    Rotation(const Quaternion& quaternion);
    Rotation(const AxisAngle& axisAngle);
    Rotation(const DirectionAngle& directionAngle);
    Rotation(const RotationMatrix& rotationMatrix);
    Rotation(const Vector3D& X, const Vector3D& Y, const Vector3D& Z);
    Rotation(const EulerAngles& eulerAngles);
    Rotation(const Vector3D& initial, const Vector3D& target);
    Rotation(const YawPitchRoll& ypr);

    Quaternion GetQuaternion();
    AxisAngle GetAxisAngle();
    DirectionAngle GetDirectionAngle();
    RotationMatrix GetRotationMatrix();
    EulerAngles GetEulerAngles(const EulerOrder& order);
    YawPitchRoll GetYawPitchRoll();
};
