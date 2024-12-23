/**
 * @file SimpleMaterial.h
 * @brief A material class that applies a single RGB color to all surfaces.
 *
 * The `SimpleMaterial` class is designed for cases where a uniform color is required for rendering,
 * with optional hue-shifting functionality for dynamic color effects.
 *
 * @date 22/12/2024
 * @author Coela Can't
 */

#pragma once

#include "../Material.h" ///< Base class for materials.
#include "../../../Utils/Math/Vector2D.h" ///< Utility for 2D vector operations.

/**
 * @class SimpleMaterial
 * @brief A material that applies a single, solid RGB color to surfaces.
 *
 * This class allows setting a static RGB color or dynamically adjusting its hue for visual effects.
 */
class SimpleMaterial : public Material {
private:
    RGBColor rgb; ///< The active RGB color applied to the surface.
    RGBColor baseRGB; ///< The base RGB color used for reference during hue shifts.

public:
    /**
     * @brief Constructs a `SimpleMaterial` with a specified RGB color.
     *
     * @param rgb The initial color to be applied to the material.
     */
    SimpleMaterial(RGBColor rgb);

    /**
     * @brief Adjusts the hue of the material's color.
     *
     * This function shifts the hue of the current color by the specified degree value
     * while maintaining its brightness and saturation.
     *
     * @param hueDeg The hue shift in degrees (range: 0–360).
     */
    void HueShift(float hueDeg);

    /**
     * @brief Sets a new RGB color for the material.
     *
     * @param rgb The new RGB color to apply.
     */
    void SetRGB(RGBColor rgb);

    /**
     * @brief Retrieves the RGB color for a surface.
     *
     * For `SimpleMaterial`, this always returns the same color, regardless of position, normal, or texture coordinates.
     *
     * @param position 3D position in the scene (not used for this material).
     * @param normal Normal vector at the position (not used for this material).
     * @param uvw Texture coordinates at the position (not used for this material).
     * @return The RGB color of the material.
     */
    RGBColor GetRGB(const Vector3D& position, const Vector3D& normal, const Vector3D& uvw) override;
};
