/**
 * @file ObjectDeformer.h
 * @brief Defines the `ObjectDeformer` class for deforming 3D objects using various transformations.
 *
 * This class provides methods for applying perspective, sinusoidal, and other custom deformations
 * to one or more 3D objects.
 *
 * @date 22/12/2024
 * @version 1.0
 * @author Coela Can't
 */

#pragma once

#include "Object3D.h"

/**
 * @class ObjectDeformer
 * @brief Applies geometric transformations to one or more 3D objects.
 *
 * The `ObjectDeformer` class allows for various deformations, including perspective,
 * sinusoidal waves, and surface-based transformations. It supports operations on both
 * individual objects and collections of objects.
 */
class ObjectDeformer {
public:
    /**
     * @enum Axis
     * @brief Represents the axis of deformation or clipping.
     */
    enum Axis {
        XAxis, ///< X-axis
        YAxis, ///< Y-axis
        ZAxis  ///< Z-axis
    };

private:
    Object3D** objects;   ///< Array of pointers to `Object3D` instances to be deformed.
    int objectCount = 0;  ///< Number of objects in the `objects` array.

    /**
     * @brief Checks if a given axis value exceeds a clipping threshold.
     *
     * @param base The base vector to check.
     * @param positive Determines whether the check is for positive or negative values.
     * @param valueCheckAxis The axis to check for clipping.
     * @return True if the value exceeds the threshold, false otherwise.
     */
    bool CheckClipAxis(Vector3D base, bool positive, Axis valueCheckAxis);

public:
    /**
     * @brief Constructs an `ObjectDeformer` for a single object.
     *
     * @param object Pointer to the `Object3D` to be deformed.
     */
    ObjectDeformer(Object3D* object);

    /**
     * @brief Constructs an `ObjectDeformer` for multiple objects.
     *
     * @param objects Pointer to an array of `Object3D` pointers.
     * @param objectCount Number of objects in the array.
     */
    ObjectDeformer(Object3D** objects, int objectCount);

    /**
     * @brief Applies a perspective deformation to the object(s).
     *
     * @param scaleRatio Scaling factor for the deformation.
     * @param center Center point for the perspective effect.
     * @param axis Axis along which the deformation is applied.
     */
    void PerspectiveDeform(float scaleRatio, Vector3D center, Axis axis);

    /**
     * @brief Applies a sinusoidal deformation to the object(s).
     *
     * @param magnitude Magnitude of the sinusoidal wave.
     * @param timeRatio Ratio for time-based animation.
     * @param periodModifier Modifier for the wave's period.
     * @param frequencyModifier Modifier for the wave's frequency.
     * @param axis Axis along which the deformation is applied.
     */
    void SinusoidalDeform(float magnitude, float timeRatio, float periodModifier, float frequencyModifier, Axis axis);

    /**
     * @brief Applies a dropwave deformation to the object(s).
     *
     * @param magnitude Magnitude of the dropwave effect.
     * @param timeRatio Ratio for time-based animation.
     * @param periodModifier Modifier for the wave's period.
     * @param frequencyModifier Modifier for the wave's frequency.
     * @param axis Axis along which the deformation is applied.
     */
    void DropwaveDeform(float magnitude, float timeRatio, float periodModifier, float frequencyModifier, Axis axis);

    /**
     * @brief Applies a sine wave surface deformation to the object(s).
     *
     * @param offset Offset for the deformation center.
     * @param magnitude Magnitude of the wave.
     * @param timeRatio Ratio for time-based animation.
     * @param periodModifier Modifier for the wave's period.
     * @param frequencyModifier Modifier for the wave's frequency.
     * @param axis Axis along which the deformation is applied.
     */
    void SineWaveSurfaceDeform(Vector3D offset, float magnitude, float timeRatio, float periodModifier, float frequencyModifier, Axis axis);

    /**
     * @brief Applies cosine interpolation deformation to the object(s).
     *
     * @param pointMultiplier Array of multipliers for point deformation.
     * @param points Number of points to deform.
     * @param scale Scaling factor for the deformation.
     * @param minAxis Minimum axis value for the deformation range.
     * @param maxAxis Maximum axis value for the deformation range.
     * @param selectionAxis Axis used for selecting points to deform.
     * @param deformAxis Axis along which the deformation is applied.
     */
    void CosineInterpolationDeformer(float* pointMultiplier, int points, float scale, float minAxis, float maxAxis, Axis selectionAxis, Axis deformAxis);

    /**
     * @brief Clips the object(s) along a specified axis.
     *
     * @param positive Determines whether to clip positive or negative values.
     * @param clipAxis Axis along which clipping is performed.
     * @param valueCheckAxis Axis used for value checks during clipping.
     */
    void AxisZeroClipping(bool positive, Axis clipAxis, Axis valueCheckAxis);
};
