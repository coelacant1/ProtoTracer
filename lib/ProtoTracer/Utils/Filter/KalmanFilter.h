/**
 * @file KalmanFilter.h
 * @brief Provides a template-based implementation of a Kalman Filter.
 *
 * The Kalman Filter is used for estimating the state of a system in the presence
 * of noise. It is widely used in signal processing, control systems, and navigation.
 *
 * @date 22/12/2024
 * @version 1.0
 * @author Coela Can't
 */

#pragma once

/**
 * @class KalmanFilter
 * @brief Implements a generic Kalman Filter for 1D data.
 *
 * This class provides a template-based implementation of a Kalman Filter
 * for filtering noisy data. It estimates the true value by accounting for
 * process noise and sensor noise.
 *
 * @tparam T The numeric type for the filter (e.g., `float`, `double`).
 */
template<typename T>
class KalmanFilter {
private:
    T processNoise; ///< The process noise variance.
    T sensorNoise; ///< The sensor noise variance.
    T estimation; ///< The current estimation of the value.
    T errorCovariance; ///< The error covariance of the estimation.

public:
    /**
     * @brief Constructs a `KalmanFilter` with specified noise parameters.
     *
     * @param processNoise The process noise variance.
     * @param sensorNoise The sensor noise variance.
     * @param errorCovariance The initial error covariance.
     */
    KalmanFilter(T processNoise, T sensorNoise, T errorCovariance);

    /**
     * @brief Filters the given input value using the Kalman Filter algorithm.
     *
     * @param value The noisy input value to be filtered.
     * @return The filtered estimate of the value.
     */
    T Filter(T value);
};

#include "KalmanFilter.tpp" ///< Includes the implementation of the template.
