/**
 * @file SpectrumAnalyzer.h
 * @brief A material for visualizing audio data as a colorful spectrum analyzer.
 *
 * This file defines the SpectrumAnalyzer class, which uses audio data to generate
 * a visually dynamic spectrum effect, with options for mirroring, flipping, and bouncing.
 *
 * @date 22/12/2024
 * @author Coela Can't
 */

#pragma once

#include "../Material.h" ///< Base material class.
#include "../Static/GradientMaterial.h" ///< For managing gradient colors.
#include "../../../Physics/Utils/BouncePhysics.h" ///< For adding bounce physics to spectrum data.

/**
 * @class SpectrumAnalyzer
 * @brief A material that visualizes audio data as a spectrum.
 *
 * The SpectrumAnalyzer class processes audio data to create a colorful and dynamic
 * spectrum visualization with options for customization, including mirroring and flipping.
 */
class SpectrumAnalyzer : public Material {
private:
    BouncePhysics* bPhy[128]; ///< Array of bounce physics objects for each frequency bin.
    Vector2D size; ///< Size of the visualization area.
    Vector2D offset; ///< Offset position of the visualization area.
    float angle = 0.0f; ///< Rotation angle of the visualization.
    float hueAngle = 0.0f; ///< Hue adjustment angle for the spectrum colors.
    uint8_t colors; ///< Number of colors in the gradient.
    float* data; ///< Pointer to the input audio data.
    float bounceData[128]; ///< Processed bounce data for visualization.
    uint8_t bins = 128; ///< Number of frequency bins.
    bool mirrorY = false; ///< Whether to mirror the visualization along the Y-axis.
    bool flipY = false; ///< Whether to flip the visualization along the Y-axis.
    bool bounce = false; ///< Whether to apply bouncing animation to the spectrum.

    RGBColor rainbowSpectrum[6] = {
        RGBColor(255, 0, 0), 
        RGBColor(255, 255, 0), 
        RGBColor(0, 255, 0), 
        RGBColor(0, 255, 255), 
        RGBColor(0, 0, 255), 
        RGBColor(255, 0, 255)
    }; ///< Predefined rainbow color gradient.

    GradientMaterial<6> gM = GradientMaterial<6>(rainbowSpectrum, 1.0f, false); ///< Gradient material for coloring the spectrum.
    Material* material; ///< Optional sub-material for additional effects.

public:
    /**
     * @brief Constructor for SpectrumAnalyzer.
     *
     * @param size The size of the visualization area.
     * @param offset The offset position of the visualization.
     * @param bounce Enables bouncing animation for the spectrum.
     * @param flipY Enables flipping the visualization along the Y-axis.
     * @param mirrorY Enables mirroring the visualization along the Y-axis.
     */
    SpectrumAnalyzer(Vector2D size, Vector2D offset, bool bounce = false, bool flipY = false, bool mirrorY = false);

    /**
     * @brief Destructor for SpectrumAnalyzer.
     */
    ~SpectrumAnalyzer();

    /**
     * @brief Sets the mirroring state for the visualization.
     *
     * @param state True to enable mirroring along the Y-axis, false to disable.
     */
    void SetMirrorYState(bool state);

    /**
     * @brief Sets the flipping state for the visualization.
     *
     * @param state True to enable flipping along the Y-axis, false to disable.
     */
    void SetFlipYState(bool state);

    /**
     * @brief Sets a custom material for additional effects.
     *
     * @param material Pointer to the custom material.
     */
    void SetMaterial(Material* material);

    /**
     * @brief Retrieves the Fourier data used for visualization.
     *
     * @return Pointer to the array of Fourier data.
     */
    float* GetFourierData();

    /**
     * @brief Sets the size of the visualization area.
     *
     * @param size The new size as a Vector2D.
     */
    void SetSize(Vector2D size);

    /**
     * @brief Sets the position of the visualization area.
     *
     * @param offset The new position as a Vector2D.
     */
    void SetPosition(Vector2D offset);

    /**
     * @brief Sets the rotation angle of the visualization.
     *
     * @param angle The rotation angle in degrees.
     */
    void SetRotation(float angle);

    /**
     * @brief Sets the hue adjustment angle for the spectrum colors.
     *
     * @param hueAngle The hue adjustment angle in degrees.
     */
    void SetHueAngle(float hueAngle);

    /**
     * @brief Updates the spectrum visualization with new audio data.
     *
     * @param readData Pointer to the new audio data.
     */
    void Update(float* readData);

    /**
     * @brief Computes the color at a given position in the material.
     *
     * @param position The position in 3D space.
     * @param normal The surface normal vector.
     * @param uvw The texture coordinates.
     * @return The computed color as an RGBColor.
     */
    RGBColor GetRGB(const Vector3D& position, const Vector3D& normal, const Vector3D& uvw) override;
};
