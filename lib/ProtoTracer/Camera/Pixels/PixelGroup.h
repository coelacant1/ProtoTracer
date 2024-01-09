#pragma once

#include "IPixelGroup.h"

template<size_t pixelCount>
class PixelGroup : public IPixelGroup{
private:
	const Vector2D* pixelPositions;
    Direction direction;
    BoundingBox2D bounds;
  	RGBColor pixelColors[pixelCount];
  	RGBColor pixelBuffer[pixelCount];
    uint16_t up[pixelCount];
    uint16_t down[pixelCount];
    uint16_t left[pixelCount];
    uint16_t right[pixelCount];

    bool isRectangular = false;
    uint16_t rowCount;
    uint16_t colCount;
    Vector2D size;
    Vector2D position;
    Vector2D tempLocation;

public:
    PixelGroup(Vector2D size, Vector2D position, uint16_t rowCount);
    PixelGroup(const Vector2D* pixelLocations, Direction direction = ZEROTOMAX);
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

#include "PixelGroup.tpp"
