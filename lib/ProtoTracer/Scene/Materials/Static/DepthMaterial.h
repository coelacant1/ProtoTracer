/**
 * @file DepthMaterial.h
 * @brief Defines a material that maps depth along a specified axis to RGB values.
 *
 * The `DepthMaterial` class uses a gradient to represent depth values along a specified axis.
 * This is particularly useful for visualizing 3D spatial data as a color gradient.
 *
 * @date 22/12/2024
 * @author Coela Can't
 */

#pragma once

#include "../Material.h" // Base class for materials.
#include "../../../Utils/Math/Mathematics.h" // Utilities for mathematical operations.
#include "GradientMaterial.h" // For creating gradient-based color mapping.

/**
 * @class DepthMaterial
 * @brief Maps depth along a specified axis to an RGB color using a gradient.
 *
 * The `DepthMaterial` class converts spatial depth data into RGB colors based on a gradient.
 * It supports customization of the depth axis and offset for precise visualization.
 */
class DepthMaterial : public Material {
public:
    /**
     * @enum Axis
     * @brief Specifies the axis along which depth is calculated.
     */
    enum Axis {
        X, ///< Depth along the X-axis.
        Y, ///< Depth along the Y-axis.
        Z  ///< Depth along the Z-axis.
    };

private:
    RGBColor spectrum[4] = { RGBColor(0, 255, 0), RGBColor(255, 0, 0), RGBColor(0, 255, 0), RGBColor(0, 0, 255) }; ///< Gradient spectrum for depth mapping.
    GradientMaterial<4> gNoiseMat = GradientMaterial<4>(spectrum, 2.0f, false); ///< Gradient material for depth mapping.
    Axis axis; ///< Axis along which depth is calculated.
    float depth = 0.0f; ///< Depth scaling factor.
    float zOffset = 0.0f; ///< Z-axis offset for depth calculation.

public:
    /**
     * @brief Constructs a DepthMaterial instance.
     *
     * @param axis The axis along which depth is calculated.
     * @param depth The scaling factor for depth.
     * @param zOffset The offset along the Z-axis for depth calculation.
     */
    DepthMaterial(Axis axis, float depth, float zOffset);

    /**
     * @brief Calculates the RGB color at a given position based on depth.
     *
     * @param position The position in 3D space.
     * @param normal The surface normal vector.
     * @param uvw The texture coordinates.
     * @return The calculated RGB color based on depth.
     */
    RGBColor GetRGB(const Vector3D& position, const Vector3D& normal, const Vector3D& uvw) override;
};
