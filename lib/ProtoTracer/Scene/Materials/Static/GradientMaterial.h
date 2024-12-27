/**
 * @file GradientMaterial.h
 * @brief Defines a material for creating gradient color effects in 3D rendering.
 *
 * The `GradientMaterial` class allows for the creation of gradients with customizable
 * colors, radial effects, steps, and transformations like rotation and position offsets.
 *
 * @tparam colorCount Number of colors in the gradient.
 * @date 22/12/2024
 * @author Coela Can't
 */

#pragma once

#include "../Material.h" // Base class for materials.
#include "../../../Utils/Math/Mathematics.h" // Mathematical utilities.
#include "../../../Utils/Math/Rotation.h" // Rotation utilities.
#include "../../../Utils/Math/Vector2D.h" // 2D vector operations.

/**
 * @class GradientMaterial
 * @brief Creates a customizable gradient material for rendering.
 *
 * The `GradientMaterial` class supports linear and radial gradients, with options for
 * stepping, position and rotation offsets, and period adjustments.
 *
 * @tparam colorCount Number of colors in the gradient.
 */
template<size_t colorCount>
class GradientMaterial : public Material {
private:
    RGBColor rgbColors[colorCount]; ///< Array of colors used in the gradient.
    RGBColor* baseRGBColors; ///< Pointer to the base RGB colors.
    Vector2D positionOffset; ///< Offset for the gradient's position.
    Vector2D rotationOffset; ///< Point about which the gradient rotates.
    float gradientPeriod = 1.0f; ///< Period of the gradient repetition.
    float rotationAngle = 0.0f; ///< Angle for rotating the gradient.
    bool isRadial = false; ///< Whether the gradient is radial.
    bool isStepped = false; ///< Whether the gradient is stepped.
    float gradientShift = 0.0f; ///< Shift in the gradient pattern.

public:
    /**
     * @brief Constructs a `GradientMaterial` instance.
     *
     * @param rgbColors Array of colors for the gradient.
     * @param gradientPeriod Period of the gradient repetition.
     * @param isRadial Whether the gradient is radial.
     * @param isStepped Whether the gradient is stepped.
     */
    GradientMaterial(RGBColor* rgbColors, float gradientPeriod, bool isRadial, bool isStepped = false);

    /**
     * @brief Updates the colors of the gradient.
     *
     * @param rgbColors New array of colors for the gradient.
     */
    void UpdateGradient(RGBColor* rgbColors);

    /**
     * @brief Sets the position offset for the gradient.
     *
     * @param positionOffset The new position offset.
     */
    void SetPositionOffset(Vector2D positionOffset);

    /**
     * @brief Sets the rotation offset for the gradient.
     *
     * @param rotationOffset The new rotation offset point.
     */
    void SetRotationOffset(Vector2D rotationOffset);

    /**
     * @brief Sets the rotation angle for the gradient.
     *
     * @param rotationAngle The new rotation angle in degrees.
     */
    void SetRotationAngle(float rotationAngle);

    /**
     * @brief Sets the gradient's period of repetition.
     *
     * @param gradientPeriod The new gradient period.
     */
    void SetGradientPeriod(float gradientPeriod);

    /**
     * @brief Shifts the gradient by a ratio.
     *
     * @param ratio The ratio by which to shift the gradient.
     */
    void GradientShift(float ratio);

    /**
     * @brief Shifts the hue of the gradient by a specified degree.
     *
     * @param hueDeg Degrees by which to shift the gradient's hue.
     */
    void HueShift(float hueDeg);

    /**
     * @brief Updates the RGB colors in the gradient.
     */
    void UpdateRGB();

    /**
     * @brief Gets the RGB color for a given position in the gradient.
     *
     * @param position 3D position in the gradient.
     * @param normal Normal vector at the position.
     * @param uvw Texture coordinates at the position.
     * @return The calculated RGB color.
     */
    RGBColor GetRGB(const Vector3D& position, const Vector3D& normal, const Vector3D& uvw) override;
};

#include "GradientMaterial.tpp" // Include the template implementation.
