/**
 * @file StripeMaterial.h
 * @brief A material class for generating striped patterns with configurable properties.
 *
 * This class provides functionality for creating dynamic striped patterns with wave effects,
 * color gradients, and rotational transformations.
 *
 * @date 22/12/2024
 * @author Coela Can't
 */

#pragma once

#include "../Material.h"
#include "../../../../../Utils/Math/Mathematics.h"
#include "../../../../../Utils/Math/Vector2D.h"
#include "../../../../../Utils/Math/Rotation.h"

/**
 * @class StripeMaterial
 * @brief Generates striped patterns with configurable properties.
 *
 * The `StripeMaterial` class provides methods for creating and manipulating
 * striped patterns that can include wave effects, color gradients, and rotational
 * transformations.
 */
class StripeMaterial : public Material {
private:
    RGBColor* rgbColors; ///< Array of colors used for the stripes.
    RGBColor* baseRGBColors; ///< Backup of the original colors for hue adjustments.
    uint8_t colorCount; ///< Number of colors in the stripe pattern.
    Vector2D positionOffset; ///< Offset for the stripe position.
    Vector2D rotationOffset; ///< Rotation center for the pattern.
    float stripeWidth; ///< Width of each stripe in the pattern.
    float wavePeriod; ///< Period of the sinusoidal wave effect.
    float waveAmplitude; ///< Amplitude of the sinusoidal wave effect.
    float rotationAngle; ///< Angle for rotating the pattern.

public:
    /**
     * @brief Constructs a StripeMaterial with given properties.
     *
     * @param colorCount Number of colors in the stripe pattern.
     * @param rgbColors Array of RGB colors for the stripes.
     * @param stripeWidth Width of each stripe.
     * @param wavePeriod Period of the wave effect.
     * @param waveAmplitude Amplitude of the wave effect.
     */
    StripeMaterial(uint8_t colorCount, RGBColor* rgbColors, float stripeWidth, float wavePeriod, float waveAmplitude);

    /**
     * @brief Sets the position offset for the pattern.
     *
     * @param positionOffset The desired position offset.
     */
    void SetPositionOffset(Vector2D positionOffset);

    /**
     * @brief Sets the rotation offset (center point) for the pattern.
     *
     * @param rotationOffset The center point for rotation.
     */
    void SetRotationOffset(Vector2D rotationOffset);

    /**
     * @brief Sets the rotation angle for the pattern.
     *
     * @param rotationAngle The desired rotation angle in degrees.
     */
    void SetRotationAngle(float rotationAngle);

    /**
     * @brief Sets the stripe width.
     *
     * @param stripeWidth The desired stripe width.
     */
    void SetStripeWidth(float stripeWidth);

    /**
     * @brief Sets the wave period for the sinusoidal effect.
     *
     * @param wavePeriod The desired wave period.
     */
    void SetWavePeriod(float wavePeriod);

    /**
     * @brief Sets the wave amplitude for the sinusoidal effect.
     *
     * @param waveAmplitude The desired wave amplitude.
     */
    void SetWaveAmplitude(float waveAmplitude);

    /**
     * @brief Applies a hue shift to the stripe colors.
     *
     * @param hueDeg The degree of hue shift to apply.
     */
    void HueShift(float hueDeg);

    /**
     * @brief Computes the color at a given position.
     *
     * @param position 3D position in the scene.
     * @param normal Normal vector at the position (not used for this material).
     * @param uvw Texture coordinates at the position (not used for this material).
     * @return The RGB color corresponding to the given position.
     */
    RGBColor GetRGB(const Vector3D& position, const Vector3D& normal, const Vector3D& uvw) override;
};
