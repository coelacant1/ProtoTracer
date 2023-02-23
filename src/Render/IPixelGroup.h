#pragma once

#include "..\Materials\RGBColor.h"
#include "BoundingBox2D.h"

class IPixelGroup {
public:
    enum Direction{
        ZEROTOMAX,
        MAXTOZERO
    };

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
    virtual bool GetRadialIndex(unsigned int count, unsigned int* index, int pixels, float angle) = 0;
    virtual void GridSort() = 0;
};
