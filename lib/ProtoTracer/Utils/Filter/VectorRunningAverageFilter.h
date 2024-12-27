/**
 * @file VectorRunningAverageFilter.h
 * @brief Implements a running average filter for 3D vector smoothing.
 *
 * The `VectorRunningAverageFilter` class applies independent running average filters
 * to each component (X, Y, Z) of a 3D vector to reduce noise in the input data.
 *
 * @date 22/12/2024
 * @version 1.0
 * @author Coela Can't
 */

#pragma once

#include "RunningAverageFilter.h"
#include "../Math/Vector3D.h"

/**
 * @class VectorRunningAverageFilter
 * @brief Applies running average filtering independently to each component of a 3D vector.
 *
 * The `VectorRunningAverageFilter` class uses three `RunningAverageFilter` instances
 * to process the X, Y, and Z components of a `Vector3D`, providing a smoothed output for noisy 3D data.
 *
 * @tparam memory The size of the memory buffer used for the running average filter.
 */
template <size_t memory>
class VectorRunningAverageFilter {
private:
    RunningAverageFilter<memory> X; ///< Running average filter for the X component of the vector.
    RunningAverageFilter<memory> Y; ///< Running average filter for the Y component of the vector.
    RunningAverageFilter<memory> Z; ///< Running average filter for the Z component of the vector.

public:
    /**
     * @brief Default constructor for `VectorRunningAverageFilter`.
     *
     * Initializes the running average filters for each component with default parameters.
     */
    VectorRunningAverageFilter();

    /**
     * @brief Constructs a `VectorRunningAverageFilter` with a specified gain.
     *
     * Initializes the running average filters for each component with the given gain value.
     *
     * @param gain The smoothing gain for the running average filter (range 0.0 to 1.0).
     */
    VectorRunningAverageFilter(float gain);

    /**
     * @brief Filters a 3D vector input using the running average filter.
     *
     * Applies running average filtering independently to the X, Y, and Z components of the input vector.
     *
     * @param input The input `Vector3D` to filter.
     * @return The filtered `Vector3D`.
     */
    Vector3D Filter(Vector3D input);
};
