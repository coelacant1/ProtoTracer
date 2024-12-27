/**
 * @file RadialBlur.h
 * @brief Defines the `RadialBlur` effect class for applying a radial blur to pixel groups.
 *
 * The `RadialBlur` effect creates a circular blur effect, simulating radial motion,
 * for visually dynamic animations.
 *
 * @date 22/12/2024
 * @version 1.0
 * @author Coela Can't
 */

#pragma once

#include "Effect.h"
#include "../../Utils/Signals/FunctionGenerator.h"
#include "../../Utils/Math/Mathematics.h"

/**
 * @class RadialBlur
 * @brief Applies a radial blur effect to pixel groups.
 *
 * The `RadialBlur` effect uses a function generator to create rotational motion,
 * resulting in a circular blur effect.
 */
class RadialBlur : public Effect {
private:
    const uint8_t pixels; ///< Number of pixels to apply the effect to.

    /// Function generator for controlling the rotational motion of the blur.
    FunctionGenerator fGenRotation = FunctionGenerator(FunctionGenerator::Sawtooth, 0.0f, 360.0f, 3.7f);

public:
    /**
     * @brief Constructs a `RadialBlur` effect instance.
     *
     * @param pixels The number of pixels to apply the effect to.
     */
    RadialBlur(uint8_t pixels);

    /**
     * @brief Applies the radial blur effect to the given pixel group.
     *
     * This method modifies the pixel group by simulating a circular blur effect.
     *
     * @param pixelGroup Pointer to the `IPixelGroup` to which the effect will be applied.
     */
    void ApplyEffect(IPixelGroup* pixelGroup) override;
};
