/**
 * @file CombineMaterial.h
 * @brief Combines multiple materials with different blending methods and opacities.
 *
 * This class allows combining materials for complex visual effects.
 *
 * @date 22/12/2024
 * @version 1.0
 * @author Coela Can't
 */

#pragma once

#include "Material.h"
#include "../../Utils/Math/Vector2D.h"
#include "../../Utils/Math/Vector3D.h"

/**
 * @class CombineMaterial
 * @brief Combines multiple materials with specified blending methods and opacities.
 *
 * The `CombineMaterial` class allows for the creation of composite materials by blending
 * multiple materials using different methods and opacities. Each material can have a unique
 * blending method and opacity level.
 *
 * @tparam materialCount Maximum number of materials to combine.
 */
template<size_t materialCount>
class CombineMaterial : public Material {
private:
    Method method[materialCount]; ///< Array of blending methods for each material.
    Material* materials[materialCount]; ///< Array of pointers to materials.
    float opacity[materialCount]; ///< Array of opacities for each material.
    uint8_t materialsAdded = 0; ///< Counter for added materials.

public:
    /**
     * @brief Constructs an empty `CombineMaterial` instance.
     */
    CombineMaterial();

    /**
     * @brief Adds a new material to the combination.
     * 
     * @param method The blending method to use for the material.
     * @param material A pointer to the material to add.
     * @param opacity The opacity level of the material (0.0 to 1.0).
     */
    void AddMaterial(Method method, Material* material, float opacity);

    /**
     * @brief Sets the blending method for a specific material.
     * 
     * @param index The index of the material.
     * @param method The new blending method.
     */
    void SetMethod(uint8_t index, Method method);

    /**
     * @brief Sets the opacity for a specific material.
     * 
     * @param index The index of the material.
     * @param opacity The new opacity value (0.0 to 1.0).
     */
    void SetOpacity(uint8_t index, float opacity);

    /**
     * @brief Replaces a material at a specific index.
     * 
     * @param index The index of the material to replace.
     * @param material A pointer to the new material.
     */
    void SetMaterial(uint8_t index, Material* material);

    /**
     * @brief Calculates the resulting color by combining all materials.
     *
     * @param position The position in 3D space.
     * @param normal The normal vector at the position.
     * @param uvw The UVW coordinates for texture mapping.
     * @return The resulting combined `RGBColor`.
     */
    RGBColor GetRGB(const Vector3D& position, const Vector3D& normal, const Vector3D& uvw) override;
};

#include "CombineMaterial.tpp"
