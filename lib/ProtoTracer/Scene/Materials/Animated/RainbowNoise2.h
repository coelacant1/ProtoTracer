/**
 * @file RainbowNoise2.h
 * @brief A dynamic material generating a rainbow effect using simplex noise with a black-to-color gradient.
 *
 * This file defines the RainbowNoise2 class, which uses simplex noise combined
 * with a gradient material to create a dynamic, flowing rainbow effect transitioning from black to color.
 *
 * @date 22/12/2024
 * @author Coela Can't
 */

#pragma once

#include "../AnimatedMaterial.h" ///< Base class for animated materials.
#include "../../../Utils/Signals/FunctionGenerator.h" ///< Utility for generating animated functions.
#include "../Static/GradientMaterial.h" ///< Include for gradient materials.
#include "../Static/SimplexNoise.h" ///< Include for simplex noise generation.

/**
 * @class RainbowNoise2
 * @brief A dynamic material that creates a rainbow effect using simplex noise with black-to-color transitions.
 *
 * The RainbowNoise2 class combines simplex noise with a gradient material to
 * produce a dynamic, colorful effect that shifts over time, starting from black.
 */
class RainbowNoise2 : public AnimatedMaterial {
private:
    FunctionGenerator fGenMatGradient = FunctionGenerator(FunctionGenerator::Sine, 0.0f, 0.5f, 6.65f); ///< Function to animate gradient properties.
    RGBColor noiseSpectrum[4] = {RGBColor(0, 0, 0), RGBColor(255, 0, 0), RGBColor(0, 255, 0), RGBColor(0, 0, 255)}; ///< Spectrum for the gradient, starting with black.
    GradientMaterial<4> gNoiseMat = GradientMaterial<4>(noiseSpectrum, 2.0f, false); ///< Gradient material for simplex noise.
    SimplexNoise<4> sNoise = SimplexNoise<4>(1, &gNoiseMat); ///< Simplex noise generator.
    float simplexNoiseDepth = 0.0f; ///< Depth parameter for simplex noise.

public:
    /**
     * @brief Default constructor for RainbowNoise2.
     */
    RainbowNoise2() {}

    /**
     * @brief Updates the material animation based on the time ratio.
     *
     * @param ratio The time ratio used for animation updates.
     */
    void Update(float ratio);

    /**
     * @brief Retrieves the associated material.
     *
     * @return Pointer to the GradientMaterial instance.
     */
    Material* GetMaterial();

    /**
     * @brief Computes the color at a given position in the material.
     *
     * @param position The position in 3D space.
     * @param normal The surface normal vector.
     * @param uvw The texture coordinates.
     * @return The computed color as an RGBColor.
     */
    RGBColor GetRGB(const Vector3D& position, const Vector3D& normal, const Vector3D& uvw) override;
};
