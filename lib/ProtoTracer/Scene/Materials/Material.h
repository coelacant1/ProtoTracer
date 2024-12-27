/**
 * @file Material.h
 * @brief Base class for materials defining shading and rendering behavior.
 *
 * The `Material` class serves as an interface for materials that calculate
 * color based on various blending methods and surface parameters.
 *
 * @date 22/12/2024
 * @version 1.0
 * @author Coela Can't
 */

#pragma once

#include "../../Utils/RGBColor.h"
#include "../../Utils/Math/Vector3D.h"

/**
 * @class Material
 * @brief Abstract base class for rendering materials.
 *
 * The `Material` class provides a virtual interface for deriving specific
 * material types, defining how colors are computed based on position, normals,
 * and UVW texture coordinates. Materials also support various blending methods
 * through the `Method` enumeration.
 */
class Material {
public:
    /**
     * @enum Method
     * @brief Defines blending methods for combining colors.
     */
    enum Method {
        Base,           ///< The base material color.
        Add,            ///< Adds colors together.
        Subtract,       ///< Subtracts colors.
        Multiply,       ///< Multiplies colors.
        Divide,         ///< Divides colors.
        Darken,         ///< Chooses the darker color.
        Lighten,        ///< Chooses the lighter color.
        Screen,         ///< Screen blending.
        Overlay,        ///< Overlay blending.
        SoftLight,      ///< Soft light blending.
        Replace,        ///< Replaces the base color.
        EfficientMask,  ///< Efficient masking method.
        Bypass          ///< Passes through without blending.
    };

    /**
     * @brief Pure virtual function to calculate color based on surface parameters.
     * 
     * @param position The position in 3D space.
     * @param normal The normal vector at the position.
     * @param uvw The UVW texture coordinates.
     * @return The computed color as `RGBColor`.
     */
    virtual RGBColor GetRGB(const Vector3D& position, const Vector3D& normal, const Vector3D& uvw) = 0;

    /**
     * @brief Virtual destructor for proper cleanup in derived classes.
     */
    virtual ~Material() = default;
};
