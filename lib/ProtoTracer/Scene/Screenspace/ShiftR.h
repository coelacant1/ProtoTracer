/**
 * @file ShiftR.h
 * @brief Defines the `ShiftR` effect class for shifting color channels radially.
 *
 * The `ShiftR` effect applies a radial shift to the red, green, and blue channels
 * of the pixels, creating a dynamic swirling color effect.
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
 * @class ShiftR
 * @brief Radially shifts the red, green, and blue channels of the pixels.
 *
 * The `ShiftR` effect uses multiple function generators to apply rotations and phase shifts
 * to the pixel colors, resulting in a swirling radial color transition.
 */
class ShiftR : public Effect {
private:
    const uint8_t pixels; ///< Number of pixels to consider for the radial effect.

    /// Function generator for the red channel rotation phase.
    FunctionGenerator fGenPhase1 = FunctionGenerator(FunctionGenerator::Sawtooth, 0.0f, 1.0f, 4.5f);

    /// Function generator for the green channel rotation phase.
    FunctionGenerator fGenPhase2 = FunctionGenerator(FunctionGenerator::Sawtooth, 0.0f, 1.0f, 3.2f);

    /// Function generator for the overall rotation.
    FunctionGenerator fGenRotation = FunctionGenerator(FunctionGenerator::Sawtooth, 0.0f, 360.0f, 3.7f);

public:
    /**
     * @brief Constructs a `ShiftR` effect instance.
     *
     * @param pixels The number of pixels to consider for the radial effect.
     */
    ShiftR(uint8_t pixels);

    /**
     * @brief Applies the radial shift effect to the given pixel group.
     *
     * This method shifts the red, green, and blue channels of the pixels radially
     * based on the configured function generators.
     *
     * @param pixelGroup Pointer to the `IPixelGroup` to which the effect will be applied.
     */
    void ApplyEffect(IPixelGroup* pixelGroup) override;
};
