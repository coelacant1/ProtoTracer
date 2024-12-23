/**
 * @file VerticalBlur.h
 * @brief Defines the `VerticalBlur` effect class for applying a vertical blur effect.
 *
 * The `VerticalBlur` effect softens the visual appearance of a pixel group
 * by averaging pixel values along the vertical axis.
 *
 * @date 22/12/2024
 * @version 1.0
 * @author Coela Can't
 */

#pragma once

#include "Effect.h"

/**
 * @class VerticalBlur
 * @brief An effect that applies a vertical blur to a pixel group.
 *
 * The `VerticalBlur` effect modifies pixel colors by averaging neighboring pixels
 * along the vertical axis, creating a softened appearance.
 */
class VerticalBlur : public Effect {
private:
    /// Number of pixels to include in the vertical blur radius.
    const uint8_t pixels;

public:
    /**
     * @brief Constructs a `VerticalBlur` effect instance.
     * 
     * @param pixels Number of pixels to include in the blur radius.
     */
    VerticalBlur(uint8_t pixels);

    /**
     * @brief Applies the vertical blur effect to the given pixel group.
     *
     * The effect calculates an average color value for each pixel by considering
     * neighboring pixels within the specified vertical radius.
     *
     * @param pixelGroup Pointer to the `IPixelGroup` to which the effect will be applied.
     */
    void ApplyEffect(IPixelGroup* pixelGroup) override;
};
