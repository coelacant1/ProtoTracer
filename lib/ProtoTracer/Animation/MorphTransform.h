/**
 * @file MorphTransform.h
 * @brief Declares the MorphTransform template class for handling 3D transformations.
 *
 * This file defines the MorphTransform class, which manages position, scale, and
 * rotation offsets for 3D transformations using a dictionary-based approach and
 * an animation controller.
 *
 * @author Coela Can't
 * @date 22/12/2024
 */

#pragma once

#include "IEasyEaseAnimator.h" ///< Include for animation controller interface.
#include "../Utils/Math/Vector3D.h" ///< Include for 3D vector operations.

/**
 * @class MorphTransform
 * @brief A template class for managing 3D transformations using morph targets.
 *
 * The MorphTransform class allows the definition of multiple morph targets with position,
 * scale, and rotation offsets. It integrates with an animation controller to dynamically
 * calculate the resulting transformation based on animation values.
 *
 * @tparam maxMorphs The maximum number of morph targets this class can handle.
 */
template<size_t maxMorphs>
class MorphTransform {
private:
    IEasyEaseAnimator* eEA; ///< Pointer to the animation controller.
    uint16_t dictionary[maxMorphs]; ///< Dictionary mapping morph targets to identifiers.
    uint16_t currentMorphs = 0; ///< Current number of morph targets.
    Vector3D positionOffsets[maxMorphs]; ///< Array of position offsets for morph targets.
    Vector3D scaleOffsets[maxMorphs]; ///< Array of scale offsets for morph targets.
    Vector3D rotationOffsets[maxMorphs]; ///< Array of rotation offsets for morph targets.

public:
    /**
     * @brief Constructs a MorphTransform object with an animation controller.
     *
     * @param eEA Pointer to the IEasyEaseAnimator instance.
     */
    MorphTransform(IEasyEaseAnimator* eEA);

    /**
     * @brief Adds a morph target with a position offset.
     *
     * @param dictionaryValue The identifier for the morph target.
     * @param positionOffset The position offset for the morph target.
     */
    void AddMorph(uint16_t dictionaryValue, Vector3D positionOffset);

    /**
     * @brief Adds a morph target with position and scale offsets.
     *
     * @param dictionaryValue The identifier for the morph target.
     * @param positionOffset The position offset for the morph target.
     * @param scaleOffset The scale offset for the morph target.
     */
    void AddMorph(uint16_t dictionaryValue, Vector3D positionOffset, Vector3D scaleOffset);

    /**
     * @brief Adds a morph target with position, scale, and rotation offsets.
     *
     * @param dictionaryValue The identifier for the morph target.
     * @param positionOffset The position offset for the morph target.
     * @param scaleOffset The scale offset for the morph target.
     * @param rotationOffset The rotation offset for the morph target.
     */
    void AddMorph(uint16_t dictionaryValue, Vector3D positionOffset, Vector3D scaleOffset, Vector3D rotationOffset);

    /**
     * @brief Sets the position offset for a specific morph target.
     *
     * @param dictionaryValue The identifier for the morph target.
     * @param positionOffset The new position offset.
     */
    void SetMorphPositionOffset(uint16_t dictionaryValue, Vector3D positionOffset);

    /**
     * @brief Sets the scale offset for a specific morph target.
     *
     * @param dictionaryValue The identifier for the morph target.
     * @param scaleOffset The new scale offset.
     */
    void SetMorphScaleOffset(uint16_t dictionaryValue, Vector3D scaleOffset);

    /**
     * @brief Sets the rotation offset for a specific morph target.
     *
     * @param dictionaryValue The identifier for the morph target.
     * @param rotationOffset The new rotation offset.
     */
    void SetMorphRotationOffset(uint16_t dictionaryValue, Vector3D rotationOffset);

    /**
     * @brief Retrieves the combined position offset for all active morph targets.
     *
     * @return The cumulative position offset.
     */
    Vector3D GetPositionOffset();

    /**
     * @brief Retrieves the combined scale offset for all active morph targets.
     *
     * @return The cumulative scale offset.
     */
    Vector3D GetScaleOffset();

    /**
     * @brief Retrieves the combined rotation offset for all active morph targets.
     *
     * @return The cumulative rotation offset.
     */
    Vector3D GetRotationOffset();
};

#include "MorphTransform.tpp" ///< Include the template implementation.
