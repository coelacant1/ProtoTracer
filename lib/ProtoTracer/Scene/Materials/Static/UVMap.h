/**
 * @file UVMap.h
 * @brief A material class for mapping UV texture coordinates to RGB colors.
 *
 * The `UVMap` class extends the `Image` class and provides functionality
 * for mapping UV coordinates to pixel colors in an image, enabling texture
 * mapping in 3D rendering.
 *
 * @date 22/12/2024
 * @author Coela Can't
 */

#pragma once

#include "Image.h"
#include "../../../Utils/Math/Mathematics.h"

/**
 * @class UVMap
 * @brief A material for mapping UV texture coordinates to image colors.
 *
 * The `UVMap` class uses UV coordinates to sample colors from a specified
 * image, providing a way to texture surfaces in 3D space.
 */
class UVMap : public Image {
public:
    /**
     * @brief Constructs a UVMap with the given image data and color palette.
     *
     * @param data Pointer to the image data (pixel indices).
     * @param rgbColors Pointer to the RGB color palette.
     * @param xPixels Width of the image in pixels.
     * @param yPixels Height of the image in pixels.
     * @param colors Number of colors in the palette.
     */
    UVMap(const uint8_t* data, const uint8_t* rgbColors, uint16_t xPixels, uint16_t yPixels, uint8_t colors);

    /**
     * @brief Retrieves the RGB color at a given 3D position using UV mapping.
     *
     * @param position 3D position in the scene.
     * @param normal Normal vector at the position (not used in UV mapping).
     * @param uvw UV texture coordinates at the position.
     * @return The RGB color sampled from the image at the given UV coordinates.
     */
    RGBColor GetRGB(const Vector3D& position, const Vector3D& normal, const Vector3D& uvw) override;
};
