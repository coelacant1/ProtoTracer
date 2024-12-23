/**
 * @file Pixel.h
 * @brief Declares the Pixel class for managing pixel data and relationships in a 2D grid.
 *
 * This file defines the Pixel class, which represents a single pixel with positional data,
 * color, and connections to neighboring pixels in a grid.
 *
 * @author Coela Can't
 * @date 22/12/2024
 */

#pragma once

#include "../../Utils/RGBColor.h" ///< Include for color representation.
#include "../../Utils/Math/Vector2D.h" ///< Include for 2D positional data.

/**
 * @class Pixel
 * @brief Represents a pixel in a 2D grid with positional, color, and neighbor information.
 *
 * The Pixel class stores data for a single pixel, including its position, color, and connections
 * to neighboring pixels (up, down, left, right). It provides methods for managing these relationships
 * and accessing pixel properties.
 */
class Pixel {
private:
    const Vector2D* position; ///< Pointer to the pixel's position in 2D space.
    bool sorted = false; ///< Indicates whether the pixel has been processed in sorting algorithms.
    bool upExists = false; ///< Indicates if a pixel exists above this pixel.
    bool downExists = false; ///< Indicates if a pixel exists below this pixel.
    bool leftExists = false; ///< Indicates if a pixel exists to the left of this pixel.
    bool rightExists = false; ///< Indicates if a pixel exists to the right of this pixel.

    Pixel* up = nullptr; ///< Pointer to the pixel above this pixel.
    Pixel* down = nullptr; ///< Pointer to the pixel below this pixel.
    Pixel* left = nullptr; ///< Pointer to the pixel to the left of this pixel.
    Pixel* right = nullptr; ///< Pointer to the pixel to the right of this pixel.

public:
    RGBColor* Color; ///< Pointer to the RGB color of the pixel.

    /**
     * @brief Default constructor.
     *
     * Constructs a Pixel object with default settings.
     */
    Pixel();

    /**
     * @brief Constructs a Pixel object with a specified position.
     *
     * @param position Pointer to the pixel's position in 2D space.
     */
    Pixel(const Vector2D* position);

    /**
     * @brief Retrieves the pixel's position.
     *
     * @return A copy of the pixel's position as a Vector2D object.
     */
    const Vector2D GetPosition();

    /**
     * @brief Sets the pixel above this pixel.
     *
     * @param pixel Pointer to the pixel above this pixel.
     */
    void SetUpPixel(Pixel* pixel);

    /**
     * @brief Sets the pixel below this pixel.
     *
     * @param pixel Pointer to the pixel below this pixel.
     */
    void SetDownPixel(Pixel* pixel);

    /**
     * @brief Sets the pixel to the left of this pixel.
     *
     * @param pixel Pointer to the pixel to the left of this pixel.
     */
    void SetLeftPixel(Pixel* pixel);

    /**
     * @brief Sets the pixel to the right of this pixel.
     *
     * @param pixel Pointer to the pixel to the right of this pixel.
     */
    void SetRightPixel(Pixel* pixel);

    /**
     * @brief Checks if a pixel exists above this pixel.
     *
     * @return True if a pixel exists above, otherwise false.
     */
    bool HasUpPixel();

    /**
     * @brief Checks if a pixel exists below this pixel.
     *
     * @return True if a pixel exists below, otherwise false.
     */
    bool HasDownPixel();

    /**
     * @brief Checks if a pixel exists to the left of this pixel.
     *
     * @return True if a pixel exists to the left, otherwise false.
     */
    bool HasLeftPixel();

    /**
     * @brief Checks if a pixel exists to the right of this pixel.
     *
     * @return True if a pixel exists to the right, otherwise false.
     */
    bool HasRightPixel();

    /**
     * @brief Retrieves the pixel above this pixel.
     *
     * @return Pointer to the pixel above, or nullptr if none exists.
     */
    Pixel* GetUpPixel();

    /**
     * @brief Retrieves the pixel below this pixel.
     *
     * @return Pointer to the pixel below, or nullptr if none exists.
     */
    Pixel* GetDownPixel();

    /**
     * @brief Retrieves the pixel to the left of this pixel.
     *
     * @return Pointer to the pixel to the left, or nullptr if none exists.
     */
    Pixel* GetLeftPixel();

    /**
     * @brief Retrieves the pixel to the right of this pixel.
     *
     * @return Pointer to the pixel to the right, or nullptr if none exists.
     */
    Pixel* GetRightPixel();
};
