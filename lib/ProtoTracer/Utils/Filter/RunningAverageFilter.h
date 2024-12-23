/**
 * @file RunningAverageFilter.h
 * @brief Implements a running average filter for smoothing data.
 *
 * The `RunningAverageFilter` class uses a specified memory size to smooth
 * incoming data values over time, providing a low-pass filtering effect.
 *
 * @date 22/12/2024
 * @version 1.0
 * @author Coela Can't
 */

#pragma once

#include "../Math/Mathematics.h"

/**
 * @class RunningAverageFilter
 * @brief Smooths data values using a weighted running average.
 *
 * The `RunningAverageFilter` class calculates a running average based on
 * a fixed memory size, applying a gain to control the influence of new values.
 *
 * @tparam memory The size of the memory buffer for storing recent values.
 */
template <size_t memory>
class RunningAverageFilter {
private:
    float gain; ///< The gain factor for the filter, controlling smoothing intensity.
    float values[memory]; ///< Buffer to store the recent values.
    uint8_t currentAmount; ///< The current number of valid entries in the buffer.

public:
    /**
     * @brief Default constructor for `RunningAverageFilter`.
     *
     * Initializes the filter with default parameters and a memory buffer of zeros.
     */
    RunningAverageFilter();

    /**
     * @brief Constructs a `RunningAverageFilter` with a specified gain.
     *
     * @param gain The gain factor for the filter (typically between 0.0 and 1.0).
     */
    RunningAverageFilter(float gain);

    /**
     * @brief Sets the gain for the filter.
     *
     * @param gain The new gain value, controlling smoothing intensity.
     */
    void SetGain(float gain);

    /**
     * @brief Filters the input value using the running average.
     *
     * Calculates the smoothed output based on the memory buffer and gain.
     *
     * @param value The new input value to filter.
     * @return The filtered output value.
     */
    float Filter(float value);
};

#include "RunningAverageFilter.tpp"
