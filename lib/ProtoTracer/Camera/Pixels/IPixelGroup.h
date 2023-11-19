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
    virtual Vector2D GetCoordinate(unsigned int count) = 0;
    virtual int GetPixelIndex(Vector2D location) = 0;
    virtual RGBColor* GetColor(unsigned int count) = 0;
    virtual RGBColor* GetColors() = 0;
    virtual RGBColor* GetColorBuffer() = 0;
    virtual unsigned int GetPixelCount() = 0;
    virtual bool Overlaps(BoundingBox2D* box) = 0;
    virtual bool ContainsVector2D(Vector2D v) = 0;
    virtual bool GetUpIndex(unsigned int count, unsigned int* upIndex) = 0;
    virtual bool GetDownIndex(unsigned int count, unsigned int* downIndex) = 0;
    virtual bool GetLeftIndex(unsigned int count, unsigned int* leftIndex) = 0;
    virtual bool GetRightIndex(unsigned int count, unsigned int* rightIndex) = 0;
    virtual bool GetAlternateXIndex(unsigned int count, unsigned int* index) = 0;
    virtual bool GetAlternateYIndex(unsigned int count, unsigned int* index) = 0;
    virtual bool GetOffsetXIndex(unsigned int count, unsigned int* index, int x1) = 0;
    virtual bool GetOffsetYIndex(unsigned int count, unsigned int* index, int y1) = 0;
    virtual bool GetOffsetXYIndex(unsigned int count, unsigned int* index, int x1, int y1) = 0;
    virtual bool GetRadialIndex(unsigned int count, unsigned int* index, int pixels, float angle) = 0;
    virtual void GridSort() = 0;
};
