/**
 * @file MaxFilter.h
 * @brief Implements a moving maximum filter for processing data streams.
 *
 * The `MaxFilter` maintains a window of the largest values over a specified
 * memory range. It can be used to smooth data while capturing peak values.
 *
 * @date 22/12/2024
 * @version 1.0
 * @author Coela Can't
 */

#pragma once

#include "../Math/Mathematics.h"

/**
 * @class MaxFilter
 * @brief Implements a maximum filter over a sliding window.
 *
 * This class filters input data by maintaining a history of maximum values
 * over a specified memory window. It is particularly useful for detecting
 * and tracking peak values in data streams.
 *
 * @tparam memory The size of the memory window for tracking maximum values.
 */
template<size_t memory>
class MaxFilter {
private:
    const int maxMemory = static_cast<int>(std::ceil(memory / 10.0)); ///< Number of memory blocks for peak tracking.
    float values[memory]; ///< Circular buffer of values.
    float maxValues[memory / 10]; ///< Array of maximum values in each block.
    uint8_t currentAmount = 0; ///< Number of values currently stored in the buffer.

    /**
     * @brief Shifts the values in the specified array to make room for a new value.
     *
     * @param mem The size of the array.
     * @param arr The array to shift.
     */
    void ShiftArray(uint8_t mem, float* arr);

public:
    /**
     * @brief Constructs a `MaxFilter` with the specified memory size.
     */
    MaxFilter();

    /**
     * @brief Filters the given value, updating the maximum value within the memory window.
     *
     * @param value The input value to filter.
     * @return The maximum value within the memory window after updating with the new value.
     */
    float Filter(float value);
};

#include "MaxFilter.tpp" ///< Includes the implementation of the template class.
