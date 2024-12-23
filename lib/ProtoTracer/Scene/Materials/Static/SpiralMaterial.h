/**
 * @file SpiralMaterial.h
 * @brief A material class for generating spiral effects.
 *
 * This class provides functionality for creating spiraling patterns
 * using customizable colors, width, and bending parameters.
 *
 * @date 22/12/2024
 * @author Coela Can't
 */

#pragma once

#include "../Material.h"
#include "../../../Utils/Math/Mathematics.h"
#include "../../../Utils/Math/Vector2D.h"
#include "../../../Utils/Math/Rotation.h"

/**
 * @class SpiralMaterial
 * @brief Generates a spiral pattern with configurable properties.
 *
 * This class provides methods for manipulating the position, rotation,
 * width, and bend of a spiral. The pattern is created using an array
 * of RGB colors.
 */
class SpiralMaterial : public Material {
private:
    RGBColor* rgbColors; ///< Array of colors for the spiral.
    RGBColor* baseRGBColors; ///< Backup array for the original colors.
    uint8_t colorCount; ///< Number of colors in the spiral.
    Vector2D positionOffset; ///< Offset for the position of the spiral.
    Vector2D rotationOffset; ///< Point around which the spiral rotates.
    float width; ///< Width of the spiral arms.
    float bend; ///< Degree of bending for the spiral arms.
    float rotationAngle; ///< Angle to rotate the spiral pattern.

public:
    /**
     * @brief Constructs a SpiralMaterial instance.
     *
     * @param colorCount Number of colors in the spiral.
     * @param rgbColors Pointer to an array of colors.
     * @param width Width of the spiral arms.
     * @param bend Degree of bending for the spiral arms.
     */
    SpiralMaterial(uint8_t colorCount, RGBColor* rgbColors, float width, float bend);

    /**
     * @brief Destructor for SpiralMaterial.
     */
    ~SpiralMaterial();

    /**
     * @brief Sets the position offset for the spiral.
     *
     * @param positionOffset The offset to apply.
     */
    void SetPositionOffset(Vector2D positionOffset);

    /**
     * @brief Sets the rotation offset for the spiral.
     *
     * @param rotationOffset The point around which to rotate.
     */
    void SetRotationOffset(Vector2D rotationOffset);

    /**
     * @brief Sets the rotation angle for the spiral.
     *
     * @param rotationAngle The angle to rotate the spiral pattern.
     */
    void SetRotationAngle(float rotationAngle);

    /**
     * @brief Sets the width of the spiral arms.
     *
     * @param width The desired width.
     */
    void SetWidth(float width);

    /**
     * @brief Sets the bending factor of the spiral arms.
     *
     * @param bend The degree of bending.
     */
    void SetBend(float bend);

    /**
     * @brief Shifts the hue of the spiral colors.
     *
     * @param hueDeg The degree to shift the hue.
     */
    void HueShift(float hueDeg);

    /**
     * @brief Retrieves the color for a given position.
     *
     * @param position 3D position in the scene.
     * @param normal Normal vector at the position (not used for this material).
     * @param uvw Texture coordinates at the position (not used for this material).
     * @return The RGB color corresponding to the given position.
     */
    RGBColor GetRGB(const Vector3D& position, const Vector3D& normal, const Vector3D& uvw) override;
};
