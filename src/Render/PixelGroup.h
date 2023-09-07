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
    PixelGroup(Vector2D size, Vector2D position, uint16_t rowCount){
        this->size = size;
        this->position = position;
        this->rowCount = rowCount;
        this->colCount = pixelCount / rowCount;

        isRectangular = true;

        bounds.UpdateBounds(position - (size / 2.0f));
        bounds.UpdateBounds(position + (size / 2.0f));

        for(unsigned int i = 0; i < pixelCount; i++){
            pixelColors[i] = RGBColor();
            pixelBuffer[i] = RGBColor();
        }
    }

    PixelGroup(Vector2D* pixelLocations, Direction direction = ZEROTOMAX){
        this->direction = direction;
        pixelPositions = pixelLocations;

        for(unsigned int i = 0; i < pixelCount; i++){
            bounds.UpdateBounds(pixelLocations[i]);
        }

        GridSort();
        //ListPixelNeighbors();
    }

    ~PixelGroup(){}

    virtual Vector2D GetCenterCoordinate(){
        return (bounds.GetMaximum() + bounds.GetMinimum()) / 2.0f;
    }

    virtual Vector2D GetSize(){
        return bounds.GetMaximum() - bounds.GetMinimum();
    }

    virtual Vector2D GetCoordinate(unsigned int count) override {
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
            if(direction == ZEROTOMAX){
                return pixelPositions[count];
            }
            else{
                return pixelPositions[pixelCount - count - 1];
            }
        }
    }

    virtual int GetPixelIndex(Vector2D location) override {
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

    virtual RGBColor* GetColor(unsigned int count) override {
        return &pixelColors[count];
    }

    virtual RGBColor* GetColors() override {
        return &pixelColors[0];
    }

    virtual RGBColor* GetColorBuffer() override {
        return &pixelBuffer[0];
    }

    virtual unsigned int GetPixelCount() override {
        return pixelCount;
    }

    virtual bool Overlaps(BoundingBox2D* box) override {
        return bounds.Overlaps(box);
    }

    virtual bool ContainsVector2D(Vector2D v) override {
        return v.CheckBounds(bounds.GetMinimum(), bounds.GetMaximum());
    }

    virtual bool GetUpIndex(unsigned int count, unsigned int* upIndex) override {
        if (isRectangular){
            unsigned int index = count + rowCount;

            if (index < pixelCount){
                *upIndex = index;
                return true;
            }
            else{ return false; }
        }
        else{
            *upIndex = up[count];

            return upExists[count];
        }
    }

    virtual bool GetDownIndex(unsigned int count, unsigned int* downIndex) override {
        if (isRectangular){
            unsigned int index = count - rowCount;

            if (index > 0){
                *downIndex = index;
                return true;
            }
            else{ return false; }
        }
        else{
            *downIndex = down[count];

            return downExists[count];
        }
    }

    virtual bool GetLeftIndex(unsigned int count, unsigned int* leftIndex) override {
        if (isRectangular){
            unsigned int index = count - 1;

            if (!count % rowCount == 0 && count > 0){
                *leftIndex = index;
                return true;
            }
            else{ return false; }
        }
        else{
            *leftIndex = left[count];

            return leftExists[count];
        }
    }

    virtual bool GetRightIndex(unsigned int count, unsigned int* rightIndex) override {
        if (isRectangular){
            unsigned int index = count + 1;

            if (!count % rowCount + 1 == 0 && count < pixelCount){
                *rightIndex = index;
                return true;
            }
            else{ return false; }
        }
        else{
            *rightIndex = right[count];

            return rightExists[count];
        }
    }

    virtual bool GetAlternateXIndex(unsigned int count, unsigned int* index){
        unsigned int tempIndex = count;
        bool isEven = count % 2;
        bool valid = true;

        for(unsigned int i = 0; i < count / 2; i++){
            if (isEven){
                valid = GetRightIndex(tempIndex, &tempIndex);
            }
            else{
                valid = GetLeftIndex(tempIndex, &tempIndex);
            }
            
            if (!valid) break;
        }

        *index = tempIndex;

        return valid;
    }

    virtual bool GetAlternateYIndex(unsigned int count, unsigned int* index){
        unsigned int tempIndex = count;
        bool isEven = count % 2;
        bool valid = true;

        for(unsigned int i = 0; i < count / 2; i++){
            if (isEven){
                valid = GetUpIndex(tempIndex, &tempIndex);
            }
            else{
                valid = GetDownIndex(tempIndex, &tempIndex);
            }
            
            if (!valid) break;
        }
        
        *index = tempIndex;

        return valid;
    }

    virtual bool GetOffsetXIndex(unsigned int count, unsigned int* index, int x1) override {
        unsigned int tempIndex = count;
        bool valid = true;

        for(int i = 0; i < x1; i++){
            if (x1 > 0) valid = GetRightIndex(tempIndex, &tempIndex);
            else if (x1 < 0) valid = GetLeftIndex(tempIndex, &tempIndex);
            else break;
            
            if (!valid) break;
        }
        
        *index = tempIndex;

        return valid;
    }

    virtual bool GetOffsetYIndex(unsigned int count, unsigned int* index, int y1) override {
        unsigned int tempIndex = count;
        bool valid = true;
        
        for(int i = 0; i < y1; i++){
            if (y1 > 0) valid = GetUpIndex(tempIndex, &tempIndex);
            else if (y1 < 0) valid = GetDownIndex(tempIndex, &tempIndex);
            else break;
            
            if (!valid) break;
        }
        
        *index = tempIndex;

        return valid;
    }

    virtual bool GetOffsetXYIndex(unsigned int count, unsigned int* index, int x1, int y1) override {
        unsigned int tempIndex = count;
        bool valid = true;

        for(int i = 0; i < fabs(x1); i++){
            if (x1 > 0) valid = GetRightIndex(tempIndex, &tempIndex);
            else if (x1 < 0) valid = GetLeftIndex(tempIndex, &tempIndex);
            else break;
            
            if (!valid) break;
        }
        
        for(int i = 0; i < fabs(y1); i++){
            if (y1 > 0) valid = GetUpIndex(tempIndex, &tempIndex);
            else if (y1 < 0) valid = GetDownIndex(tempIndex, &tempIndex);
            else break;
            
            if (!valid) break;
        }
        
        *index = tempIndex;

        return valid;
    }

    virtual bool GetRadialIndex(unsigned int count, unsigned int* index, int pixels, float angle) override {//walks in the direction of the angle to a target pixel to grab an index
        int x1 = int(float(pixels) * cosf(angle * Mathematics::MPID180));
        int y1 = int(float(pixels) * sinf(angle * Mathematics::MPID180));

        unsigned int tempIndex = count;
        bool valid = true;

        int previousX = 0;
        int previousY = 0;

        int x = 0;
        int y = 0;

        for(int i = 0; i < pixels; i++){
            x = Mathematics::Map(i, 0, pixels, 0, x1);
            y = Mathematics::Map(i, 0, pixels, 0, y1);

            for (int k = 0; k < abs(x - previousX); k++){
                if (x > previousX) valid = GetRightIndex(tempIndex, &tempIndex);
                else if (x < previousX) valid = GetLeftIndex(tempIndex, &tempIndex);
                if (!valid) break;
            }

            if (!valid) break;

            for (int k = 0; k < abs(y - previousY); k++){
                if (y > previousY) valid = GetUpIndex(tempIndex, &tempIndex);
                else if (y < previousY) valid = GetDownIndex(tempIndex, &tempIndex);
                if (!valid) break;
            }
            
            if (!valid) break;

            previousX = x;
            previousY = y;
        }

        *index = tempIndex;

        return valid;
    }

    virtual void GridSort() override {
        if(!isRectangular){
            // Loop through all pixels
            for (unsigned int i = 0; i < pixelCount; i++) {
                Vector2D& currentPos = direction == ZEROTOMAX ? pixelPositions[i] : pixelPositions[pixelCount - i - 1];

                // Initialize the minimum distances and indices to the first pixel
                float minUp = Mathematics::FLTMAX, minDown = Mathematics::FLTMAX, minLeft = Mathematics::FLTMAX, minRight = Mathematics::FLTMAX;
                int minUpIndex = -1, minDownIndex = -1, minLeftIndex = -1, minRightIndex = -1;

                // Loop through all other pixels
                for (unsigned int j = 0; j < pixelCount; j++) {
                    if (i == j) { continue; } // Skip the current pixel

                    Vector2D& neighborPos = direction == ZEROTOMAX ? pixelPositions[j] : pixelPositions[pixelCount - j - 1];

                    // Calculate the distances between the current pixel and the other pixel
                    float dist = currentPos.CalculateEuclideanDistance(neighborPos);

                    // Check if the other pixel is above or below the current pixel
                    if (Mathematics::IsClose(currentPos.X, neighborPos.X, 1.0f)) {
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
                    if (Mathematics::IsClose(currentPos.Y, neighborPos.Y, 1.0f)) {
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
                    up[i] = minUpIndex;
                    upExists[i] = true;
                }

                if (minDownIndex != -1) {
                    down[i] = minDownIndex;
                    downExists[i] = true;
                }

                if (minLeftIndex != -1) {
                    left[i] = minLeftIndex;
                    leftExists[i] = true;
                }

                if (minRightIndex != -1) {
                    right[i] = minRightIndex;
                    rightExists[i] = true;
                }
            }
        }
        //else do nothing
    }

    void ListPixelNeighbors(){
        for(unsigned int i = 0; i < pixelCount; i++){
            Serial.print(i); Serial.print('\t');
            Serial.print(up[i]); Serial.print('\t');
            Serial.print(down[i]); Serial.print('\t');
            Serial.print(left[i]); Serial.print('\t');
            Serial.print(right[i]); Serial.print('\t');
            Serial.print(upExists[i]); Serial.print('\t');
            Serial.print(downExists[i]); Serial.print('\t');
            Serial.print(leftExists[i]); Serial.print('\t');
            Serial.print(rightExists[i]); Serial.print('\n');
        }
    }
};
