/**
 * @file LightMaterial.h
 * @brief A material class that incorporates multiple light sources for advanced lighting effects.
 *
 * The `LightMaterial` class provides an interface for managing a set of light sources
 * and calculating the resulting illumination for a given material.
 *
 * @date 22/12/2024
 * @author Coela Can't
 */

#pragma once

#include "../Material.h" ///< Base class for materials.
#include "../../../Utils/Math/Vector2D.h" ///< Vector utilities.
#include "../../../Renderer/Lights/Light.h" ///< Light source definitions.

/**
 * @class LightMaterial
 * @brief A material class that incorporates multiple light sources for rendering.
 *
 * This template-based material class allows for dynamic lighting by utilizing a fixed number
 * of light sources. The lighting calculations take into account position, normal, and texture
 * coordinates to determine the final color output.
 *
 * @tparam lightCount The number of lights included in the material.
 */
template<size_t lightCount>
class LightMaterial : public Material {
private:
    Light lights[lightCount]; ///< Array of lights used for lighting calculations.

public:
    /**
     * @brief Constructs a `LightMaterial` object with the specified number of lights.
     */
    LightMaterial();

    /**
     * @brief Retrieves the array of lights.
     *
     * @return Pointer to the array of `Light` objects.
     */
    Light* GetLights();

    /**
     * @brief Retrieves the number of lights in the material.
     *
     * @return The number of lights (`lightCount`).
     */
    uint8_t GetLightCount();

    /**
     * @brief Calculates the RGB color at a specific position using the light sources.
     *
     * @param position 3D position in the scene.
     * @param normal Normal vector at the position.
     * @param uvw Texture coordinates at the position.
     * @return The calculated RGB color.
     */
    RGBColor GetRGB(const Vector3D& position, const Vector3D& normal, const Vector3D& uvw) override;
};

#include "LightMaterial.tpp" ///< Include the template implementation.
