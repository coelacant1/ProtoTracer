/**
 * @file HorizontalRainbow.h
 * @brief A dynamic horizontal rainbow gradient material.
 *
 * This file defines the HorizontalRainbow class, which generates a horizontal
 * rainbow gradient effect that can be animated over time.
 *
 * @date 22/12/2024
 * @author Coela Can't
 */

#pragma once

#include "../AnimatedMaterial.h" // Base class for animated materials.
#include "../Static/GradientMaterial.h" // Include for gradient materials.
#include "../Static/SimplexNoise.h" // Include for simplex noise generation.

/**
 * @class HorizontalRainbow
 * @brief A dynamic horizontal rainbow gradient material.
 *
 * The HorizontalRainbow class generates a colorful horizontal gradient using
 * a predefined rainbow spectrum and supports dynamic animation of the gradient.
 */
class HorizontalRainbow : public AnimatedMaterial {
private:
    RGBColor noiseSpectrum[6] = {RGBColor(255, 0, 0), RGBColor(255, 255, 0), RGBColor(0, 255, 0), RGBColor(0, 255, 255), RGBColor(0, 0, 255), RGBColor(255, 0, 255)}; ///< Predefined rainbow colors.
    GradientMaterial<6> gNoiseMat = GradientMaterial<6>(&noiseSpectrum[0], 2.0f, false, false); ///< Gradient material for the rainbow spectrum.
    float positionOffset = 0.0f; ///< Position offset for animating the gradient.

public:
    /**
     * @brief Default constructor for HorizontalRainbow.
     */
    HorizontalRainbow() {}

    /**
     * @brief Updates the gradient animation based on the provided time ratio.
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
     * @brief Computes the color at a given position in the gradient.
     *
     * @param position The position in 3D space.
     * @param normal The surface normal vector.
     * @param uvw The texture coordinates.
     * @return The computed color as an RGBColor.
     */
    RGBColor GetRGB(const Vector3D& position, const Vector3D& normal, const Vector3D& uvw) override;
};
