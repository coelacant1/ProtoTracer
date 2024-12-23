/**
 * @file PhaseOffsetY.h
 * @brief Defines the `PhaseOffsetY` effect class for applying vertical phase offsets to pixel groups.
 *
 * The `PhaseOffsetY` effect dynamically alters pixel groups by introducing phase shifts
 * along the vertical axis for visually engaging animations.
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
 * @class PhaseOffsetY
 * @brief Applies vertical phase offsets to pixel groups.
 *
 * The `PhaseOffsetY` effect utilizes a function generator to create phase shifts
 * along the vertical axis for smooth and dynamic animations.
 */
class PhaseOffsetY : public Effect {
private:
    const uint8_t pixels; ///< Number of pixels to apply the effect to.

    /// Function generator for vertical phase offsets.
    FunctionGenerator fGenPhase = FunctionGenerator(FunctionGenerator::Sawtooth, 0.0f, 1.0f, 3.5f);

public:
    /**
     * @brief Constructs a `PhaseOffsetY` effect instance.
     *
     * @param pixels The number of pixels to apply the effect to.
     */
    PhaseOffsetY(uint8_t pixels);

    /**
     * @brief Applies the vertical phase offset effect to the given pixel group.
     *
     * This method modifies the pixel group by applying phase shifts along the vertical axis.
     *
     * @param pixelGroup Pointer to the `IPixelGroup` to which the effect will be applied.
     */
    void ApplyEffect(IPixelGroup* pixelGroup) override;
};
