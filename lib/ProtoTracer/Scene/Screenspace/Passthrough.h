/**
 * @file Passthrough.h
 * @brief Defines the `Passthrough` effect class for applying no modifications to pixel groups.
 *
 * The `Passthrough` effect serves as a placeholder or default effect that simply
 * forwards pixel data without any alterations.
 *
 * @date 22/12/2024
 * @version 1.0
 * @author Coela Can't
 */

#pragma once

#include "Effect.h"

/**
 * @class Passthrough
 * @brief A no-operation effect that leaves pixel groups unchanged.
 *
 * The `Passthrough` effect is used when no transformations or modifications
 * are required for a pixel group.
 */
class Passthrough : public Effect {
public:
    /**
     * @brief Constructs a `Passthrough` effect instance.
     *
     * This constructor initializes the `Passthrough` effect without requiring any parameters.
     */
    Passthrough();

    /**
     * @brief Applies the passthrough effect to the given pixel group.
     *
     * This method leaves the pixel group unchanged, effectively acting as a no-op.
     *
     * @param pixelGroup Pointer to the `IPixelGroup` to which the effect will be applied.
     */
    void ApplyEffect(IPixelGroup* pixelGroup) override;
};
