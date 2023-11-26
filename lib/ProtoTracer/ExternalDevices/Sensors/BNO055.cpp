#include "BNO055.h"

BNO055::BNO055() {
    previousMicros = micros();

    pinMode(18, INPUT_PULLUP);
    pinMode(19, INPUT_PULLUP);

    Wire.setClock(100000);
    if (!bno.begin()) {
        Serial.println("No BNO055 detected");
    } else {
        Serial.println("BNO055 was detected");
    }

    delay(1000);

    bno.setExtCrystalUse(true);
}

Vector3D BNO055::ReadMagneticField() {
    bno.getEvent(&magnetometerData, Adafruit_BNO055::VECTOR_MAGNETOMETER);
    return Vector3D(magnetometerData.magnetic.x, magnetometerData.magnetic.y, magnetometerData.magnetic.z);
}

Vector3D BNO055::ReadLocalAcceleration() {
    bno.getEvent(&accelerometerData, Adafruit_BNO055::VECTOR_ACCELEROMETER);
    return Vector3D(accelerometerData.acceleration.x, accelerometerData.acceleration.y, accelerometerData.acceleration.z);
}

Vector3D BNO055::ReadLocalAngularVelocity() {
    bno.getEvent(&angVelocityData, Adafruit_BNO055::VECTOR_GYROSCOPE);
    return Vector3D(angVelocityData.gyro.x, angVelocityData.gyro.y, angVelocityData.gyro.z);
}

Vector3D BNO055::ReadLocalGravityVector() {
    bno.getEvent(&gravityData, Adafruit_BNO055::VECTOR_GRAVITY);
    return Vector3D(gravityData.acceleration.x, gravityData.acceleration.y, gravityData.acceleration.z);
}

void BNO055::Update() {
    float dT = ((float)micros() - (float)previousMicros) / 1000000.0f;

    Vector3D orthogonal = GetLocalMagneticField().CrossProduct(localForce);
    Vector3D orthoGravity = orthogonal.CrossProduct(localForce); // use for absolute yaw position

    // use orthogonal for X axis -> east/west
    // use orthogravity for Y axis -> north/south
    // use gravity vector for Z axis -> up/down
    Quaternion magForceQ = Rotation(orthogonal.UnitSphere(), orthoGravity.UnitSphere(), localForce.UnitSphere()).GetQuaternion().UnitQuaternion();

    // complementary filter join both the gyro integration to angular position with the absolute orientation from mag and force
    absoluteOrientation = Quaternion::SphericalInterpolation(absoluteOrientation.DeltaRotation(localAngularVelocity, dT), magForceQ, 0.05f);

    localAcceleration = localForce - localGraviKF.Filter(localGravityVector);

    previousMicros = micros();
}

Vector3D BNO055::GetLocalMagneticField() {
    return localMagneticField;
}

Vector3D BNO055::GetLocalForce() {
    return localForce;
}

Vector3D BNO055::GetLocalAccelerationFiltered() {
    return localAccelKF.Filter(localAcceleration);
}

Vector3D BNO055::GetLocalAngularVelocityFiltered() {
    return localAngulKF.Filter(localAngularVelocity);
}

Vector3D BNO055::GetLocalAcceleration() {
    return localAcceleration;
}

Vector3D BNO055::GetLocalAngularVelocity() {
    return localAngularVelocity;
}

Quaternion BNO055::GetAbsoluteOrientation() {
    return absoluteOrientation;
}
