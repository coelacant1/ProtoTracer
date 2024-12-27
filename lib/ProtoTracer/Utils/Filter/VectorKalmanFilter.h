/**
 * @file VectorKalmanFilter.h
 * @brief Implements a Kalman filter for 3D vector smoothing.
 *
 * The `VectorKalmanFilter` class applies independent Kalman filters to each component (X, Y, Z)
 * of a 3D vector to smooth noisy data.
 *
 * @date 22/12/2024
 * @version 1.0
 * @author Coela Can't
 */

#pragma once

#include "KalmanFilter.h"
#include "../Math/Vector3D.h"

/**
 * @class VectorKalmanFilter
 * @brief Applies Kalman filtering independently to each component of a 3D vector.
 *
 * The `VectorKalmanFilter` class uses three `KalmanFilter` instances to process the
 * X, Y, and Z components of a `Vector3D`, providing a smooth output for noisy 3D data.
 *
 * @tparam T The numeric type used for calculations (e.g., `float` or `double`).
 */
template <typename T>
class VectorKalmanFilter {
private:
    KalmanFilter<T> X; ///< Kalman filter for the X component of the vector.
    KalmanFilter<T> Y; ///< Kalman filter for the Y component of the vector.
    KalmanFilter<T> Z; ///< Kalman filter for the Z component of the vector.

public:
    /**
     * @brief Constructs a `VectorKalmanFilter` with specified parameters.
     *
     * Initializes the Kalman filters for each component with the given process noise,
     * sensor noise, and error covariance.
     *
     * @param processNoise The process noise for the Kalman filter.
     * @param sensorNoise The sensor noise for the Kalman filter.
     * @param errorCovariance The initial error covariance for the Kalman filter.
     */
    VectorKalmanFilter(T processNoise, T sensorNoise, T errorCovariance);

    /**
     * @brief Filters a 3D vector input using the Kalman filter.
     *
     * Applies Kalman filtering independently to the X, Y, and Z components of the input vector.
     *
     * @param input The input `Vector3D` to filter.
     * @return The filtered `Vector3D`.
     */
    Vector3D Filter(Vector3D input);
};
