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


    uint8_t p_supply[256] = {151,160,137,91,90,15, //this contains all the numbers between 0 and 255, these are put in a random order depending upon the seed
    131,13,201,95,96,53,194,233,7,225,140,36,103,30,69,142,8,99,37,240,21,10,23,
    190, 6,148,247,120,234,75,0,26,197,62,94,252,219,203,117,35,11,32,57,177,33,
    88,237,149,56,87,174,20,125,136,171,168, 68,175,74,165,71,134,139,48,27,166,
    77,146,158,231,83,111,229,122,60,211,133,230,220,105,92,41,55,46,245,40,244,
    102,143,54, 65,25,63,161, 1,216,80,73,209,76,132,187,208, 89,18,169,200,196,
    135,130,116,188,159,86,164,100,109,198,173,186, 3,64,52,217,226,250,124,123,
    5,202,38,147,118,126,255,82,85,212,207,206,59,227,47,16,58,17,182,189,28,42,
    223,183,170,213,119,248,152, 2,44,154,163, 70,221,153,101,155,167, 43,172,9,
    129,22,39,253, 19,98,108,110,79,113,224,232,178,185, 112,104,218,246,97,228,
    251,34,242,193,238,210,144,12,191,179,162,241, 81,51,145,235,249,14,239,107,
    49,192,214, 31,181,199,106,157,184, 84,204,176,115,121,50,45,127, 4,150,254,
    138,236,205,93,222,114,67,29,24,72,243,141,128,195,78,66,215,61,156,180};
    
    uint8_t p[256] = {151,160,137,91,90,15, //this contains all the numbers between 0 and 255, these are put in a random order depending upon the seed
    131,13,201,95,96,53,194,233,7,225,140,36,103,30,69,142,8,99,37,240,21,10,23,
    190, 6,148,247,120,234,75,0,26,197,62,94,252,219,203,117,35,11,32,57,177,33,
    88,237,149,56,87,174,20,125,136,171,168, 68,175,74,165,71,134,139,48,27,166,
    77,146,158,231,83,111,229,122,60,211,133,230,220,105,92,41,55,46,245,40,244,
    102,143,54, 65,25,63,161, 1,216,80,73,209,76,132,187,208, 89,18,169,200,196,
    135,130,116,188,159,86,164,100,109,198,173,186, 3,64,52,217,226,250,124,123,
    5,202,38,147,118,126,255,82,85,212,207,206,59,227,47,16,58,17,182,189,28,42,
    223,183,170,213,119,248,152, 2,44,154,163, 70,221,153,101,155,167, 43,172,9,
    129,22,39,253, 19,98,108,110,79,113,224,232,178,185, 112,104,218,246,97,228,
    251,34,242,193,238,210,144,12,191,179,162,241, 81,51,145,235,249,14,239,107,
    49,192,214, 31,181,199,106,157,184, 84,204,176,115,121,50,45,127, 4,150,254,
    138,236,205,93,222,114,67,29,24,72,243,141,128,195,78,66,215,61,156,180};

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
