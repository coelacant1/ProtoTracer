#include "VectorField2D.h"

VectorField2D::VectorField2D(uint16_t x, uint16_t y)
    : countX(x), countY(y) {
    this->vecXP = new int8_t[x * y];
    this->vecYP = new int8_t[x * y];
    this->vecDP = new int8_t[x * y];
    this->vecX = new int8_t[x * y];
    this->vecY = new int8_t[x * y];
    this->vecD = new int8_t[x * y];
}

VectorField2D::~VectorField2D() {
    delete vecXP;
    delete vecYP;
    delete vecDP;
    delete vecX;
    delete vecY;
    delete vecD;
}

void VectorField2D::Boundary() {
    // Handle edges
}

void VectorField2D::Diffuse(float viscosity, float dt) {
    float a = dt * viscosity * (float)countX * (float)countY;
    float aS = 1.0f + (4.0f * a);

    for (uint32_t i = 0; i < countX * countY; i++) {
        vecDP[i] = Mathematics::Constrain(vecD[i] - 1, 0, 127);
    }

    for (int x = 1; x < countX - 1; x++) {
        for (int y = 1; y < countY - 1; y++) {
            uint32_t index = x + countX * y;
            uint32_t top = x + countX * (y - 1);
            uint32_t bot = x + countX * (y + 1);
            uint32_t rgt = index + 1;
            uint32_t lft = index - 1;

            float value = ((float)vecDP[index] + a * ((float)vecD[top] + (float)vecD[bot] + (float)vecD[rgt] + (float)vecD[lft])) / aS;

            vecD[index] = value;
        }
    }

    // Boundary();
}

void VectorField2D::Advect(float dt) {
    int x0, x1, y0, y1;
    float s0, s1, t0, t1;

    float dtX = dt * (float)countX;
    float dtY = dt * (float)countY;

    for (int x = 1; x < countX - 1; x++) {
        for (int y = 1; y < countY - 1; y++) {
            uint32_t index = x + countX * y;
            float xA = (float)x - dtX * (float)vecX[index];
            float yA = (float)y - dtY * (float)vecY[index];

            if (xA < 0.5f) xA = 0.5f;
            if (xA > countX + 0.5f) xA = countX + 0.5f;
            x0 = (int)xA;
            x1 = x0 + 1;

            if (yA < 0.5f) yA = 0.5f;
            if (yA > countY + 0.5f) yA = countY + 0.5f;
            y0 = (int)yA;
            y1 = y0 + 1;

            s1 = xA - x0;
            s0 = 1.0f - s1;
            t1 = yA - y0;
            t0 = 1.0f - t1;

            float td00 = t0 * (float)vecDP[Mathematics::Constrain(uint32_t(x0 + countX * y0), uint32_t(0), index)];
            float td01 = t1 * (float)vecDP[Mathematics::Constrain(uint32_t(x0 + countX * y1), uint32_t(0), index)];
            float td10 = t0 * (float)vecDP[Mathematics::Constrain(uint32_t(x1 + countX * y0), uint32_t(0), index)];
            float td11 = t1 * (float)vecDP[Mathematics::Constrain(uint32_t(x1 + countX * y1), uint32_t(0), index)];

            float value = s0 * (td00 + td01) + s1 * (td10 + td11);

            vecD[index] = value;
        }
    }

    // Boundary();
}

void VectorField2D::SineField(float ratio, float period, float amplitude) {
    for (int x = 0; x < countX; x++) {
        for (int y = 0; y < countY; y++) {
            float posX = (((float)x) / ((float)countX) - 0.5f) * 2.0f * size.X;
            float posY = (((float)y) / ((float)countY) - 0.5f) * 2.0f * size.Y;

            uint32_t index = x + countX * y;

            vecX[index] = Mathematics::Constrain(sinf((posX + posY) / (period * 6.28f * 1000.0f) + ratio * 6.28f) * amplitude, -1.0f, 1.0f) * 127.0f;
            vecY[index] = Mathematics::Constrain(cosf((posX - posY) / (period * 6.28f * 1000.0f) + ratio * 6.28f) * amplitude, -1.0f, 1.0f) * 127.0f;
            vecD[index] = Mathematics::Constrain((sinf((posX + posY) / (period * 6.28f * 50.0f)) + cosf((posX - posY) / (period * 6.28f * 50.0f))) * amplitude, -1.0f, 1.0f) * 127.0f;
        }
    }
}

void VectorField2D::StepField(float ratio, float period, float intensity) {
    float offsetX = sinf(ratio * 2.0f * Mathematics::MPI * 2.0f) * period;
    float offsetY = cosf(ratio * 2.0f * Mathematics::MPI * 2.0f) * period;

    for (int x = 0; x < countX; x++) {
        for (int y = 0; y < countY; y++) {
            float posX = (((float)x) / ((float)countX) - 0.5f) * 2.0f * size.X + offsetX;
            float posY = (((float)y) / ((float)countY) - 0.5f) * 2.0f * size.Y + offsetY;

            uint32_t index = x + countX * y;

            bool xOdd = (int)(posX * 0.3f / (10.0f / period)) % 2;
            bool yOdd = (int)(posY * 0.3f / (10.0f / period)) % 2;

            vecX[index] = xOdd ? 127 : -128;
            vecY[index] = yOdd ? 127 : -128;
            if (xOdd != yOdd) vecD[index] = Mathematics::Constrain(int8_t(vecD[index] + intensity), int8_t(0), int8_t(127));
        }
    }
}

void VectorField2D::MovingSquareField(float ratio, float period, float intensity) {
    float offsetX = sinf(ratio * 2.0f * Mathematics::MPI * 2.0f) * period;
    float offsetY = cosf(ratio * 2.0f * Mathematics::MPI * 2.0f) * period;

    for (int x = 0; x < countX; x++) {
        for (int y = 0; y < countY; y++) {
            float posX = (((float)x) / ((float)countX) - 0.5f) * 2.0f * size.X + offsetX;
            float posY = (((float)y) / ((float)countY) - 0.5f) * 2.0f * size.Y + offsetY;

            uint32_t index = x + countX * y;

            if (posX < period / 2.0f && posX > -period / 2.0f && posY < period / 2.0f && posY > -period / 2.0f) {
                vecD[index] = Mathematics::Constrain(int8_t(vecD[index] + intensity), int8_t(0), int8_t(127));
            } else {
                // vecX[index] = -intensity;
                // vecY[index] = -128;
                // vecD[index] = 0;
            }
        }
    }
}

void VectorField2D::SpiralField(float ratio, float period, float amplitude){
    for(int x = 0; x < countX; x++){
        for(int y = 0; y < countY; y++){
            float posX = (((float)x) / ((float)countX) - 0.5f) * 2.0f * size.X;
            float posY = (((float)y) / ((float)countY) - 0.5f) * 2.0f * size.Y;

            float magn = powf(posX * posX + posY * posY, 0.5f);

            uint32_t index = x + countX * y;

            vecX[index] = Mathematics::Constrain((posX * cosf(2.0f * magn * period / 40.0f)) * 0.01f * amplitude, -1.0f, 1.0f) * 127.0f;
            vecY[index] = Mathematics::Constrain((posY * sinf(2.0f * magn * period / 40.0f)) * 0.01f * amplitude, -1.0f, 1.0f) * 127.0f;
        }
    }
}

void VectorField2D::ObjectField(Object3D* object, float intensity) {
    int numTriangles = object->GetTriangleGroup()->GetTriangleCount();
    Triangle2D** triangles = new Triangle2D*[numTriangles];

    //for each triangle in object, project onto 2d surface, but pass material
    for (int i = 0; i < numTriangles; i++) {
        triangles[i] = new Triangle2D(&object->GetTriangleGroup()->GetTriangles()[i]);
    }

    //create current and next vector fields for advection simulation
    //do not use pixel groups, use vectors

    for(int x = 0; x < countX; x++){
        for(int y = 0; y < countY; y++){
            float posX = (((float)x) / ((float)countX) - 0.5f) * 2.0f * size.X;
            float posY = (((float)y) / ((float)countY) - 0.5f) * 2.0f * size.Y;

            uint32_t index = x + countX * y;
            
            float u = 0.0f, v = 0.0f, w = 0.0f;
            bool didIntersect = false;

            for (int t = 0; t < numTriangles; t++) {
                if (triangles[t]->DidIntersect(posX, posY, u, v, w)){
                    didIntersect = true;

                    break;
                }
            }

            if (didIntersect){
                vecX[index] = 127;
                vecY[index] = 127;
                vecD[index] = Mathematics::Constrain(int8_t(vecD[index] + intensity), int8_t(0), int8_t(127));
            }
            else{
                vecX[index] = 0;
                vecY[index] = 0;
                vecD[index] = 0;
            }
        }
    }

    for (int i = 0; i < numTriangles; i++){
        delete triangles[i];
    }
    
    delete[] triangles;
}

uint16_t VectorField2D::GetCountX(){
    return countX;
}

uint16_t VectorField2D::GetCountY(){
    return countY;
}

void VectorField2D::RenderDensity(){
    this->density = true;
}

void VectorField2D::RenderVector(){
    this->density = false;
}

void VectorField2D::SetSize(float sizeX, float sizeY){
    this->size.X = sizeX;
    this->size.Y = sizeY;
}

void VectorField2D::SetPosition(float posX, float posY){
    this->position.X = posX;
    this->position.Y = posY;
}

void VectorField2D::SetRotation(float rotation){
    this->rotation = rotation;
}

uint32_t VectorField2D::GetVectorAtPosition(float x, float y, bool &inBounds){
    Vector2D input = Vector2D(x, y);

    input = input - position + size / 2.0f;

    //rotate input coordinate to local coordinate
    if (!Mathematics::IsClose(rotation, 0.0f, 0.001f)){
        input = input.Rotate(rotation, size / 2.0f);//rotate by center coordinate
    }

    inBounds = input.X > 0  && input.X < size.X &&
               input.Y > 0  && input.Y < size.Y;

    if (inBounds){
        float scaleX = Mathematics::Map(input.X, 0.0f, size.X, 0.0f, countX - 1.0f);
        float scaleY = Mathematics::Map(input.Y, 0.0f, size.Y, 0.0f, countY - 1.0f);
        uint16_t colX = (uint16_t)floorf(scaleX);
        uint16_t rowY = (uint16_t)floorf(scaleY);
        
        //Vector corners
        uint32_t q11 = rowY * countX + colX;
        uint32_t q12 = rowY * countX + (colX + 1);
        uint32_t q21 = (rowY + 1) * countX + colX;
        uint32_t q22 = (rowY + 1) * countX + (colX + 1);
        
        //Bilinear interpolation
        float x1 = colX * (size.X / (float)(countX - 1));
        float x2 = (colX + 1) * (size.X / (float)(countX - 1));
        float y1 = rowY * (size.Y / (float)(countY - 1));
        float y2 = (rowY + 1) * (size.Y / (float)(countY - 1));
        
        float v11 = vecD[q11];
        float v12 = vecD[q12];
        float v21 = vecD[q21];
        float v22 = vecD[q22];
        
        float value = Mathematics::BilinearInterpolation(scaleX, scaleY, x1, y1, x2, y2, v11, v12, v21, v22);
        
        return (uint32_t)value;
    }

    return 0;
}

RGBColor VectorField2D::GetRGB(const Vector3D& position, const Vector3D& normal, const Vector3D& uvw){
    float x = uvw.X * size.X;
    float y = uvw.Y * size.Y;
    bool inBounds;
    uint32_t densityValue = GetVectorAtPosition(x, y, inBounds);

    if (inBounds){
        float red = (float)densityValue / 127.0f;
        float green = 0.0f;
        float blue = 1.0f - (float)densityValue / 127.0f;

        return RGBColor(red, green, blue);
    }

    return RGBColor(0.0f, 0.0f, 0.0f);
}
