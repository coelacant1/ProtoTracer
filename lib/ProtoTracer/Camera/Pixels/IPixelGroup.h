/**
 * @file IPixelGroup.h
 * @brief Declares the IPixelGroup interface for managing collections of pixels.
 *
 * This file defines the IPixelGroup interface, which specifies the contract
 * for working with groups of pixels, including spatial relationships and color management.
 *
 * @date 22/12/2024
 * @author Coela Can't
 */

#pragma once

#include "../../Utils/RGBColor.h" // Include for RGB color representation.
#include "../../Physics/Utils/BoundingBox2D.h" // Include for 2D bounding box representation.

/**
 * @class IPixelGroup
 * @brief Interface for managing and interacting with a collection of pixels.
 *
 * The IPixelGroup interface provides methods for retrieving pixel properties,
 * spatial relationships, and color data. Implementations of this interface can
 * manage rectangular grids or arbitrary pixel arrangements.
 */
class IPixelGroup {
public:
    /**
     * @enum Direction
     * @brief Specifies traversal directions for pixels.
     */
    enum Direction {
        ZEROTOMAX, ///< Traverse from minimum to maximum indices.
        MAXTOZERO  ///< Traverse from maximum to minimum indices.
    };

    /**
     * @brief Retrieves the center coordinate of the pixel group.
     *
     * @return The center coordinate as a Vector2D.
     */
    virtual Vector2D GetCenterCoordinate() = 0;

    /**
     * @brief Retrieves the size of the pixel group.
     *
     * @return The size as a Vector2D.
     */
    virtual Vector2D GetSize() = 0;

    /**
     * @brief Retrieves the coordinate of a specific pixel.
     *
     * @param count The index of the pixel.
     * @return The coordinate of the pixel as a Vector2D.
     */
    virtual Vector2D GetCoordinate(uint16_t count) = 0;

    /**
     * @brief Retrieves the index of a pixel at a specific location.
     *
     * @param location The location to search for a pixel.
     * @return The index of the pixel, or -1 if not found.
     */
    virtual int GetPixelIndex(Vector2D location) = 0;

    /**
     * @brief Retrieves the color of a specific pixel.
     *
     * @param count The index of the pixel.
     * @return Pointer to the RGB color of the pixel.
     */
    virtual RGBColor* GetColor(uint16_t count) = 0;

    /**
     * @brief Retrieves the array of colors for the pixel group.
     *
     * @return Pointer to the array of RGB colors.
     */
    virtual RGBColor* GetColors() = 0;

    /**
     * @brief Retrieves the color buffer for the pixel group.
     *
     * @return Pointer to the color buffer array.
     */
    virtual RGBColor* GetColorBuffer() = 0;

    /**
     * @brief Retrieves the total number of pixels in the group.
     *
     * @return The total pixel count.
     */
    virtual uint16_t GetPixelCount() = 0;

    /**
     * @brief Checks if the pixel group overlaps with a bounding box.
     *
     * @param box Pointer to the bounding box.
     * @return True if the group overlaps with the box, otherwise false.
     */
    virtual bool Overlaps(BoundingBox2D* box) = 0;

    /**
     * @brief Checks if the pixel group contains a specific vector.
     *
     * @param v The vector to check.
     * @return True if the group contains the vector, otherwise false.
     */
    virtual bool ContainsVector2D(Vector2D v) = 0;

    /**
     * @brief Retrieves the index of the pixel above a given pixel.
     *
     * @param count The index of the current pixel.
     * @param upIndex Pointer to store the index of the pixel above.
     * @return True if a pixel above exists, otherwise false.
     */
    virtual bool GetUpIndex(uint16_t count, uint16_t* upIndex) = 0;

    /**
     * @brief Retrieves the index of the pixel below a given pixel.
     *
     * @param count The index of the current pixel.
     * @param downIndex Pointer to store the index of the pixel below.
     * @return True if a pixel below exists, otherwise false.
     */
    virtual bool GetDownIndex(uint16_t count, uint16_t* downIndex) = 0;

    /**
     * @brief Retrieves the index of the pixel to the left of a given pixel.
     *
     * @param count The index of the current pixel.
     * @param leftIndex Pointer to store the index of the pixel to the left.
     * @return True if a pixel to the left exists, otherwise false.
     */
    virtual bool GetLeftIndex(uint16_t count, uint16_t* leftIndex) = 0;

    /**
     * @brief Retrieves the index of the pixel to the right of a given pixel.
     *
     * @param count The index of the current pixel.
     * @param rightIndex Pointer to store the index of the pixel to the right.
     * @return True if a pixel to the right exists, otherwise false.
     */
    virtual bool GetRightIndex(uint16_t count, uint16_t* rightIndex) = 0;

    /**
     * @brief Retrieves an alternate X-axis index for a given pixel.
     *
     * @param count The index of the current pixel.
     * @param index Pointer to store the alternate X index.
     * @return True if an alternate index exists, otherwise false.
     */
    virtual bool GetAlternateXIndex(uint16_t count, uint16_t* index) = 0;

    /**
     * @brief Retrieves an alternate Y-axis index for a given pixel.
     *
     * @param count The index of the current pixel.
     * @param index Pointer to store the alternate Y index.
     * @return True if an alternate index exists, otherwise false.
     */
    virtual bool GetAlternateYIndex(uint16_t count, uint16_t* index) = 0;

    /**
     * @brief Retrieves an offset X-axis index for a given pixel.
     *
     * @param count The index of the current pixel.
     * @param index Pointer to store the offset X index.
     * @param x1 The X-axis offset value.
     * @return True if an offset index exists, otherwise false.
     */
    virtual bool GetOffsetXIndex(uint16_t count, uint16_t* index, int x1) = 0;

    /**
     * @brief Retrieves an offset Y-axis index for a given pixel.
     *
     * @param count The index of the current pixel.
     * @param index Pointer to store the offset Y index.
     * @param y1 The Y-axis offset value.
     * @return True if an offset index exists, otherwise false.
     */
    virtual bool GetOffsetYIndex(uint16_t count, uint16_t* index, int y1) = 0;

    /**
     * @brief Retrieves an offset XY-axis index for a given pixel.
     *
     * @param count The index of the current pixel.
     * @param index Pointer to store the offset XY index.
     * @param x1 The X-axis offset value.
     * @param y1 The Y-axis offset value.
     * @return True if an offset index exists, otherwise false.
     */
    virtual bool GetOffsetXYIndex(uint16_t count, uint16_t* index, int x1, int y1) = 0;

    /**
     * @brief Retrieves a radial index for a given pixel based on distance and angle.
     *
     * @param count The index of the current pixel.
     * @param index Pointer to store the radial index.
     * @param pixels The radial distance in pixels.
     * @param angle The angle in degrees.
     * @return True if a radial index exists, otherwise false.
     */
    virtual bool GetRadialIndex(uint16_t count, uint16_t* index, int pixels, float angle) = 0;

    /**
     * @brief Sorts the pixels in a grid structure.
     */
    virtual void GridSort() = 0;
};
