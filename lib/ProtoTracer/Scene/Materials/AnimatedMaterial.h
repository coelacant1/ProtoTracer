/**
 * @file AnimatedMaterial.h
 * @brief Declares the `AnimatedMaterial` class for time-based material updates.
 *
 * This class serves as a base for materials that require dynamic updates over time.
 *
 * @date 22/12/2024
 * @version 1.0
 * @author Coela Can't
 */

#pragma once

#include "Material.h"

/**
 * @class AnimatedMaterial
 * @brief Base class for dynamically updating materials.
 *
 * The `AnimatedMaterial` class provides an interface for materials that require
 * animation or time-based updates. Derived classes must implement the `Update` and
 * `GetMaterial` methods.
 */
class AnimatedMaterial : public Material {
public:
    /**
     * @brief Updates the material's state based on a ratio.
     *
     * This function is called to update the material's state over time.
     *
     * @param ratio A float value (0.0 to 1.0) representing the progression of time.
     */
    virtual void Update(float ratio) = 0;

    /**
     * @brief Retrieves the current material instance for rendering.
     *
     * @return A pointer to the current `Material` instance.
     */
    virtual Material* GetMaterial() = 0;
};
