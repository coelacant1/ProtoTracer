/**
 * @file Overflow.h
 * @brief Defines the `Overflow` effect class for adding overflow distortion to pixel groups.
 *
 * The `Overflow` effect manipulates pixel values to exceed their 8-bit boundaries,
 * creating visual artifacts by wrapping values that exceed 255 back to 0.
 *
 * @date 22/12/2024
 * @version 1.0
 * @author Coela Can't
 */

#pragma once

#include "Effect.h"

/**
 * @class Overflow
 * @brief Implements an overflow distortion effect for pixel groups.
 *
 * The `Overflow` effect intentionally overflows 8-bit pixel values, creating dynamic
 * wrap-around effects that result in unexpected color distortions.
 */
class Overflow : public Effect {
private:
    const uint8_t pixels; ///< Number of pixels to affect in the group.

public:
    /**
     * @brief Constructs an `Overflow` effect with a specified number of affected pixels.
     *
     * @param pixels The number of pixels to apply the overflow effect to.
     */
    Overflow(uint8_t pixels);

    /**
     * @brief Applies the overflow distortion effect to the given pixel group.
     *
     * This method modifies pixel color values, forcing them to exceed their 8-bit limits,
     * and wraps them around using modulo arithmetic.
     *
     * @param pixelGroup Pointer to the `IPixelGroup` to which the effect will be applied.
     */
    void ApplyEffect(IPixelGroup* pixelGroup) override;
};
