/**
 * @file TVStatic.h
 * @brief A dynamic material for simulating TV static with various noise effects.
 *
 * The TVStatic class creates a realistic TV static effect using a combination of simplex noise,
 * gradients, and scanline effects. It provides an animated material that dynamically changes
 * over time, with additional customization options.
 *
 * @date 22/12/2024
 * @author Coela Can't
 */

#pragma once

#include "../AnimatedMaterial.h" // Base class for animated materials.
#include "../../../Utils/Signals/FunctionGenerator.h" // For generating animated signals.
#include "../Static/GradientMaterial.h" // For gradient-based coloring.
#include "../Static/SimplexNoise.h" // For generating noise patterns.
#include "../CombineMaterial.h" // For combining multiple materials.
#include "../../../Assets/Textures/Static/ColorTest.h" // For additional color test effects.

/**
 * @class TVStatic
 * @brief Simulates a TV static effect with noise, scanlines, and color variations.
 *
 * The TVStatic class generates a dynamic and customizable TV static effect using a combination
 * of simplex noise, gradient materials, scanline effects, and color overlays. The effect
 * includes animation based on function generators and allows for layering multiple materials.
 */
class TVStatic : public AnimatedMaterial {
private:
    FunctionGenerator colorWiggle1 = FunctionGenerator(FunctionGenerator::Sine, -40.0f, 20.0f, 1.95f); ///< Function for animating color wiggles.
    FunctionGenerator colorWiggle2 = FunctionGenerator(FunctionGenerator::Sine, -10.0f, 10.0f, 0.87f); ///< Secondary function for color variation.
    FunctionGenerator fGenMatGradient = FunctionGenerator(FunctionGenerator::Sine, 0.0f, 0.5f, 6.65f); ///< Function for gradient animation.

    RGBColor noiseSpectrum[5] = {
        RGBColor(255, 255, 255), 
        RGBColor(0, 0, 0), 
        RGBColor(255, 0, 0), 
        RGBColor(0, 255, 0), 
        RGBColor(0, 0, 255)
    }; ///< Spectrum for simplex noise coloring.

    GradientMaterial<5> gNoiseMat = GradientMaterial<5>(noiseSpectrum, 2.0f, false, true); ///< Gradient for simplex noise material.
    SimplexNoise<5> sNoise = SimplexNoise<5>(1, &gNoiseMat); ///< Simplex noise generator for TV static.

    float simplexNoiseDepth = 0.0f; ///< Depth value for simplex noise animation.

    RGBColor scanlineSpectrum[10] = {
        RGBColor(0, 0, 0), 
        RGBColor(0, 0, 0), 
        RGBColor(255, 255, 255), 
        RGBColor(0, 0, 0), 
        RGBColor(255, 255, 255), 
        RGBColor(255, 255, 255), 
        RGBColor(255, 255, 255), 
        RGBColor(0, 0, 0), 
        RGBColor(0, 0, 0), 
        RGBColor(255, 255, 255)
    }; ///< Spectrum for scanline effects.

    GradientMaterial<10> scanlineGradient = GradientMaterial<10>(scanlineSpectrum, 100.0f, false, false); ///< Scanline gradient material.

    ColorTest colorTest = ColorTest(Vector2D(192.0f, 96.0f), Vector2D(140.0f, 72.0f)); ///< Color test overlay.
    CombineMaterial<3> combineScanline = CombineMaterial<3>(); ///< Material combiner for layering effects.

public:
    /**
     * @brief Constructor for TVStatic.
     *
     * Initializes the materials and sets up the layers for combining the noise, scanlines,
     * and color effects.
     */
    TVStatic() {
        // Add simplex noise, scanline gradient, and color test to the combiner.
        combineScanline.AddMaterial(Material::Method::Base, &sNoise, 1.0f);
        combineScanline.AddMaterial(Material::Method::Multiply, &scanlineGradient, 0.75f);
        combineScanline.AddMaterial(Material::Method::Lighten, &colorTest, 1.0f);

        // Rotate scanline gradient for vertical alignment.
        scanlineGradient.SetRotationAngle(90.0f);
    }

    /**
     * @brief Updates the animation parameters for the TV static effect.
     *
     * @param ratio The elapsed time ratio for updating animations.
     */
    void Update(float ratio);

    /**
     * @brief Retrieves the combined material representing the TV static effect.
     *
     * @return Pointer to the combined material.
     */
    Material* GetMaterial();

    /**
     * @brief Computes the color at a given position in the material.
     *
     * This method combines the noise, scanline, and color test effects to generate
     * the final color.
     *
     * @param position The position in 3D space.
     * @param normal The surface normal vector.
     * @param uvw The texture coordinates.
     * @return The computed color as an RGBColor.
     */
    RGBColor GetRGB(const Vector3D& position, const Vector3D& normal, const Vector3D& uvw) override;
};
