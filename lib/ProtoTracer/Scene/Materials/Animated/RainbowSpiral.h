/**
 * @file RainbowSpiral.h
 * @brief A dynamic material that creates a colorful, animated rainbow spiral effect.
 *
 * This file defines the RainbowSpiral class, which combines a spiral material with
 * a rainbow color spectrum and an animated function for dynamic visual effects.
 *
 * @date 22/12/2024
 * @author Coela Can't
 */

#pragma once

#include "../AnimatedMaterial.h" // Base class for animated materials.
#include "../../../Utils/Signals/FunctionGenerator.h" // Utility for generating animated functions.
#include "../Static/SpiralMaterial.h" // Include for the spiral material implementation.

/**
 * @class RainbowSpiral
 * @brief A dynamic material creating a colorful rainbow spiral animation.
 *
 * The RainbowSpiral class generates a visually dynamic effect by combining a spiral
 * material with a rainbow gradient and function-driven animation.
 */
class RainbowSpiral : public AnimatedMaterial {
private:
    FunctionGenerator fGenMatBend = FunctionGenerator(FunctionGenerator::Sine, 0.8f, 0.9f, 6.7f); ///< Function generator for animating spiral bending.
    RGBColor rainbowSpectrum[6] = {RGBColor(255, 0, 0), RGBColor(255, 255, 0), RGBColor(0, 255, 0), RGBColor(0, 255, 255), RGBColor(0, 0, 255), RGBColor(255, 0, 255)}; ///< Predefined rainbow color spectrum.
    SpiralMaterial spiralMaterial = SpiralMaterial(6, rainbowSpectrum, 3.0f, 7.0f); ///< Spiral material configured with rainbow spectrum and scale parameters.

public:
    /**
     * @brief Default constructor for RainbowSpiral.
     */
    RainbowSpiral() {}

    /**
     * @brief Updates the material animation based on the time ratio.
     *
     * @param ratio The time ratio used for animation updates.
     */
    void Update(float ratio);

    /**
     * @brief Retrieves the associated spiral material.
     *
     * @return Pointer to the SpiralMaterial instance.
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
