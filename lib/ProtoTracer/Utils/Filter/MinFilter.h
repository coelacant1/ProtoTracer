/**
 * @file MinFilter.h
 * @brief Implements a moving minimum filter for processing data streams.
 *
 * The `MinFilter` maintains a window of the smallest values over a specified
 * memory range. It is useful for smoothing data while capturing minimum values.
 *
 * @date 22/12/2024
 * @version 1.0
 * @author Coela Can't
 */

#pragma once

#include "../Math/Mathematics.h"

/**
 * @class MinFilter
 * @brief Implements a minimum filter over a sliding window.
 *
 * This class filters input data by maintaining a history of minimum values
 * over a specified memory window. It is particularly useful for detecting
 * and tracking minimum values in data streams.
 *
 * @tparam memory The size of the memory window for tracking minimum values.
 */
template<size_t memory>
class MinFilter {
private:
    const int minMemory = static_cast<int>(std::ceil(memory / 10.0)); ///< Number of memory blocks for minimum tracking.
    float values[memory]; ///< Circular buffer of values.
    float minValues[memory / 10]; ///< Array of minimum values in each block.
    uint8_t currentAmount = 0; ///< Number of values currently stored in the buffer.
    bool ignoreSame; ///< Whether to ignore consecutive identical values.

    /**
     * @brief Shifts the values in the specified array to make room for a new value.
     *
     * @param mem The size of the array.
     * @param arr The array to shift.
     */
    void ShiftArray(uint8_t mem, float* arr);

public:
    /**
     * @brief Constructs a `MinFilter` with the specified memory size and behavior.
     *
     * @param ignoreSame Whether to ignore consecutive identical values (default: true).
     */
    MinFilter(bool ignoreSame = true);

    /**
     * @brief Filters the given value, updating the minimum value within the memory window.
     *
     * @param value The input value to filter.
     * @return The minimum value within the memory window after updating with the new value.
     */
    float Filter(float value);
};

#include "MinFilter.tpp" // Includes the implementation of the template class.
