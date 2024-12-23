/**
 * @file SimplexNoise.h
 * @brief A material class that generates and applies Simplex Noise.
 *
 * This class utilizes Simplex Noise algorithms for 2D and 3D noise generation,
 * mapping the noise values to colors through a gradient material.
 *
 * @date 22/12/2024
 * @author Coela Can't
 */

#pragma once

#include <cstdlib>
#include "../Material.h"
#include "../../../Utils/Math/Mathematics.h"
#include "../../../Utils/Math/Vector3D.h"
#include "../Static/GradientMaterial.h"

/**
 * @class SimplexNoise
 * @brief A material class for rendering Simplex Noise.
 *
 * This template-based class generates noise values using the Simplex Noise algorithm
 * and maps the values to colors using a `GradientMaterial`.
 *
 * @tparam colors The number of colors in the gradient material.
 */
template<size_t colors>
class SimplexNoise : public Material {
private:
    GradientMaterial<colors>* gradientMaterial; ///< GradientMaterial used to map noise values to colors.

    Vector3D noiseScale = Vector3D(1, 1, 1); ///< Scaling factor for the noise generation.
    const float F2 = 0.5f * (sqrtf(3.0f) - 1.0f); ///< Simplex Noise constants for 2D.
    const float G2 = (3.0f - sqrtf(3.0f)) / 6.0f; ///< Simplex Noise constants for 2D.
    const float F3 = 1.0f / 3.0f; ///< Simplex Noise constants for 3D.
    const float G3 = 1.0f / 6.0f; ///< Simplex Noise constants for 3D.
    float zPosition = 0.0f; ///< Z-position for 3D noise.

    // Gradient vectors for noise generation.
    Vector3D grad3[12] = {Vector3D(1, 1, 0), Vector3D(-1, 1, 0), Vector3D(1, -1, 0), Vector3D(-1, -1, 0),  
                          Vector3D(1, 0, 1), Vector3D(-1, 0, 1), Vector3D(1, 0, -1), Vector3D(-1, 0, -1), 
                          Vector3D(0, 1, 1), Vector3D(0, -1, 1), Vector3D(0, 1, -1), Vector3D(0, -1, -1) };

    // Permutation arrays for noise generation.
    uint8_t perm[512]; ///< Permutation table for noise generation.
    uint8_t permMod12[512]; ///< Permutation table modulo 12 for gradient selection.

    /**
     * @brief Initializes the permutation tables based on the seed.
     *
     * @param seed The seed for randomizing the permutation tables.
     */
    void InitializePermutation(int seed);

public:
    /**
     * @brief Constructs a SimplexNoise instance.
     *
     * @param seed The seed for noise generation.
     * @param gradientMaterial Pointer to a `GradientMaterial` for mapping noise to colors.
     */
    SimplexNoise(int seed, GradientMaterial<colors>* gradientMaterial);

    /**
     * @brief Generates 2D Simplex Noise.
     *
     * @param xin X-coordinate.
     * @param yin Y-coordinate.
     * @return The noise value at the given coordinates.
     */
    float Noise(float xin, float yin);

    /**
     * @brief Generates 3D Simplex Noise.
     *
     * @param xin X-coordinate.
     * @param yin Y-coordinate.
     * @param zin Z-coordinate.
     * @return The noise value at the given coordinates.
     */
    float Noise(float xin, float yin, float zin);

    /**
     * @brief Sets the scale for noise generation.
     *
     * @param noiseScale A Vector3D representing the scaling factors for X, Y, and Z.
     */
    void SetScale(Vector3D noiseScale);

    /**
     * @brief Sets the Z-position for 3D noise generation.
     *
     * @param zPosition The Z-coordinate for noise generation.
     */
    void SetZPosition(float zPosition);

    /**
     * @brief Retrieves the color for a given position based on the noise value.
     *
     * @param position 3D position in the scene.
     * @param normal Normal vector at the position (not used for this material).
     * @param uvw Texture coordinates at the position (not used for this material).
     * @return The RGB color corresponding to the noise value at the position.
     */
    RGBColor GetRGB(const Vector3D& position, const Vector3D& normal, const Vector3D& uvw) override;
};

#include "SimplexNoise.tpp"
