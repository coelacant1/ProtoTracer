/**
 * @file PhaseOffsetX.h
 * @brief Defines the `PhaseOffsetX` effect class for applying horizontal phase offsets to pixel groups.
 *
 * The `PhaseOffsetX` effect dynamically alters pixel groups by introducing phase shifts
 * along the horizontal axis for visually engaging animations.
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
 * @class PhaseOffsetX
 * @brief Applies horizontal phase offsets to pixel groups.
 *
 * The `PhaseOffsetX` effect utilizes a function generator to create phase shifts
 * along the horizontal axis for smooth and dynamic animations.
 */
class PhaseOffsetX : public Effect {
private:
    const uint8_t pixels; ///< Number of pixels to apply the effect to.

    /// Function generator for horizontal phase offsets.
    FunctionGenerator fGenPhase = FunctionGenerator(FunctionGenerator::Sawtooth, 0.0f, 1.0f, 3.5f);

public:
    /**
     * @brief Constructs a `PhaseOffsetX` effect instance.
     *
     * @param pixels The number of pixels to apply the effect to.
     */
    PhaseOffsetX(uint8_t pixels);

    /**
     * @brief Applies the horizontal phase offset effect to the given pixel group.
     *
     * This method modifies the pixel group by applying phase shifts along the horizontal axis.
     *
     * @param pixelGroup Pointer to the `IPixelGroup` to which the effect will be applied.
     */
    void ApplyEffect(IPixelGroup* pixelGroup) override;
};
