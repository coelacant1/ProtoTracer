/**
 * @file DerivativeFilter.h
 * @brief Provides a `DerivativeFilter` class for calculating the rate of change of input values.
 *
 * The `DerivativeFilter` combines a running average filter and a minimum filter to normalize
 * and constrain the derivative values, ensuring stability and noise reduction.
 *
 * @date 22/12/2024
 * @version 1.0
 * @author Coela Can't
 */

#pragma once

#include "RunningAverageFilter.h" ///< Includes the running average filter utility.
#include "MinFilter.h" ///< Includes the minimum filter utility.
#include "../Math/Mathematics.h" ///< Includes mathematical utilities for constraints and operations.

/**
 * @class DerivativeFilter
 * @brief Calculates the derivative (rate of change) of input values with filtering for stability.
 *
 * The `DerivativeFilter` smooths the derivative output using a running average filter
 * and normalizes it using a minimum filter to prevent rapid fluctuations.
 */
class DerivativeFilter {
private:
    RunningAverageFilter<10> output = RunningAverageFilter<10>(0.2f); ///< Running average filter for smoothing the derivative output.
    MinFilter<40> minFilter; ///< Minimum filter for baseline normalization.
    float previousReading = 0.0f; ///< Stores the previous input value for calculating the rate of change.
    float outputValue = 0.0f; ///< Stores the most recent filtered derivative value.

public:
    /**
     * @brief Constructs a `DerivativeFilter` instance with default configurations.
     */
    DerivativeFilter();

    /**
     * @brief Retrieves the current filtered derivative output.
     * 
     * @return The filtered derivative value.
     */
    float GetOutput();

    /**
     * @brief Filters the derivative of the input value and normalizes the output.
     *
     * @param value The current input value.
     * @return The filtered and normalized derivative value.
     */
    float Filter(float value);
};
