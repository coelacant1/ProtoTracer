/**
 * @file PhaseOffsetR.h
 * @brief Defines the `PhaseOffsetR` effect class for applying rotational phase offsets to pixel groups.
 *
 * The `PhaseOffsetR` effect modifies pixel groups by applying phase offsets and rotations,
 * creating dynamic visual patterns.
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
 * @class PhaseOffsetR
 * @brief Applies rotational phase offsets to pixel groups.
 *
 * The `PhaseOffsetR` effect uses function generators to create phase offsets and
 * rotational transformations for dynamic and visually engaging effects.
 */
class PhaseOffsetR : public Effect {
private:
    const uint8_t pixels; ///< Number of pixels to apply the effect to.

    /// Function generator for the first phase offset.
    FunctionGenerator fGenPhase1 = FunctionGenerator(FunctionGenerator::Sawtooth, 0.0f, 1.0f, 4.5f);

    /// Function generator for the second phase offset.
    FunctionGenerator fGenPhase2 = FunctionGenerator(FunctionGenerator::Sawtooth, 0.0f, 1.0f, 3.2f);

    /// Function generator for rotation transformations.
    FunctionGenerator fGenRotation = FunctionGenerator(FunctionGenerator::Sawtooth, 0.0f, 360.0f, 3.7f);

public:
    /**
     * @brief Constructs a `PhaseOffsetR` effect instance.
     *
     * @param pixels The number of pixels to apply the effect to.
     */
    PhaseOffsetR(uint8_t pixels);

    /**
     * @brief Applies the rotational phase offset effect to the given pixel group.
     *
     * This method modifies the pixel group using phase offsets and rotations.
     *
     * @param pixelGroup Pointer to the `IPixelGroup` to which the effect will be applied.
     */
    void ApplyEffect(IPixelGroup* pixelGroup) override;
};
