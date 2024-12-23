/**
 * @file BNO055.h
 * @brief A class for interfacing with the Adafruit BNO055 sensor.
 *
 * This file defines the BNO055 class, which provides methods for retrieving and processing sensor data
 * such as acceleration, angular velocity, magnetic field, gravity vector, and absolute orientation.
 *
 * @date 22/12/2024
 * @author Coela Can't
 */

#pragma once

#include <Wire.h> ///< Include for I2C communication.
#include <Adafruit_Sensor.h> ///< Include for Adafruit sensor base class.
#include <Adafruit_BNO055.h> ///< Include for Adafruit BNO055 sensor library.
#include <utility/imumaths.h> ///< Include for mathematical utilities for IMU sensors.
#include "../../Utils/Filter/QuaternionKalmanFilter.h" ///< Include for quaternion filtering.
#include "../../Utils/Filter/VectorRunningAverageFilter.h" ///< Include for vector filtering.
#include "../../Utils/Math/Rotation.h" ///< Include for rotation mathematics.

/**
 * @class BNO055
 * @brief A class for managing the Adafruit BNO055 sensor.
 *
 * The BNO055 class provides methods for retrieving processed sensor data, including acceleration,
 * angular velocity, magnetic field, gravity vector, and absolute orientation. It uses filters
 * to smooth the data for improved reliability.
 */
class BNO055 {
private:
    sensors_event_t angVelocityData, magnetometerData, accelerometerData, gravityData; ///< Sensor event data.
    Adafruit_BNO055 bno = Adafruit_BNO055(55, 0x28); ///< BNO055 sensor instance.
    Vector3D localForce; ///< Computed local force.
    Vector3D localAcceleration; ///< Raw local acceleration data.
    Vector3D localMagneticField; ///< Raw local magnetic field data.
    Vector3D localAngularVelocity; ///< Raw local angular velocity data.
    Vector3D localGravityVector; ///< Raw local gravity vector data.
    Vector3D previousLocalAngularVelocity; ///< Previous angular velocity for filtering.
    Quaternion absoluteOrientation; ///< Computed absolute orientation.
    long previousMicros; ///< Timestamp of the previous sensor update.

    VectorRunningAverageFilter<10> localAngulKF = VectorRunningAverageFilter<10>(0.1f); ///< Filter for angular velocity.
    VectorRunningAverageFilter<10> localAccelKF = VectorRunningAverageFilter<10>(0.1f); ///< Filter for acceleration.
    VectorRunningAverageFilter<10> localGraviKF = VectorRunningAverageFilter<10>(0.1f); ///< Filter for gravity vector.

    /**
     * @brief Reads the magnetic field vector from the sensor.
     *
     * @return A Vector3D representing the magnetic field.
     */
    Vector3D ReadMagneticField();

    /**
     * @brief Reads the local acceleration vector from the sensor.
     *
     * @return A Vector3D representing the local acceleration.
     */
    Vector3D ReadLocalAcceleration();

    /**
     * @brief Reads the local angular velocity vector from the sensor.
     *
     * @return A Vector3D representing the local angular velocity.
     */
    Vector3D ReadLocalAngularVelocity();

    /**
     * @brief Reads the local gravity vector from the sensor.
     *
     * @return A Vector3D representing the local gravity vector.
     */
    Vector3D ReadLocalGravityVector();

public:
    /**
     * @brief Constructs a BNO055 instance.
     */
    BNO055();

    /**
     * @brief Updates the sensor data and applies filtering.
     */
    void Update();

    /**
     * @brief Retrieves the local magnetic field vector.
     *
     * @return A Vector3D representing the magnetic field.
     */
    Vector3D GetLocalMagneticField();

    /**
     * @brief Retrieves the computed local force vector.
     *
     * @return A Vector3D representing the local force.
     */
    Vector3D GetLocalForce();

    /**
     * @brief Retrieves the filtered local acceleration vector.
     *
     * @return A Vector3D representing the filtered local acceleration.
     */
    Vector3D GetLocalAccelerationFiltered();

    /**
     * @brief Retrieves the filtered local angular velocity vector.
     *
     * @return A Vector3D representing the filtered local angular velocity.
     */
    Vector3D GetLocalAngularVelocityFiltered();

    /**
     * @brief Retrieves the raw local acceleration vector.
     *
     * @return A Vector3D representing the raw local acceleration.
     */
    Vector3D GetLocalAcceleration();

    /**
     * @brief Retrieves the raw local angular velocity vector.
     *
     * @return A Vector3D representing the raw local angular velocity.
     */
    Vector3D GetLocalAngularVelocity();

    /**
     * @brief Retrieves the absolute orientation as a quaternion.
     *
     * @return A Quaternion representing the absolute orientation.
     */
    Quaternion GetAbsoluteOrientation();
};
