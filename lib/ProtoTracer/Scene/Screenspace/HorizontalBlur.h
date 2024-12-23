/**
 * @file HorizontalBlur.h
 * @brief Defines the `HorizontalBlur` effect class for applying horizontal blur to pixel groups.
 *
 * The `HorizontalBlur` effect smooths pixel values by blending neighboring pixels
 * along the X-axis, creating a blur effect.
 *
 * @date 22/12/2024
 * @version 1.0
 * @author Coela Can't
 */

#pragma once

#include "Effect.h"
#include "../../Utils/Math/Mathematics.h"

/**
 * @class HorizontalBlur
 * @brief Implements a horizontal blur effect for pixel groups.
 *
 * The `HorizontalBlur` effect blends pixel colors along the X-axis over a specified
 * number of neighboring pixels, producing a blur effect.
 */
class HorizontalBlur : public Effect {
private:
    const uint8_t pixels; ///< The number of neighboring pixels to blend for the blur effect.

public:
    /**
     * @brief Constructs a `HorizontalBlur` effect with a specified blur radius.
     * 
     * @param pixels The radius of the blur effect in terms of the number of neighboring pixels.
     */
    HorizontalBlur(uint8_t pixels);

    /**
     * @brief Applies the horizontal blur effect to the given pixel group.
     * 
     * This method blends the colors of neighboring pixels along the X-axis to create
     * a smooth transition effect.
     * 
     * @param pixelGroup Pointer to the `IPixelGroup` to which the effect will be applied.
     */
    void ApplyEffect(IPixelGroup* pixelGroup) override;
};
