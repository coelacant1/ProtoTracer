/**
 * @file NormalMaterial.h
 * @brief A material class that visualizes surface normals.
 *
 * The `NormalMaterial` class provides a simple visualization of surface normals,
 * where RGB values represent the x, y, and z components of the normal vector.
 *
 * @date 22/12/2024
 * @author Coela Can't
 */

#pragma once

#include "../Material.h" ///< Base class for materials.
#include "../../../Utils/Math/Vector2D.h" ///< Vector utilities.
#include "GradientMaterial.h" ///< Optional gradient utilities for advanced extensions.

/**
 * @class NormalMaterial
 * @brief A material that visualizes surface normals as RGB colors.
 *
 * This class maps the components of a normal vector (x, y, z) directly to the RGB color channels,
 * providing an intuitive representation of surface orientations.
 */
class NormalMaterial : public Material {
public:
    /**
     * @brief Constructs a `NormalMaterial` object.
     */
    NormalMaterial();

    /**
     * @brief Calculates the RGB color based on the surface normal vector.
     *
     * @param position 3D position in the scene (not used for this material).
     * @param normal Normal vector at the position, used for RGB mapping.
     * @param uvw Texture coordinates at the position (not used for this material).
     * @return The RGB color corresponding to the normal vector.
     */
    RGBColor GetRGB(const Vector3D& position, const Vector3D& normal, const Vector3D& uvw) override;
};
