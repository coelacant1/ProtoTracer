/**
 * @file Clock.h
 * @brief A material class for rendering a real-time clock with date and time overlays.
 *
 * The `Clock` class is designed to display time and date using a combination of text and materials.
 * It provides options for 24-hour or 12-hour time formats and allows customization of its size,
 * position, rotation, and material.
 *
 * @date 22/12/2024
 * @author Coela Can't
 */

#pragma once

#include "../../Static/SimpleMaterial.h" ///< For rendering static materials.
#include "../Overlays/Text/TextEngine.h" ///< For rendering text overlays.
#include "../../Material.h" ///< Base class for all materials.

/**
 * @class Clock
 * @brief Renders a real-time clock and date as a material.
 *
 * The `Clock` class uses a `TextEngine` to display formatted time and date, along with
 * a customizable material for rendering.
 */
class Clock : public Material {
private:
    TextEngine<3, 12> tE = TextEngine<3, 12>(false); ///< Text engine for rendering time and date.
    SimpleMaterial mat = SimpleMaterial(RGBColor(255, 255, 255)); ///< Default material for the clock.
    uint8_t hour; ///< Current hour.
    uint8_t minute; ///< Current minute.
    uint8_t second; ///< Current second.
    uint8_t day; ///< Current day.
    uint8_t month; ///< Current month.
    uint8_t year; ///< Current year (last two digits).
    uint8_t wDay; ///< Current weekday.
    bool hour24 = false; ///< Flag for 24-hour format (true) or 12-hour format (false).

public:
    /**
     * @brief Constructs a Clock instance with a specified time format.
     *
     * @param hour24 If true, uses 24-hour format; otherwise, uses 12-hour format.
     */
    Clock(bool hour24);

    /**
     * @brief Sets the material to be used for rendering the clock.
     *
     * @param material Pointer to a custom material.
     */
    void SetMaterial(Material* material);

    /**
     * @brief Sets the current time for the clock.
     *
     * @param hour The hour value (0-23 for 24-hour format, 0-12 for 12-hour format).
     * @param minute The minute value (0-59).
     * @param second The second value (0-59).
     */
    void SetTime(uint8_t hour, uint8_t minute, uint8_t second);

    /**
     * @brief Sets the current date for the clock.
     *
     * @param day The day value (1-31).
     * @param month The month value (1-12).
     * @param year The last two digits of the year (e.g., 24 for 2024).
     * @param wDay The weekday value (0-6, where 0 = Sunday).
     */
    void SetDate(uint8_t day, uint8_t month, uint8_t year, uint8_t wDay);

    /**
     * @brief Sets the size of the clock's rendered area.
     *
     * @param size A `Vector2D` representing the size (width and height).
     */
    void SetSize(Vector2D size);

    /**
     * @brief Sets the position of the clock in the rendered scene.
     *
     * @param position A `Vector2D` representing the position.
     */
    void SetPosition(Vector2D position);

    /**
     * @brief Sets the rotation of the clock in the rendered scene.
     *
     * @param rotation The rotation angle in degrees.
     */
    void SetRotation(float rotation);

    /**
     * @brief Updates the clock's time and date.
     *
     * This function is called to refresh the displayed time and date values.
     */
    void Update();

    /**
     * @brief Computes the color at a given position in the clock's material.
     *
     * This method is used for rendering the clock and applying effects.
     *
     * @param position The position in 3D space.
     * @param normal The surface normal vector.
     * @param uvw The texture coordinates.
     * @return The computed color as an `RGBColor`.
     */
    RGBColor GetRGB(const Vector3D& position, const Vector3D& normal, const Vector3D& uvw) override;
};
