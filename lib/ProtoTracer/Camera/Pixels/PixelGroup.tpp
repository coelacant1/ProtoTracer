#pragma once

template<size_t pixelCount>
PixelGroup<pixelCount>::PixelGroup(Vector2D size, Vector2D position, uint16_t rowCount){
    this->size = size;
    this->position = position;
    this->rowCount = rowCount;
    this->colCount = pixelCount / rowCount;

    isRectangular = true;

    bounds.UpdateBounds(position);
    bounds.UpdateBounds(position + size);

    for(uint16_t i = 0; i < pixelCount; i++){
        pixelColors[i] = RGBColor();
        pixelBuffer[i] = RGBColor();

        up[i] = 65535;
        down[i] = 65535;
        left[i] = 65535;
        right[i] = 65535;
    }

    GridSort();
}

template<size_t pixelCount>
PixelGroup<pixelCount>::PixelGroup(const Vector2D* pixelLocations, Direction direction){
    this->direction = direction;
    pixelPositions = pixelLocations;

    for(uint16_t i = 0; i < pixelCount; i++){
        pixelColors[i] = RGBColor();
        pixelBuffer[i] = RGBColor();

        bounds.UpdateBounds(pixelLocations[i]);

        up[i] = 65535;
        down[i] = 65535;
        left[i] = 65535;
        right[i] = 65535;
    }

    GridSort();
}

template<size_t pixelCount>
PixelGroup<pixelCount>::~PixelGroup(){}

template<size_t pixelCount>
Vector2D PixelGroup<pixelCount>::GetCenterCoordinate(){
    return (bounds.GetMaximum() + bounds.GetMinimum()) / 2.0f;
}

template<size_t pixelCount>
Vector2D PixelGroup<pixelCount>::GetSize(){
    return bounds.GetMaximum() - bounds.GetMinimum();
}

template<size_t pixelCount>
Vector2D PixelGroup<pixelCount>::GetCoordinate(uint16_t count){
    count = Mathematics::Constrain<int>(count, 0, pixelCount);

    if (isRectangular){
        float row = count % rowCount;
        float col = (count - row) / rowCount;

        tempLocation.X = Mathematics::Map(row, 0.0f, float(rowCount), position.X, position.X + size.X);
        tempLocation.Y = Mathematics::Map(col, 0.0f, float(colCount), position.Y, position.Y + size.Y);

        return tempLocation;
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

template<size_t pixelCount>
int PixelGroup<pixelCount>::GetPixelIndex(Vector2D location){
    float row = Mathematics::Map(location.X, position.X, position.X + size.X, 0.0f, float(rowCount));
    float col = Mathematics::Map(location.Y, position.Y, position.Y + size.Y, 0.0f, float(colCount));

    uint16_t count = row + col * rowCount;

    if (count < pixelCount && count > 0 && row > 0 && row < rowCount && col > 0 && col < colCount){
        return count;
    }
    else{
        return -1;
    }
}

template<size_t pixelCount>
RGBColor* PixelGroup<pixelCount>::GetColor(uint16_t count){
    return &pixelColors[count];
}

template<size_t pixelCount>
RGBColor* PixelGroup<pixelCount>::GetColors(){
    return &pixelColors[0];
}

template<size_t pixelCount>
RGBColor* PixelGroup<pixelCount>::GetColorBuffer(){
    return &pixelBuffer[0];
}

template<size_t pixelCount>
uint16_t PixelGroup<pixelCount>::GetPixelCount(){
    return pixelCount;
}

template<size_t pixelCount>
bool PixelGroup<pixelCount>::Overlaps(BoundingBox2D* box){
    return bounds.Overlaps(box);
}

template<size_t pixelCount>
bool PixelGroup<pixelCount>::ContainsVector2D(Vector2D v){
    return v.CheckBounds(bounds.GetMinimum(), bounds.GetMaximum());
}

template<size_t pixelCount>
bool PixelGroup<pixelCount>::GetUpIndex(uint16_t count, uint16_t* upIndex){
    *upIndex = up[count];

    return up[count] < 65535;
}

template<size_t pixelCount>
bool PixelGroup<pixelCount>::GetDownIndex(uint16_t count, uint16_t* downIndex){
    *downIndex = down[count];

    return down[count] < 65535;
}

template<size_t pixelCount>
bool PixelGroup<pixelCount>::GetLeftIndex(uint16_t count, uint16_t* leftIndex){
    *leftIndex = left[count];

    return left[count] < 65535;
}

template<size_t pixelCount>
bool PixelGroup<pixelCount>::GetRightIndex(uint16_t count, uint16_t* rightIndex){
    *rightIndex = right[count];

    return right[count] < 65535;
}

template<size_t pixelCount>
bool PixelGroup<pixelCount>::GetAlternateXIndex(uint16_t count, uint16_t* index){
    uint16_t tempIndex = count;
    bool isEven = count % 2;
    bool valid = true;

    for(uint16_t i = 0; i < count / 2; i++){
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

template<size_t pixelCount>
bool PixelGroup<pixelCount>::GetAlternateYIndex(uint16_t count, uint16_t* index){
    uint16_t tempIndex = count;
    bool isEven = count % 2;
    bool valid = true;

    for(uint16_t i = 0; i < count / 2; i++){
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

template<size_t pixelCount>
bool PixelGroup<pixelCount>::GetOffsetXIndex(uint16_t count, uint16_t* index, int x1){
    uint16_t tempIndex = count;
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

template<size_t pixelCount>
bool PixelGroup<pixelCount>::GetOffsetYIndex(uint16_t count, uint16_t* index, int y1){
    uint16_t tempIndex = count;
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

template<size_t pixelCount>
bool PixelGroup<pixelCount>::GetOffsetXYIndex(uint16_t count, uint16_t* index, int x1, int y1){
    uint16_t tempIndex = count;
    bool valid = true;

    for(int i = 0; i < abs(x1); i++){
        if (x1 > 0) valid = GetRightIndex(tempIndex, &tempIndex);
        else if (x1 < 0) valid = GetLeftIndex(tempIndex, &tempIndex);
        else break;
        
        if (!valid) break;
    }
    
    for(int i = 0; i < abs(y1); i++){
        if (y1 > 0) valid = GetUpIndex(tempIndex, &tempIndex);
        else if (y1 < 0) valid = GetDownIndex(tempIndex, &tempIndex);
        else break;
        
        if (!valid) break;
    }
    
    *index = tempIndex;

    return valid;
}

template<size_t pixelCount>
bool PixelGroup<pixelCount>::GetRadialIndex(uint16_t count, uint16_t* index, int pixels, float angle){//walks in the direction of the angle to a target pixel to grab an index
    int x1 = int(float(pixels) * cosf(angle * Mathematics::MPID180));
    int y1 = int(float(pixels) * sinf(angle * Mathematics::MPID180));

    uint16_t tempIndex = count;
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

template<size_t pixelCount>
void PixelGroup<pixelCount>::GridSort(){
    if(!isRectangular){
        // Loop through all pixels
        for (uint16_t i = 0; i < pixelCount; i++) {
            Vector2D currentPos;
            
            if(!isRectangular) currentPos = direction == ZEROTOMAX ? pixelPositions[i] : pixelPositions[pixelCount - i - 1];
            else currentPos = direction == ZEROTOMAX ? GetCoordinate(i) : GetCoordinate(pixelCount - i - 1);

            // Initialize the minimum distances and indices to the first pixel
            float minUp = Mathematics::FLTMAX, minDown = Mathematics::FLTMAX, minLeft = Mathematics::FLTMAX, minRight = Mathematics::FLTMAX;
            int minUpIndex = -1, minDownIndex = -1, minLeftIndex = -1, minRightIndex = -1;

            // Loop through all other pixels
            for (uint16_t j = 0; j < pixelCount; j++) {
                if (i == j) { continue; } // Skip the current pixel

                Vector2D neighborPos;
                
                if(!isRectangular) neighborPos = direction == ZEROTOMAX ? pixelPositions[j] : pixelPositions[pixelCount - j - 1];
                else currentPos = direction == ZEROTOMAX ? GetCoordinate(j) : GetCoordinate(pixelCount - j - 1);

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
            if (minUpIndex != -1) up[i] = minUpIndex;
            if (minDownIndex != -1) down[i] = minDownIndex;

            if (minLeftIndex != -1) left[i] = minLeftIndex;
            if (minRightIndex != -1) right[i] = minRightIndex;
        }
    }
    else {//optimized algorithm for rectangular matrices
        for (int i = 0; i < int(pixelCount); i++) {
            if (i + int(rowCount) < int(pixelCount) - 1) up[i] = uint16_t(i) + rowCount;//up
            if (i - int(rowCount) > 1) down[i] = uint16_t(i) - rowCount;//down
            
            if (!(i % rowCount == 0) && i > 1) left[i] = uint16_t(i) - 1;//left
            if (!(i % rowCount + 1 == 0) && i < int(pixelCount) - 1) right[i] = uint16_t(i) + 1;//right
        }
    }
}
