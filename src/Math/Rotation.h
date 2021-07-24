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
	Quaternion QuaternionRotation;

	Quaternion AxisAngleToQuaternion(AxisAngle axisAngle);
	Quaternion DirectionAngleToQuaternion(DirectionAngle directionAngle);
	Quaternion RotationMatrixToQuaternion(RotationMatrix rotationMatrix);
  	Quaternion RotationMatrixToQuaternion(Vector3D X, Vector3D Y, Vector3D Z);
	Quaternion EulerAnglesToQuaternion(EulerAngles eulerAngles);
	EulerAngles RotationMatrixToEulerAngles(RotationMatrix rM, EulerOrder order);
	RotationMatrix EulerAnglesToRotationMatrix(EulerAngles eulerAngles);
	Quaternion QuaternionFromDirectionVectors(Vector3D initial, Vector3D target);
	Quaternion YawPitchRollToQuaternion(YawPitchRoll ypr);

public:
	Rotation();
	Rotation(Quaternion quaternion);
	Rotation(AxisAngle axisAngle);
	Rotation(DirectionAngle directionAngle);
	Rotation(RotationMatrix rotationMatrix);
  	Rotation(Vector3D X, Vector3D Y, Vector3D Z);
	Rotation(EulerAngles eulerAngles);
	Rotation(Vector3D initial, Vector3D target);
	Rotation(YawPitchRoll ypr);

	Quaternion GetQuaternion();
	AxisAngle GetAxisAngle();
	DirectionAngle GetDirectionAngle();
	RotationMatrix GetRotationMatrix();
	EulerAngles GetEulerAngles(EulerOrder order);
	YawPitchRoll GetYawPitchRoll();

};
