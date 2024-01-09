#pragma once

#include "..\..\Utils\RGBColor.h"
#include "..\..\Physics\Utils\BoundingBox2D.h"

class IPixelGroup {
public:
    enum Direction{
        ZEROTOMAX,
        MAXTOZERO
    };

    virtual Vector2D GetCenterCoordinate() = 0;
    virtual Vector2D GetSize() = 0;
    virtual Vector2D GetCoordinate(uint16_t count) = 0;
    virtual int GetPixelIndex(Vector2D location) = 0;
    virtual RGBColor* GetColor(uint16_t count) = 0;
    virtual RGBColor* GetColors() = 0;
    virtual RGBColor* GetColorBuffer() = 0;
    virtual uint16_t GetPixelCount() = 0;
    virtual bool Overlaps(BoundingBox2D* box) = 0;
    virtual bool ContainsVector2D(Vector2D v) = 0;
    virtual bool GetUpIndex(uint16_t count, uint16_t* upIndex) = 0;
    virtual bool GetDownIndex(uint16_t count, uint16_t* downIndex) = 0;
    virtual bool GetLeftIndex(uint16_t count, uint16_t* leftIndex) = 0;
    virtual bool GetRightIndex(uint16_t count, uint16_t* rightIndex) = 0;
    virtual bool GetAlternateXIndex(uint16_t count, uint16_t* index) = 0;
    virtual bool GetAlternateYIndex(uint16_t count, uint16_t* index) = 0;
    virtual bool GetOffsetXIndex(uint16_t count, uint16_t* index, int x1) = 0;
    virtual bool GetOffsetYIndex(uint16_t count, uint16_t* index, int y1) = 0;
    virtual bool GetOffsetXYIndex(uint16_t count, uint16_t* index, int x1, int y1) = 0;
    virtual bool GetRadialIndex(uint16_t count, uint16_t* index, int pixels, float angle) = 0;
    virtual void GridSort() = 0;
};
