/**
 * @file RGBColor.h
 * @brief Defines the RGBColor class for managing and manipulating 16-bit RGB565 color values.
 *
 * The RGBColor class represents RGB colors in 16-bit format (RGB565) and provides methods for color manipulation,
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
 * @brief Represents a 16-bit RGB color (RGB565) and provides methods for manipulation.
 */
class RGBColor {
public:
    uint16_t color = 0; ///< Encoded 16-bit RGB565 color value.

    /**
     * @brief Default constructor initializes the color to black (0, 0, 0).
     */
    RGBColor() {}

    /**
     * @brief Constructor to initialize RGBColor with specified R, G, and B values.
     * @param R Red component (0-255).
     * @param G Green component (0-255).
     * @param B Blue component (0-255).
     */
    RGBColor(uint8_t R, uint8_t G, uint8_t B) {
        R = (R >> 3) & 0x1F;
        G = (G >> 2) & 0x3F;
        B = (B >> 3) & 0x1F;

        color = (R << 11) | (G << 5) | B;
    }

    /**
     * @brief Copy constructor.
     * @param rgbColor Reference to an existing RGBColor object.
     */
    RGBColor(const RGBColor& rgbColor) {
        this->R = rgbColor.R;
        this->G = rgbColor.G;
        this->B = rgbColor.B;
    }

    /**
     * @brief Constructor to initialize RGBColor from a Vector3D.
     * @param color Vector3D representing RGB values.
     */
    RGBColor(Vector3D color) {
        this->R = color.X;
        this->G = color.Y;
        this->B = color.Z;
    }

    /**
     * @brief Sets the RGB values of the color.
     * @param R Red component (0-255).
     * @param G Green component (0-255).
     * @param B Blue component (0-255).
     */
    void SetColor(uint8_t R, uint8_t G, uint8_t B) {
        this->R = R;
        this->G = G;
        this->B = B;
    }

    /**
     * @brief Scales the brightness of the color to a maximum value.
     * @param maxBrightness The maximum brightness value (0-255).
     * @return A new RGBColor with scaled brightness.
     */
    RGBColor Scale(uint8_t maxBrightness) {
        uint8_t sR = (uint8_t)R * (uint8_t)maxBrightness / 255;
        uint8_t sG = (uint8_t)G * (uint8_t)maxBrightness / 255;
        uint8_t sB = (uint8_t)B * (uint8_t)maxBrightness / 255;

        return RGBColor(
            Mathematics::Constrain(sR, 0, 255),
            Mathematics::Constrain(sG, 0, 255),
            Mathematics::Constrain(sB, 0, 255)
        );
    }

    /**
     * @brief Adds a value to each RGB component of the color.
     * @param value The value to add (0-255).
     * @return A new RGBColor with modified values.
     */
    RGBColor Add(uint8_t value) {
        return RGBColor(
            Mathematics::Constrain(R + value, 0, 255),
            Mathematics::Constrain(G + value, 0, 255),
            Mathematics::Constrain(B + value, 0, 255)
        );
    }

    /**
     * @brief Shifts the hue of the color by a specified angle in degrees.
     * @param hueDeg The angle in degrees to shift the hue.
     * @return A new RGBColor with the hue shifted.
     */
    RGBColor HueShift(float hueDeg) {
        float hueRad = hueDeg * Mathematics::MPI / 180.0f;
        float hueRat = 0.5f * sinf(hueRad / 2.0f);
        Vector3D rgbVec = Vector3D(R, G, B);
        Quaternion q = Quaternion(cosf(hueRad / 2.0f), hueRat, hueRat, hueRat);

        rgbVec = q.RotateVector(rgbVec).Constrain(0.0f, 255.0f);

        return RGBColor(rgbVec.X, rgbVec.Y, rgbVec.Z);
    }

    /**
     * @brief Interpolates between two colors based on a ratio.
     * @param a The starting color.
     * @param b The ending color.
     * @param ratio A value between 0 and 1 representing the interpolation factor.
     * @return The interpolated RGBColor.
     */
    static RGBColor InterpolateColors(RGBColor a, RGBColor b, float ratio) {
        return RGBColor(
            a.R * (1.0f - ratio) + b.R * ratio,
            a.G * (1.0f - ratio) + b.G * ratio,
            a.B * (1.0f - ratio) + b.B * ratio
        );
    }

    /**
     * @brief Converts the RGBColor to a string representation.
     * @return A string in the format "[R, G, B]".
     */
    String ToString() {
        return "[" + String(R) + ", " + String(G) + ", " + String(B) + "]";
    }
};
