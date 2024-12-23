/**
 * @file AudioReactiveGradient.h
 * @brief A material class for creating an audio-reactive gradient effect.
 *
 * This file defines the AudioReactiveGradient class, which creates a gradient effect
 * that reacts to audio data, with configurable options for size, position, rotation,
 * hue, and circular patterns.
 *
 * @date 22/12/2024
 * @author Coela Can't
 */

#pragma once

#include "../Material.h" ///< Base class for material types.
#include "../Static/GradientMaterial.h" ///< Include for static gradient materials.
#include "../../../Physics/Utils/BouncePhysics.h" ///< Include for bounce physics utilities.
#include "../../../Utils/Math/Mathematics.h" ///< Include for mathematical utilities.

/**
 * @class AudioReactiveGradient
 * @brief A material class for creating an audio-reactive gradient effect.
 *
 * The AudioReactiveGradient class generates a gradient effect that dynamically reacts
 * to audio data. It supports features like bouncing effects, circular patterns, and
 * customizable gradient colors.
 */
class AudioReactiveGradient : public Material {
private:
    BouncePhysics* bPhy[128]; ///< Array of BouncePhysics instances for handling dynamic bouncing.
    Vector2D size; ///< The size of the gradient area.
    Vector2D offset; ///< The offset of the gradient from the origin.
    float angle = 0.0f; ///< Rotation angle of the gradient.
    float hueAngle = 0.0f; ///< Hue angle for color adjustments.
    float radius = 0.0f; ///< Radius for circular gradient patterns.
    uint8_t colors; ///< Number of colors in the gradient.
    float* data; ///< Pointer to the audio data array.
    float bounceData[128]; ///< Processed bounce data for audio reactivity.
    uint8_t bins = 128; ///< Number of bins for audio data processing.
    bool bounce = false; ///< Flag indicating if bouncing effects are enabled.
    bool circular = false; ///< Flag indicating if circular patterns are enabled.

    RGBColor rainbowSpectrum[6] = {RGBColor(255, 0, 0), RGBColor(255, 255, 0), RGBColor(0, 255, 0), RGBColor(0, 255, 255), RGBColor(0, 0, 255), RGBColor(255, 0, 255)}; ///< Predefined rainbow colors.
    GradientMaterial<6> gM = GradientMaterial<6>(rainbowSpectrum, 1.0f, false); ///< Gradient material for the rainbow spectrum.

    Material* material; ///< Pointer to a secondary material for additional effects.

public:
    /**
     * @brief Constructs an AudioReactiveGradient with specified parameters.
     *
     * @param size The size of the gradient.
     * @param offset The offset of the gradient.
     * @param bounce Enable or disable bouncing effects.
     * @param circular Enable or disable circular patterns.
     */
    AudioReactiveGradient(Vector2D size, Vector2D offset, bool bounce = false, bool circular = false);

    /**
     * @brief Destroys the AudioReactiveGradient instance.
     */
    ~AudioReactiveGradient();

    /**
     * @brief Sets a secondary material for additional effects.
     *
     * @param material Pointer to the secondary material.
     */
    void SetMaterial(Material* material);

    /**
     * @brief Retrieves the Fourier-transformed audio data.
     *
     * @return Pointer to the audio data array.
     */
    float* GetFourierData();

    /**
     * @brief Sets the size of the gradient.
     *
     * @param size The new size as a Vector2D.
     */
    void SetSize(Vector2D size);

    /**
     * @brief Sets the position of the gradient.
     *
     * @param offset The new position offset as a Vector2D.
     */
    void SetPosition(Vector2D offset);

    /**
     * @brief Sets the rotation angle of the gradient.
     *
     * @param angle The new rotation angle in degrees.
     */
    void SetRotation(float angle);

    /**
     * @brief Sets the hue angle for color adjustments.
     *
     * @param hueAngle The new hue angle in degrees.
     */
    void SetHueAngle(float hueAngle);

    /**
     * @brief Sets the radius for circular gradient patterns.
     *
     * @param radius The new radius value.
     */
    void SetRadius(float radius);

    /**
     * @brief Updates the gradient based on new audio data.
     *
     * @param readData Pointer to the audio data array.
     */
    void Update(float* readData);

    /**
     * @brief Retrieves the color of the gradient at a specific position.
     *
     * @param position The position in 3D space.
     * @param normal The surface normal vector.
     * @param uvw The texture coordinates.
     * @return The computed color as an RGBColor.
     */
    RGBColor GetRGB(const Vector3D& position, const Vector3D& normal, const Vector3D& uvw) override;
};