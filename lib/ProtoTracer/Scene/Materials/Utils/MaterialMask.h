/**
 * @file MaterialMask.h
 * @brief Defines the `MaterialMask` class, which blends materials with a mask defined by a shape.
 *
 * The `MaterialMask` class allows rendering of one material within a defined shape 
 * and another material outside of it, with support for adjustable opacity.
 *
 * @date 22/12/2024
 * @version 1.0
 * @author Coela Can't
 */

#pragma once

#include "../Material.h"
#include "../../../Renderer/Primitives/2D/Shape.h"

/**
 * @class MaterialMask
 * @brief Combines two materials using a shape as a mask.
 *
 * The `MaterialMask` class provides functionality to blend two materials—one within 
 * a defined shape and another for the outer region. Opacity can be adjusted for 
 * blending effects.
 */
class MaterialMask : public Material {
private:
    Material* materialShape; ///< The material rendered inside the mask shape.
    Material* materialOuter; ///< The material rendered outside the mask shape.
    Shape* shape; ///< Defines the masked area for blending the materials.
    float opacity = 1.0f; ///< Controls the opacity of the mask effect.

public:
    /**
     * @brief Constructs a `MaterialMask` with given materials and shape.
     *
     * @param materialShape Pointer to the material rendered within the shape.
     * @param materialOuter Pointer to the material rendered outside the shape.
     * @param shape Pointer to the shape used as the mask.
     */
    MaterialMask(Material* materialShape, Material* materialOuter, Shape* shape);

    /**
     * @brief Sets the opacity of the mask effect.
     *
     * @param opacity The opacity value (0.0 to 1.0).
     */
    void SetOpacity(float opacity);

    /**
     * @brief Provides a reference to the opacity value.
     *
     * Useful for dynamically modifying opacity during runtime.
     *
     * @return Pointer to the opacity value.
     */
    float* GetOpacityReference();

    /**
     * @brief Retrieves the color at a specific position based on the mask.
     *
     * Determines if the position lies within the mask shape and blends the 
     * materials accordingly.
     *
     * @param position The 3D position to sample the color.
     * @param normal The normal vector at the position.
     * @param uvw UVW coordinates at the position.
     * @return The blended RGB color based on the mask and materials.
     */
    RGBColor GetRGB(const Vector3D& position, const Vector3D& normal, const Vector3D& uvw) override;
};
