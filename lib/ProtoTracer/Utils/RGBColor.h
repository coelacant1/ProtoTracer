/**
 * @file RGBColor.h
 * @brief Defines the RGBColor class for managing and manipulating RGB color values.
 *
 * The RGBColor class provides functionality to represent and manipulate RGB color values,
 * including scaling brightness, adding values, hue shifting, and interpolating between colors.
 *
 * @date 22/12/2024
 * @version 1.0
 * @author Coela Can't
 */

#pragma once

#include "Math/Mathematics.h"
#include "Math/Quaternion.h"
#include "Math/Vector3D.h"

/**
 * @class RGBColor
 * @brief Represents an RGB color and provides methods for manipulation.
 */
class RGBColor {
public:
    uint8_t R = 0; ///< Red component of the color (0-255).
    uint8_t G = 0; ///< Green component of the color (0-255).
    uint8_t B = 0; ///< Blue component of the color (0-255).

    /**
     * @brief Default constructor initializes the color to black (0, 0, 0).
     */
    RGBColor();

    /**
     * @brief Constructor to initialize RGBColor with specified R, G, and B values.
     * @param R Red component (0-255).
     * @param G Green component (0-255).
     * @param B Blue component (0-255).
     */
    RGBColor(const uint8_t& R, const uint8_t& G, const uint8_t& B);

    /**
     * @brief Copy constructor.
     * @param rgbColor Reference to an existing RGBColor object.
     */
    RGBColor(const RGBColor& rgbColor);

    /**
     * @brief Constructor to initialize RGBColor from a Vector3D.
     * @param color Vector3D representing RGB values.
     */
    RGBColor(const Vector3D& color);

    /**
     * @brief Sets the RGB values of the color.
     * @param R Red component (0-255).
     * @param G Green component (0-255).
     * @param B Blue component (0-255).
     */
    void SetColor(const uint8_t& R, const uint8_t& G, const uint8_t& B);

    /**
     * @brief Scales the brightness of the color to a maximum value.
     * @param maxBrightness The maximum brightness value (0-255).
     * @return A new RGBColor with scaled brightness.
     */
    RGBColor Scale(const uint8_t& maxBrightness);

    /**
     * @brief Adds a value to each RGB component of the color.
     * @param value The value to add (0-255).
     * @return A new RGBColor with modified values.
     */
    RGBColor Add(const uint8_t& value);

    /**
     * @brief Shifts the hue of the color by a specified angle in degrees.
     * @param hueDeg The angle in degrees to shift the hue.
     * @return A new RGBColor with the hue shifted.
     */
    RGBColor HueShift(const float& hueDeg);

    /**
     * @brief Interpolates between two colors based on a ratio.
     * @param a The starting color.
     * @param b The ending color.
     * @param ratio A value between 0 and 1 representing the interpolation factor.
     * @return The interpolated RGBColor.
     */
    static RGBColor InterpolateColors(const RGBColor& a, const RGBColor& b, const float& ratio);

    /**
     * @brief Converts the RGBColor to a string representation.
     * @return A string in the format "(R, G, B)".
     */
    String ToString();
};
