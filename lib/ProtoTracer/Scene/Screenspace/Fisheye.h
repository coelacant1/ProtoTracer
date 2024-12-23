/**
 * @file Fisheye.h
 * @brief Defines the `Fisheye` effect class for applying fisheye distortions to pixel groups.
 *
 * The `Fisheye` class applies a dynamic, time-variant fisheye distortion effect to pixel groups,
 * modifying their positions and colors based on mathematical transformations.
 *
 * @date 22/12/2024
 * @version 1.0
 * @author Coela Can't
 */

#pragma once

#include "Effect.h"
#include "../../Utils/Signals/FunctionGenerator.h"
#include "../../Utils/Math/Vector2D.h"

/**
 * @class Fisheye
 * @brief Implements a fisheye distortion effect for pixel groups.
 *
 * The `Fisheye` effect dynamically distorts pixel positions around a specified offset
 * using sinusoidal function generators for smooth, animated transformations.
 */
class Fisheye : public Effect {
private:
    Vector2D offset = Vector2D(0.0f, 0.0f); ///< Offset for the fisheye distortion center.
    float amplitude; ///< Amplitude of the distortion effect.
    FunctionGenerator fGenSize = FunctionGenerator(FunctionGenerator::Sine, 1.0f, 48.0f, 2.3f); ///< Controls the size modulation.
    FunctionGenerator fGenX = FunctionGenerator(FunctionGenerator::Sine, -96.0f, 96.0f, 2.7f); ///< Controls X-axis displacement.
    FunctionGenerator fGenY = FunctionGenerator(FunctionGenerator::Sine, -96.0f, 96.0f, 1.7f); ///< Controls Y-axis displacement.
    FunctionGenerator fGenWarp = FunctionGenerator(FunctionGenerator::Sine, 1.0f, 100.0f, 3.7f); ///< Controls warp effect.

public:
    /**
     * @brief Constructs a `Fisheye` effect with a specified amplitude.
     * 
     * @param amplitude The amplitude of the fisheye distortion. Default is 0.5.
     */
    Fisheye(float amplitude = 0.5f);

    /**
     * @brief Sets the distortion center offset.
     * 
     * @param offset The new offset for the fisheye effect center.
     */
    void SetPosition(Vector2D offset);

    /**
     * @brief Sets the amplitude of the distortion.
     * 
     * @param amplitude The new amplitude for the fisheye effect.
     */
    void SetAmplitude(float amplitude);

    /**
     * @brief Applies the fisheye effect to the given pixel group.
     * 
     * This method modifies the positions of the pixels in the group based on the
     * fisheye distortion formula, using the amplitude, offset, and function generators.
     * 
     * @param pixelGroup Pointer to the `IPixelGroup` to which the effect will be applied.
     */
    void ApplyEffect(IPixelGroup* pixelGroup) override;
};

