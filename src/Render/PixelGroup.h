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
    unsigned int** up;
    unsigned int** down;
    unsigned int** left;
    unsigned int** right;
    bool** upExists;
    bool** downExists;
    bool** leftExists;
    bool** rightExists;

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
        up = new unsigned int*[pixelCount];
        down = new unsigned int*[pixelCount];
        left = new unsigned int*[pixelCount];
        right = new unsigned int*[pixelCount];
        upExists = new bool*[pixelCount];
        downExists = new bool*[pixelCount];
        leftExists = new bool*[pixelCount];
        rightExists = new bool*[pixelCount];

        if(direction == ZEROTOMAX){
            for(unsigned int i = 0; i < pixelCount; i++){
                pixelPositions[i] = &pixelLocations[i];
                pixelColors[i] = new RGBColor();
                up[i] = new unsigned int();
                down[i] = new unsigned int();
                left[i] = new unsigned int();
                right[i] = new unsigned int();
                upExists[i] = new bool();
                downExists[i] = new bool();
                leftExists[i] = new bool();
                rightExists[i] = new bool();

                
                *up[i] = 0;
                *down[i] = 0;
                *left[i] = 0;
                *right[i] = 0;
                *upExists[i] = false;
                *downExists[i] = false;
                *leftExists[i] = false;
                *rightExists[i] = false;

                bounds.UpdateBounds(pixelLocations[i]);
            }
        }
        else{
            for(unsigned int i = 0; i < pixelCount; i++){
                pixelPositions[i] = &pixelLocations[pixelCount - i - 1];
                pixelColors[i] = new RGBColor();
                up[i] = new unsigned int();
                down[i] = new unsigned int();
                left[i] = new unsigned int();
                right[i] = new unsigned int();
                upExists[i] = new bool();
                downExists[i] = new bool();
                leftExists[i] = new bool();
                rightExists[i] = new bool();

                *up[i] = 0;
                *down[i] = 0;
                *left[i] = 0;
                *right[i] = 0;
                *upExists[i] = false;
                *downExists[i] = false;
                *leftExists[i] = false;
                *rightExists[i] = false;

                bounds.UpdateBounds(pixelLocations[i]);
            }
        }

        //delay(2000);
        GridSort();
        //ListPixelNeighbors();
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

    int GetPixelIndex(Vector2D location){
        float row = Mathematics::Map(location.X, position.X - size.X / 2.0f, position.X + size.X / 2.0f, 0.0f, float(rowCount));
        float col = Mathematics::Map(location.Y, position.Y - size.Y / 2.0f, position.Y + size.Y / 2.0f, 0.0f, float(colCount));

        unsigned int count = row + col * rowCount;

        if (count < pixelCount && count > 0 && row > 0 && row < rowCount && col > 0 && col < colCount){
            return count;
        }
        else{
            return -1;
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

    
    bool GetUpIndex(unsigned int count, unsigned int* upIndex){
        if (isRectangular){
            unsigned int index = count + rowCount;

            if (index < pixelCount){
                *upIndex = index;
                return true;
            }
            else{ return false; }
        }
        else{
            *upIndex = *up[count];

            return upExists[*up[count]];
        }
    }

    bool GetDownIndex(unsigned int count, unsigned int* downIndex){
        if (isRectangular){
            unsigned int index = count - rowCount;

            if (index > 0){
                *downIndex = index;
                return true;
            }
            else{ return false; }
        }
        else{
            *downIndex = *down[count];

            return downExists[*down[count]];
        }
    }

    bool GetLeftIndex(unsigned int count, unsigned int* leftIndex){
        if (isRectangular){
            unsigned int index = count - 1;

            if (!count % rowCount == 0 && count > 0){
                *leftIndex = index;
                return true;
            }
            else{ return false; }
        }
        else{
            *leftIndex = *left[count];

            return leftExists[*left[count]];
        }
    }

    bool GetRightIndex(unsigned int count, unsigned int* rightIndex){
        if (isRectangular){
            unsigned int index = count + 1;

            if (!count % rowCount + 1 == 0 && count < pixelCount){
                *rightIndex = index;
                return true;
            }
            else{ return false; }
        }
        else{
            *rightIndex = *right[count];

            return rightExists[*right[count]];
        }
    }

    bool GetUpColor(unsigned int count, RGBColor* upColor){
        if (isRectangular){
            unsigned int index = count + rowCount;

            if (index < pixelCount){
                upColor = pixelColors[index];
                return true;
            }
            else{ return false; }
        }
        else{
            unsigned int index = *up[count];
            
            upColor = pixelColors[index];

            return upExists[index];
        }
    }

    bool GetDownColor(unsigned int count, RGBColor* downColor){
        if (isRectangular){
            int index = count - rowCount;

            if (index > 0){
                downColor = pixelColors[index];
                return true;
            }
            else{ return false; }
        }
        else{
            unsigned int index = *down[count];
            
            downColor = pixelColors[index];

            return downExists[index];
        }
    }

    bool GetLeftColor(unsigned int count, RGBColor* leftColor){
        if (isRectangular){
            int index = count - 1;

            if (!count % rowCount == 0 && count > 0){
                leftColor = pixelColors[index];
                return true;
            }
            else{ return false; }
        }
        else{
            unsigned int index = *left[count];
            
            leftColor = pixelColors[index];

            return leftExists[index];
        }
    }

    bool GetRightColor(unsigned int count, RGBColor* rightColor){
        if (isRectangular){
            int index = count + 1;

            if (!count % rowCount + 1 == 0 && count < pixelCount){
                rightColor = pixelColors[index];
                return true;
            }
            else{ return false; }
        }
        else{
            unsigned int index = *right[count];

            rightColor = pixelColors[index];

            return rightExists[index];
        }
    }

    void GridSort() {
        if(!isRectangular){
            // Loop through all pixels
            for (unsigned int i = 0; i < pixelCount; i++) {
                Vector2D& currentPos = *pixelPositions[i];

                // Initialize the minimum distances and indices to the first pixel
                float minUp = Mathematics::FLTMAX, minDown = Mathematics::FLTMAX, minLeft = Mathematics::FLTMAX, minRight = Mathematics::FLTMAX;
                int minUpIndex = -1, minDownIndex = -1, minLeftIndex = -1, minRightIndex = -1;

                // Loop through all other pixels
                for (unsigned int j = 0; j < pixelCount; j++) {
                    if (i == j) { continue; } // Skip the current pixel

                    Vector2D& neighborPos = *pixelPositions[j];

                    // Calculate the distances between the current pixel and the other pixel
                    float dist = currentPos.CalculateEuclideanDistance(neighborPos);

                    // Check if the other pixel is above or below the current pixel
                    if (Mathematics::IsClose(currentPos.X, neighborPos.X, 0.5f)) {
                        if (currentPos.Y < neighborPos.Y && dist < minUp) {
                            minUp = dist;
                            minUpIndex = j;
                        }
                        else if (currentPos.Y > neighborPos.Y && dist < minDown) {
                            minDown = dist;
                            minDownIndex = j;
                        }
                    }

                    // Check if the other pixel is to the left or right of the current pixel
                    if (Mathematics::IsClose(currentPos.Y, neighborPos.Y, 0.5f)) {
                        if (currentPos.X > neighborPos.X && dist < minLeft) {
                            minLeft = dist;
                            minLeftIndex = j;
                        }
                        else if (currentPos.X < neighborPos.X && dist < minRight) {
                            minRight = dist;
                            minRightIndex = j;
                        }
                    }
                }

                // Set the indices of the neighboring pixels
                if (minUpIndex != -1) {
                    *up[i] = minUpIndex;
                    *upExists[i] = true;
                }
                if (minDownIndex != -1) {
                    *down[i] = minDownIndex;
                    *downExists[i] = true;
                }
                if (minLeftIndex != -1) {
                    *left[i] = minLeftIndex;
                    *leftExists[i] = true;
                }
                if (minRightIndex != -1) {
                    *right[i] = minRightIndex;
                    *rightExists[i] = true;
                }
            }
        }
        //else do nothing
    }

    void ListPixelNeighbors(){
        for(unsigned int i = 0; i < pixelCount; i++){
            Serial.print(i); Serial.print('\t');
            Serial.print(*up[i]); Serial.print('\t');
            Serial.print(*down[i]); Serial.print('\t');
            Serial.print(*left[i]); Serial.print('\t');
            Serial.print(*right[i]); Serial.print('\t');
            Serial.print(*upExists[i]); Serial.print('\t');
            Serial.print(*downExists[i]); Serial.print('\t');
            Serial.print(*leftExists[i]); Serial.print('\t');
            Serial.print(*rightExists[i]); Serial.print('\n');
        }
    }

    void ShiftRedLeft(){
        for (unsigned int i = 0; i < pixelCount; i++){
            unsigned int l1 = 0, l2 = 0, l3 = 0, l4 = 0, l5 = 0;
            
            bool l1E = GetLeftIndex(i, &l1);
            bool l2E = GetLeftIndex(l1, &l2);
            bool l3E = GetLeftIndex(l2, &l3);
            bool l4E = GetLeftIndex(l3, &l4);
            bool l5E = GetLeftIndex(l4, &l5);

            if(l5E){
                pixelColors[l5]->R = (pixelColors[i]->R + pixelColors[l2]->R + pixelColors[l3]->R + pixelColors[4]->R) / 4;
                pixelColors[l5]->B = (pixelColors[i]->B + pixelColors[l2]->B + pixelColors[l3]->B + pixelColors[4]->B) / 4;
                pixelColors[l5]->G = (pixelColors[i]->G + pixelColors[l2]->G + pixelColors[l3]->G + pixelColors[4]->G) / 4;
            }
            else{
                pixelColors[l5]->R = 0;
                pixelColors[l5]->B = 0;
                pixelColors[l5]->G = 0;
            }
        }
    }
};
