/**
 * @file TriangleGroupDeformer.h
 * @brief Provides functionality to deform groups of 3D triangles in various ways.
 *
 * The TriangleGroupDeformer class allows for applying sinusoidal, dropwave, and other
 * deformation effects to groups of 3D triangles, with support for axis-aligned clipping.
 *
 * @date 22/12/2024
 * @version 1.0
 * @author Coela Can't
 */

#pragma once

#include "TriangleGroup.h"

/**
 * @class TriangleGroupDeformer
 * @brief Provides deformation effects for groups of triangles.
 *
 * This class supports applying various deformations to groups of triangles
 * such as sinusoidal, dropwave, and cosine interpolation. It also supports
 * axis-aligned clipping and custom deformations along selected axes.
 */
class TriangleGroupDeformer {
public:
    /**
     * @enum Axis
     * @brief Defines the axes available for deformations and clipping.
     */
    enum Axis {
        XAxis, ///< X-axis.
        YAxis, ///< Y-axis.
        ZAxis  ///< Z-axis.
    };

private:
    ITriangleGroup** objects; ///< Array of triangle group objects to deform.
    int objectCount = 0; ///< Number of triangle group objects.

    /**
     * @brief Checks if a given base position is clipped along a specific axis.
     * @param base The base position to check.
     * @param positive Whether to check the positive side of the axis.
     * @param valueCheckAxis The axis to check against.
     * @return True if the base position is clipped, otherwise false.
     */
    bool CheckClipAxis(Vector3D base, bool positive, Axis valueCheckAxis);

public:
    /**
     * @brief Constructor for a single triangle group.
     * @param object A single triangle group object to deform.
     */
    TriangleGroupDeformer(ITriangleGroup* object);

    /**
     * @brief Constructor for multiple triangle groups.
     * @param objects Array of triangle group objects to deform.
     * @param objectCount Number of triangle group objects.
     */
    TriangleGroupDeformer(ITriangleGroup** objects, int objectCount);

    /**
     * @brief Applies a sinusoidal deformation along a specified axis.
     * @param magnitude Magnitude of the deformation.
     * @param timeRatio Time progression ratio for the deformation.
     * @param periodModifier Modifier for the deformation period.
     * @param frequencyModifier Modifier for the deformation frequency.
     * @param axis The axis along which to apply the deformation.
     */
    void SinusoidalDeform(float magnitude, float timeRatio, float periodModifier, float frequencyModifier, Axis axis);

    /**
     * @brief Applies a dropwave deformation along a specified axis.
     * @param magnitude Magnitude of the deformation.
     * @param timeRatio Time progression ratio for the deformation.
     * @param periodModifier Modifier for the deformation period.
     * @param frequencyModifier Modifier for the deformation frequency.
     * @param axis The axis along which to apply the deformation.
     */
    void DropwaveDeform(float magnitude, float timeRatio, float periodModifier, float frequencyModifier, Axis axis);

    /**
     * @brief Applies a sine wave surface deformation along a specified axis.
     * @param offset Offset for the sine wave deformation.
     * @param magnitude Magnitude of the deformation.
     * @param timeRatio Time progression ratio for the deformation.
     * @param periodModifier Modifier for the deformation period.
     * @param frequencyModifier Modifier for the deformation frequency.
     * @param axis The axis along which to apply the deformation.
     */
    void SineWaveSurfaceDeform(Vector3D offset, float magnitude, float timeRatio, float periodModifier, float frequencyModifier, Axis axis);

    /**
     * @brief Applies a cosine interpolation deformation along a specified axis.
     * @param pointMultiplier Array of multipliers for points during deformation.
     * @param points Number of points to deform.
     * @param scale Scale of the deformation.
     * @param minAxis Minimum axis value for deformation.
     * @param maxAxis Maximum axis value for deformation.
     * @param selectionAxis Axis used for selecting points.
     * @param deformAxis Axis along which the deformation is applied.
     */
    void CosineInterpolationDeformer(float* pointMultiplier, int points, float scale, float minAxis, float maxAxis, Axis selectionAxis, Axis deformAxis);

    /**
     * @brief Applies axis-aligned clipping to the triangles.
     * @param positive Whether to clip along the positive side of the axis.
     * @param clipAxis Axis to apply the clipping.
     * @param valueCheckAxis Axis used to determine clipping.
     */
    void AxisZeroClipping(bool positive, Axis clipAxis, Axis valueCheckAxis);
};
