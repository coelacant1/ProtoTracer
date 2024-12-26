/**
 * @file FlowNoise.h
 * @brief A dynamic simplex noise gradient material for a lava lamp effect.
 *
 * This file defines the FlowNoise class, which generates a dynamic gradient
 * using simplex noise and animates the z-position over time to create a flowing,
 * lava lamp-like visual effect.
 *
 * @date 22/12/2024
 * @author Coela Can't
 */

#pragma once

#include "../AnimatedMaterial.h" // Base class for animated materials.
#include "../../../Utils/Signals/FunctionGenerator.h" // Utility for generating animated functions.
#include "../Static/GradientMaterial.h" // Include for gradient materials.
#include "../Static/SimplexNoise.h" // Include for simplex noise generation.

/**
 * @class FlowNoise
 * @brief A dynamic simplex noise gradient material for a flowing effect.
 *
 * The FlowNoise class generates a gradient using simplex noise and animates
 * the z-position over time. The result is a flowing, lava lamp-like visual effect.
 */
class FlowNoise : public AnimatedMaterial {
private:
    FunctionGenerator fGenMatGradientP = FunctionGenerator(FunctionGenerator::Sine, 0.25f, 1.5f, 4.35f); ///< Function for gradient property modulation.
    FunctionGenerator fGenMatGradientX = FunctionGenerator(FunctionGenerator::Sine, 0.0f, 0.5f, 3.12f); ///< Function for x-axis modulation.
    FunctionGenerator fGenMatGradientY = FunctionGenerator(FunctionGenerator::Sine, 0.0f, 0.5f, 1.93f); ///< Function for y-axis modulation.
    FunctionGenerator fGenMatGradientZ = FunctionGenerator(FunctionGenerator::Sine, 0.0f, 0.5f, 4.56f); ///< Function for z-axis modulation.
    RGBColor noiseSpectrum[2] = {RGBColor(14, 33, 160), RGBColor(236, 83, 176)}; ///< Gradient colors for the noise material.
    GradientMaterial<2> gNoiseMat = GradientMaterial<2>(noiseSpectrum, 2.0f, false); ///< Gradient material for simplex noise.
    SimplexNoise<2> sNoise = SimplexNoise<2>(1, &gNoiseMat); ///< Simplex noise generator.
    float simplexNoiseDepth = 0.0f; ///< Depth parameter for simplex noise.

public:
    /**
     * @brief Default constructor for FlowNoise.
     */
    FlowNoise() {}

    /**
     * @brief Sets a specific gradient color.
     *
     * @param color The RGB color to set.
     * @param colorIndex The index in the gradient array to modify.
     */
    void SetGradient(RGBColor color, uint8_t colorIndex);

    /**
     * @brief Updates the material's state based on the provided time ratio.
     *
     * @param ratio The time ratio for animation updates.
     */
    void Update(float ratio);

    /**
     * @brief Retrieves the associated material.
     *
     * @return Pointer to the Material instance.
     */
    Material* GetMaterial();

    /**
     * @brief Computes the color at a given position using simplex noise.
     *
     * @param position The position in 3D space.
     * @param normal The surface normal vector.
     * @param uvw The texture coordinates.
     * @return The computed color as an RGBColor.
     */
    RGBColor GetRGB(const Vector3D& position, const Vector3D& normal, const Vector3D& uvw) override;
};
