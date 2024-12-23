/**
 * @file FFTFilter.h
 * @brief Provides the `FFTFilter` class for processing and normalizing FFT data.
 *
 * The `FFTFilter` applies a smoothing filter to FFT data and normalizes the output
 * to constrain the values within a specified range.
 *
 * @date 22/12/2024
 * @version 1.0
 * @author Coela Can't
 */

#pragma once

#include "RunningAverageFilter.h" ///< Includes the running average filter utility.
#include "../Math/Mathematics.h" ///< Includes mathematical utilities for constraints and operations.

/**
 * @class FFTFilter
 * @brief Processes and normalizes FFT data.
 *
 * The `FFTFilter` applies a running average filter to FFT input values, removes
 * a baseline minimum value, and normalizes the output for stability and usability
 * in other FFT-based functionalities.
 */
class FFTFilter {
private:
    RunningAverageFilter<20> minKF = RunningAverageFilter<20>(0.05f); ///< Running average filter for baseline normalization.
    float outputValue = 0.0f; ///< Stores the most recent filtered output value.

public:
    /**
     * @brief Constructs an `FFTFilter` instance with default configurations.
     */
    FFTFilter();

    /**
     * @brief Retrieves the current filtered and normalized output value.
     * 
     * @return The most recent filtered output value.
     */
    float GetOutput();

    /**
     * @brief Filters and normalizes the input value for FFT data processing.
     *
     * @param value The current FFT input value.
     * @return The filtered and normalized FFT value.
     */
    float Filter(float value);
};
