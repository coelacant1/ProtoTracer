#pragma once

#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>
#include "..\..\Utils\Filter\QuaternionKalmanFilter.h"
#include "..\..\Utils\Filter\VectorRunningAverageFilter.h"
#include "..\..\Utils\Math\Rotation.h"

class BNO055 {
private:
    sensors_event_t angVelocityData, magnetometerData, accelerometerData, gravityData;
    Adafruit_BNO055 bno = Adafruit_BNO055(55, 0x28);
    Vector3D localForce;
    Vector3D localAcceleration;
    Vector3D localMagneticField;
    Vector3D localAngularVelocity;
    Vector3D localGravityVector;
    Vector3D previousLocalAngularVelocity;
    Quaternion absoluteOrientation;
    long previousMicros;

    VectorRunningAverageFilter<10> localAngulKF = VectorRunningAverageFilter<10>(0.1f);
    VectorRunningAverageFilter<10> localAccelKF = VectorRunningAverageFilter<10>(0.1f);
    VectorRunningAverageFilter<10> localGraviKF = VectorRunningAverageFilter<10>(0.1f);

    Vector3D ReadMagneticField();
    Vector3D ReadLocalAcceleration();
    Vector3D ReadLocalAngularVelocity();
    Vector3D ReadLocalGravityVector();

public:
    BNO055();
    void Update();
    Vector3D GetLocalMagneticField();
    Vector3D GetLocalForce();
    Vector3D GetLocalAccelerationFiltered();
    Vector3D GetLocalAngularVelocityFiltered();
    Vector3D GetLocalAcceleration();
    Vector3D GetLocalAngularVelocity();
    Quaternion GetAbsoluteOrientation();
};
