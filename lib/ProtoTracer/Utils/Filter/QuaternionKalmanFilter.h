/**
 * @file QuaternionKalmanFilter.h
 * @brief Implements a Kalman filter for smoothing quaternion data.
 *
 * The `QuaternionKalmanFilter` class provides a mechanism to smooth quaternion values
 * using a simple Kalman filter approach.
 *
 * @date 22/12/2024
 * @version 1.0
 * @author Coela Can't
 */

#pragma once

#include "../Math/Quaternion.h"

/**
 * @class QuaternionKalmanFilter
 * @brief A Kalman filter for quaternion smoothing.
 *
 * This class applies a Kalman filter to quaternion data to reduce noise and
 * smooth transitions between rotations.
 */
class QuaternionKalmanFilter {
private:
    float gain; ///< The filter gain, controls the weight of new data versus the estimated state.
    int memory; ///< The size of the internal buffer to store quaternion history.
    Quaternion* values; ///< Pointer to an array of quaternion values for the filter's memory.

    int currentAmount = 0; ///< Tracks the current number of quaternions stored in memory.

    /**
     * @brief Shifts the array to remove the oldest quaternion and make room for a new one.
     *
     * @param arr Array of quaternions to shift.
     * @return Pointer to the shifted array.
     */
    Quaternion* ShiftArray(Quaternion arr[]);

public:
    /**
     * @brief Default constructor for `QuaternionKalmanFilter`.
     *
     * Initializes the filter with default parameters.
     */
    QuaternionKalmanFilter();

    /**
     * @brief Constructs a `QuaternionKalmanFilter` with specified parameters.
     *
     * @param gain The filter gain.
     * @param memory The size of the filter's internal memory.
     */
    QuaternionKalmanFilter(float gain, int memory);

    /**
     * @brief Filters a quaternion value to reduce noise.
     *
     * @param value The new quaternion value to process.
     * @return The filtered quaternion.
     */
    Quaternion Filter(Quaternion value);

    /**
     * @brief Destructor for `QuaternionKalmanFilter`.
     *
     * Releases allocated memory for quaternion storage.
     */
    ~QuaternionKalmanFilter();
};
