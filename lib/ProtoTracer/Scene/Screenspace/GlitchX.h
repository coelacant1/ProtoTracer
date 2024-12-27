/**
 * @file GlitchX.h
 * @brief Defines the `GlitchX` effect class for applying glitch effects along the X-axis to pixel groups.
 *
 * The `GlitchX` effect randomly distorts pixel positions along the X-axis,
 * creating a glitch-like appearance.
 *
 * @date 22/12/2024
 * @version 1.0
 * @author Coela Can't
 */

#pragma once

#include <Arduino.h>
#include "Effect.h"
#include "../../Utils/Math/Mathematics.h"

/**
 * @class GlitchX
 * @brief Implements a glitch effect along the X-axis for pixel groups.
 *
 * The `GlitchX` effect distorts the positions of pixels randomly along the X-axis,
 * creating a glitch-like distortion.
 */
class GlitchX : public Effect {
private:
    const uint8_t pixels; ///< The number of pixels to distort.

public:
    /**
     * @brief Constructs a `GlitchX` effect with a specified number of pixels.
     * 
     * @param pixels The number of pixels to distort along the X-axis.
     */
    GlitchX(uint8_t pixels);

    /**
     * @brief Applies the glitch effect along the X-axis to the given pixel group.
     * 
     * This method modifies the X-coordinates of the pixels in the group,
     * shifting them randomly within a defined range.
     * 
     * @param pixelGroup Pointer to the `IPixelGroup` to which the effect will be applied.
     */
    void ApplyEffect(IPixelGroup* pixelGroup) override;
};

