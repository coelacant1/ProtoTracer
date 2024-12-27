/**
 * @file Effect.h
 * @brief Defines the base `Effect` class for applying transformations or effects to pixel groups.
 *
 * The `Effect` class serves as an abstract base for implementing various visual effects
 * on pixel groups, leveraging mathematical transformations and ratios for dynamic adjustments.
 *
 * @date 22/12/2024
 * @version 1.0
 * @author Coela Can't
 */

#pragma once

#include "../../Camera/Pixels/IPixelGroup.h"
#include "../../Utils/Math/Mathematics.h"

/**
 * @class Effect
 * @brief Abstract base class for applying visual effects to pixel groups.
 *
 * The `Effect` class provides a framework for applying transformations or effects
 * to `IPixelGroup` objects. Subclasses should implement the `ApplyEffect` method
 * to define specific effect behavior.
 */
class Effect {
protected:
    float ratio = 0.0f; ///< A scaling ratio used for dynamic effect adjustments.

public:
    /**
     * @brief Default constructor for the `Effect` class.
     */
    Effect();

    /**
     * @brief Sets the scaling ratio for the effect.
     *
     * The ratio is typically used for time-based or intensity-based transformations.
     *
     * @param ratio The scaling ratio to be applied.
     */
    void SetRatio(float ratio);

    /**
     * @brief Pure virtual method for applying the effect to a pixel group.
     *
     * Subclasses must override this method to implement the effect's behavior.
     *
     * @param pixelGroup Pointer to the `IPixelGroup` to which the effect will be applied.
     */
    virtual void ApplyEffect(IPixelGroup* pixelGroup) = 0;
};

