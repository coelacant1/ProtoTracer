/**
 * @file PixelGroup.h
 * @brief Declares the PixelGroup template class for managing a collection of pixels.
 *
 * This file defines the PixelGroup class, which implements the IPixelGroup interface
 * to manage a fixed number of pixels with spatial and color properties.
 *
 * @date 22/12/2024
 * @author Coela Can't
 */

#pragma once

#include "IPixelGroup.h" // Include for the base pixel group interface.

/**
 * @class PixelGroup
 * @brief Manages a collection of pixels with positions, colors, and spatial relationships.
 *
 * The PixelGroup class provides methods for retrieving and manipulating pixel data,
 * including spatial relationships and color properties. Supports both rectangular
 * and arbitrary pixel arrangements.
 *
 * @tparam pixelCount The total number of pixels in the group.
 */
template<size_t pixelCount>
class PixelGroup : public IPixelGroup {
private:
    const Vector2D* pixelPositions; ///< Array of pixel positions.
    Direction direction; ///< Direction of pixel traversal.
    BoundingBox2D bounds; ///< Bounding box for the pixel group.
    RGBColor pixelColors[pixelCount]; ///< Array of pixel colors.
    RGBColor pixelBuffer[pixelCount]; ///< Array of color buffers for temporary use.
    uint16_t up[pixelCount]; ///< Indices of pixels above each pixel.
    uint16_t down[pixelCount]; ///< Indices of pixels below each pixel.
    uint16_t left[pixelCount]; ///< Indices of pixels to the left of each pixel.
    uint16_t right[pixelCount]; ///< Indices of pixels to the right of each pixel.

    bool isRectangular = false; ///< Indicates if the group forms a rectangular grid.
    uint16_t rowCount; ///< Number of rows in the grid.
    uint16_t colCount; ///< Number of columns in the grid.
    Vector2D size; ///< Size of the grid.
    Vector2D position; ///< Position of the grid.
    Vector2D tempLocation; ///< Temporary location for calculations.

public:
    /**
     * @brief Constructs a rectangular PixelGroup.
     *
     * @param size Size of the rectangular grid.
     * @param position Position of the rectangular grid.
     * @param rowCount Number of rows in the grid.
     */
    PixelGroup(Vector2D size, Vector2D position, uint16_t rowCount);

    /**
     * @brief Constructs a PixelGroup from arbitrary pixel locations.
     *
     * @param pixelLocations Array of pixel locations.
     * @param direction Direction of pixel traversal (default: ZEROTOMAX).
     */
    PixelGroup(const Vector2D* pixelLocations, Direction direction = ZEROTOMAX);

    /**
     * @brief Destroys the PixelGroup object.
     */
    ~PixelGroup();

    Vector2D GetCenterCoordinate() override;
    Vector2D GetSize() override;
    Vector2D GetCoordinate(uint16_t count) override;
    int GetPixelIndex(Vector2D location) override;
    RGBColor* GetColor(uint16_t count) override;
    RGBColor* GetColors() override;
    RGBColor* GetColorBuffer() override;
    uint16_t GetPixelCount() override;
    bool Overlaps(BoundingBox2D* box) override;
    bool ContainsVector2D(Vector2D v) override;
    bool GetUpIndex(uint16_t count, uint16_t* upIndex) override;
    bool GetDownIndex(uint16_t count, uint16_t* downIndex) override;
    bool GetLeftIndex(uint16_t count, uint16_t* leftIndex) override;
    bool GetRightIndex(uint16_t count, uint16_t* rightIndex) override;
    bool GetAlternateXIndex(uint16_t count, uint16_t* index) override;
    bool GetAlternateYIndex(uint16_t count, uint16_t* index) override;
    bool GetOffsetXIndex(uint16_t count, uint16_t* index, int x1) override;
    bool GetOffsetYIndex(uint16_t count, uint16_t* index, int y1) override;
    bool GetOffsetXYIndex(uint16_t count, uint16_t* index, int x1, int y1) override;
    bool GetRadialIndex(uint16_t count, uint16_t* index, int pixels, float angle) override;
    void GridSort() override;
};

#include "PixelGroup.tpp" // Include the template implementation.
