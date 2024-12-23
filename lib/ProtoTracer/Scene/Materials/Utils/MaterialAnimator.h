/**
 * @file MaterialAnimator.h
 * @brief Provides functionality for animating transitions and blends between materials.
 *
 * This file defines the `MaterialAnimator` class, which enables dynamic material animations
 * by combining multiple materials and blending them with animated opacities.
 *
 * @date 22/12/2024
 * @author Coela Can't
 */

#pragma once

#include "../../../Animation/EasyEaseAnimator.h"
#include "../CombineMaterial.h"
#include "../Material.h"

/**
 * @class MaterialAnimator
 * @brief Animates transitions and blends between multiple materials.
 *
 * The `MaterialAnimator` class uses an `EasyEaseAnimator` for smooth transitions
 * between materials, allowing dynamic blending and effects in rendering systems.
 *
 * @tparam materialCount The maximum number of materials to animate.
 */
template<size_t materialCount>
class MaterialAnimator : public Material {
private:
    EasyEaseAnimator<materialCount> eEA = EasyEaseAnimator<materialCount>(IEasyEaseAnimator::Cosine); ///< Animator for easing transitions.
    CombineMaterial<materialCount> combineMaterial; ///< Combines multiple materials for rendering.
    float materialRatios[materialCount]; ///< Stores the opacity ratios for each material.
    Material* dictionary[materialCount]; ///< Holds the materials in the animator.
    uint8_t currentMaterials = 0; ///< Tracks the number of materials added.
    bool baseMaterialSet = false; ///< Indicates if the base material is set.

public:
    /**
     * @brief Default constructor for `MaterialAnimator`.
     */
    MaterialAnimator();

    /**
     * @brief Sets the base material for the animation.
     *
     * @param method The method of blending for the base material.
     * @param material Pointer to the base material.
     */
    void SetBaseMaterial(Material::Method method, Material* material);

    /**
     * @brief Adds a material to the animation with specified properties.
     *
     * @param method The blending method for this material.
     * @param material Pointer to the material to be added.
     * @param frames The number of frames for the transition.
     * @param minOpacity The minimum opacity of the material during the animation.
     * @param maxOpacity The maximum opacity of the material during the animation.
     */
    void AddMaterial(Material::Method method, Material* material, uint16_t frames, float minOpacity, float maxOpacity);

    /**
     * @brief Adds a specific frame for a material in the animation.
     *
     * @param material Reference to the material.
     * @param opacity The opacity value for the frame.
     */
    void AddMaterialFrame(Material& material, float opacity);

    /**
     * @brief Retrieves the current opacity of a material.
     *
     * @param material Reference to the material.
     * @return The current opacity of the material.
     */
    float GetMaterialOpacity(Material& material);

    /**
     * @brief Updates the animator, advancing the transitions.
     */
    void Update();

    /**
     * @brief Retrieves the color at a specific position, considering the blended materials.
     *
     * @param position The 3D position to sample the color.
     * @param normal The normal vector at the position.
     * @param uvw UVW coordinates at the position.
     * @return The blended RGB color at the specified position.
     */
    RGBColor GetRGB(const Vector3D& position, const Vector3D& normal, const Vector3D& uvw) override;
};

#include "MaterialAnimator.tpp" ///< Includes the template implementation.
