#pragma once

#include "IPixelGroup.h"

template<size_t pixelCount>
class PixelGroup : public IPixelGroup{
private:
    Direction direction;
    BoundingBox2D bounds;
	Vector2D* pixelPositions;
  	RGBColor pixelColors[pixelCount];
  	RGBColor pixelBuffer[pixelCount];
    unsigned int up[pixelCount];
    unsigned int down[pixelCount];
    unsigned int left[pixelCount];
    unsigned int right[pixelCount];
    bool upExists[pixelCount];
    bool downExists[pixelCount];
    bool leftExists[pixelCount];
    bool rightExists[pixelCount];

    bool isRectangular = false;
    uint16_t rowCount;
    uint16_t colCount;
    Vector2D size;
    Vector2D position;

public:
    PixelGroup(Vector2D size, Vector2D position, uint16_t rowCount);
    PixelGroup(Vector2D* pixelLocations, Direction direction = ZEROTOMAX);
    ~PixelGroup();

    Vector2D GetCenterCoordinate() override;
    Vector2D GetSize() override;
    Vector2D GetCoordinate(unsigned int count) override;

    int GetPixelIndex(Vector2D location) override;

    RGBColor* GetColor(unsigned int count) override;
    RGBColor* GetColors() override;
    RGBColor* GetColorBuffer() override;

    unsigned int GetPixelCount() override;

    bool Overlaps(BoundingBox2D* box) override;
    bool ContainsVector2D(Vector2D v) override;
    bool GetUpIndex(unsigned int count, unsigned int* upIndex) override;
    bool GetDownIndex(unsigned int count, unsigned int* downIndex) override;
    bool GetLeftIndex(unsigned int count, unsigned int* leftIndex) override;
    bool GetRightIndex(unsigned int count, unsigned int* rightIndex) override;
    bool GetAlternateXIndex(unsigned int count, unsigned int* index) override;
    bool GetAlternateYIndex(unsigned int count, unsigned int* index) override;
    bool GetOffsetXIndex(unsigned int count, unsigned int* index, int x1) override;
    bool GetOffsetYIndex(unsigned int count, unsigned int* index, int y1) override;
    bool GetOffsetXYIndex(unsigned int count, unsigned int* index, int x1, int y1) override;
    bool GetRadialIndex(unsigned int count, unsigned int* index, int pixels, float angle) override;

    void GridSort() override;
    void ListPixelNeighbors();
};

#include "PixelGroup.tpp"
