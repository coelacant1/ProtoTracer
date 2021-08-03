#pragma once

#include "BoundingBox2D.h"
#include "Pixel.h"

class PixelGroup{
public:
    enum Direction{
        ZEROTOMAX,
        MAXTOZERO
    };

private:
    const unsigned int pixelCount;
    BoundingBox2D bounds;
    Direction direction;
    Pixel** pixels;

public:
    PixelGroup(Vector2D* pixelLocations, unsigned int pixelCount, Direction direction = ZEROTOMAX) : pixelCount(pixelCount){
        this->direction = direction;

        pixels = new Pixel*[pixelCount];

        if(direction == ZEROTOMAX){
            for(unsigned int i = 0; i < pixelCount; i++){
                pixels[i] = new Pixel(&pixelLocations[i]);
                bounds.UpdateBounds(pixelLocations[i]);
            }
        }
        else{
            for(unsigned int i = 0; i < pixelCount; i++){
                pixels[i] = new Pixel(&pixelLocations[pixelCount - i - 1]);
                bounds.UpdateBounds(pixelLocations[i]);
            }
        }
    }

    ~PixelGroup(){
        for (unsigned int i = 0; i < pixelCount; i++){
            delete pixels[i];
        }

        delete pixels;
    }

    Pixel* GetPixel(unsigned int count){
        count = Mathematics::Constrain(count, 0, pixelCount);

        return pixels[count];
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
