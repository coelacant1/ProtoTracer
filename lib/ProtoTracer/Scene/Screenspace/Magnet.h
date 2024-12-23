/**
 * @file Magnet.h
 * @brief Defines the `Magnet` effect class for creating magnetic distortion effects on pixel groups.
 *
 * The `Magnet` effect simulates a magnetic field that distorts the positions of pixels
 * based on a central offset, amplitude, and sinusoidal warping functions.
 *
 * @date 22/12/2024
 * @version 1.0
 * @author Coela Can't
 */

#pragma once

#include "Effect.h"
#include "../../Utils/Signals/FunctionGenerator.h"

/**
 * @class Magnet
 * @brief Implements a magnetic distortion effect for pixel groups.
 *
 * The `Magnet` effect distorts pixel positions by applying a simulated magnetic
 * field, creating dynamic and fluid distortion patterns.
 */
class Magnet : public Effect {
private:
    Vector2D offset = Vector2D(0.0f, 0.0f); ///< The central offset of the magnetic effect.
    float amplitude; ///< The strength of the magnetic distortion.
    FunctionGenerator fGenSize = FunctionGenerator(FunctionGenerator::Sine, 1.0f, 5000.0f, 2.3f); ///< Generator for field size dynamics.
    FunctionGenerator fGenX = FunctionGenerator(FunctionGenerator::Sine, -96.0f, 96.0f, 2.7f); ///< Generator for X-axis warp dynamics.
    FunctionGenerator fGenY = FunctionGenerator(FunctionGenerator::Sine, -96.0f, 96.0f, 1.7f); ///< Generator for Y-axis warp dynamics.
    FunctionGenerator fGenWarp = FunctionGenerator(FunctionGenerator::Sine, 1.0f, 100.0f, 3.7f); ///< Generator for warp intensity dynamics.

public:
    /**
     * @brief Constructs a `Magnet` effect with a specified amplitude.
     *
     * @param amplitude The initial strength of the magnetic distortion. Default is 0.5f.
     */
    Magnet(float amplitude = 0.5f);

    /**
     * @brief Sets the central position of the magnetic effect.
     *
     * @param offset The `Vector2D` position to set as the central offset.
     */
    void SetPosition(Vector2D offset);

    /**
     * @brief Sets the amplitude of the magnetic distortion effect.
     *
     * @param amplitude The new amplitude value.
     */
    void SetAmplitude(float amplitude);

    /**
     * @brief Applies the magnetic distortion effect to the given pixel group.
     *
     * This method modifies pixel positions dynamically based on the magnetic field simulation.
     *
     * @param pixelGroup Pointer to the `IPixelGroup` to which the effect will be applied.
     */
    void ApplyEffect(IPixelGroup* pixelGroup) override;
};
