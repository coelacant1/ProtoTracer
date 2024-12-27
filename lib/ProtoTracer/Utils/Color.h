/**
 * @file Color.h
 * @brief Abstract class template for defining and manipulating colors.
 *
 * @date 22/12/2024
 * @version 1.0
 * @author Coela Can't
 */

#pragma once

#include <Arduino.h>

/**
 * @class Color
 * @brief Abstract base class for representing a color with operations for modification and interpolation.
 * @tparam T Data type for the color channels (e.g., uint8_t, float).
 */
template <typename T>
class Color {
public:
    /**
     * @brief Constructor to initialize a color with red, green, and blue components.
     * @param R The red component of the color.
     * @param G The green component of the color.
     * @param B The blue component of the color.
     */
    virtual Color(T R, T G, T B) = 0;

    /**
     * @brief Virtual destructor.
     */
    virtual ~Color() {}

    /**
     * @brief Sets the color using red, green, and blue components.
     * @param R The red component of the color.
     * @param G The green component of the color.
     * @param B The blue component of the color.
     */
    virtual void SetColor(T R, T G, T B) = 0;

    /**
     * @brief Scales the color brightness to a maximum brightness level.
     * @param maxBrightness The maximum brightness value.
     * @return A new color scaled to the specified brightness.
     */
    virtual Color Scale(T maxBrightness) = 0;

    /**
     * @brief Adds a constant value to all color channels.
     * @param value The value to add to each channel.
     * @return A new color with the added value.
     */
    virtual Color Add(T value) = 0;

    /**
     * @brief Shifts the hue of the color by a specified angle.
     * @param hueDeg The hue shift in degrees.
     * @return A new color with the hue shifted.
     */
    virtual Color HueShift(float hueDeg) = 0;

    /**
     * @brief Interpolates between two colors based on a ratio.
     * @param color1 The first color.
     * @param color2 The second color.
     * @param ratio The interpolation ratio (0.0 - 1.0).
     * @return A new color that is the interpolated result.
     */
    virtual Color InterpolateColors(Color color1, Color color2, float ratio) = 0;

    /**
     * @brief Converts the color to a string representation.
     * @return A string representing the color in "R, G, B" format.
     */
    virtual String ToString() = 0;
};
