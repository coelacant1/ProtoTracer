#pragma once

#include "..\Materials\RGBColor.h"
#include "BoundingBox2D.h"

class PixelGroup{
public:
    enum Direction{
        ZEROTOMAX,
        MAXTOZERO
    };

private:
    const unsigned int pixelCount;
    BoundingBox2D bounds;
	Vector2D** pixelPositions;
  	RGBColor** pixelColors;

    bool isRectangular = false;
    uint16_t rowCount;
    uint16_t colCount;
    Vector2D size;
    Vector2D position;

public:
    PixelGroup(Vector2D size, Vector2D position, uint16_t rowCount, unsigned int pixelCount) : pixelCount(pixelCount){
        this->size = size;
        this->position = position;
        this->rowCount = rowCount;
        this->colCount = pixelCount / rowCount;

        isRectangular = true;

        bounds.UpdateBounds(position - (size / 2.0f));
        bounds.UpdateBounds(position + (size / 2.0f));

        pixelColors = new RGBColor*[pixelCount];

        for(unsigned int i = 0; i < pixelCount; i++){
            pixelColors[i] = new RGBColor();
        }
    }

    PixelGroup(Vector2D* pixelLocations, unsigned int pixelCount, Direction direction = ZEROTOMAX) : pixelCount(pixelCount){
        pixelPositions = new Vector2D*[pixelCount];
        pixelColors = new RGBColor*[pixelCount];

        if(direction == ZEROTOMAX){
            for(unsigned int i = 0; i < pixelCount; i++){
                pixelPositions[i] = &pixelLocations[i];
                pixelColors[i] = new RGBColor();
                bounds.UpdateBounds(pixelLocations[i]);
            }
        }
        else{
            for(unsigned int i = 0; i < pixelCount; i++){
                pixelPositions[i] = &pixelLocations[pixelCount - i - 1];
                pixelColors[i] = new RGBColor();
                bounds.UpdateBounds(pixelLocations[i]);
            }
        }
    }

    ~PixelGroup(){
        for (unsigned int i = 0; i < pixelCount; i++){
            delete pixelPositions[i];
            delete pixelColors[i];
        }

        delete pixelPositions;
        delete pixelColors;
    }

    Vector2D GetCoordinate(unsigned int count){
        count = Mathematics::Constrain<int>(count, 0, pixelCount);

        if (isRectangular){
            float row = count % rowCount;
            float col = (count - row) / rowCount;

            Vector2D location;

            location.X = Mathematics::Map(row, 0.0f, float(rowCount), position.X - size.X / 2.0f, position.X + size.X / 2.0f);
            location.Y = Mathematics::Map(col, 0.0f, float(colCount), position.Y - size.Y / 2.0f, position.Y + size.Y / 2.0f);

            return location;
        }
        else{
            return *pixelPositions[count];
        }
    }

    RGBColor* GetColor(unsigned int count){
        return pixelColors[count];
    }

    unsigned int GetPixelCount(){
        return pixelCount;
    }

    bool Overlaps(BoundingBox2D* box){
        return bounds.Overlaps(box);
    }

    bool ContainsVector2D(Vector2D v){
        return v.CheckBounds(bounds.GetMinimum(), bounds.GetMaximum());
    }
};
