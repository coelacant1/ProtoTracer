#pragma once

#include "Arduino.h"
#include "GradientMaterial.h"
#include "..\Math\Vector2D.h"
#include "..\Render\Scene.h"
#include "..\Render\Triangle2D.h"
#include "..\Render\PixelGroup.h"

class VectorField2D : public Material{
private:
    GradientMaterial* colorDirection;
    int8_t* vecXP;
    int8_t* vecYP;
    int8_t* vecDP;
    int8_t* vecX;
    int8_t* vecY;
    int8_t* vecD;

    Vector2D size;
    Vector2D position;
    const uint16_t countX;
    const uint16_t countY;
    float rotation = 0.0f;
    bool density = false;

public:
    VectorField2D(uint16_t x, uint16_t y, GradientMaterial* colorDirection) : countX(x), countY(y){
        this->vecXP = new int8_t[x * y];
        this->vecYP = new int8_t[x * y];
        this->vecDP = new int8_t[x * y];
        this->vecX = new int8_t[x * y];
        this->vecY = new int8_t[x * y];
        this->vecD = new int8_t[x * y];
        this->colorDirection = colorDirection;
    }

    ~VectorField2D(){
        delete vecXP;
        delete vecYP;
        delete vecDP;
        delete vecX;
        delete vecY;
        delete vecD;
    }

    void Boundary(){
        //handle edges
    }
    
    void Diffuse(float viscosity, float dt){
        float a = dt * viscosity * (float)countX * (float)countY;
        float aS = 1.0f + (4.0f * a);

        for (uint32_t i = 0; i < countX * countY; i++){
            vecDP[i] = Mathematics::Constrain(vecD[i] - 1.0f, 0, 127);
        }

        for (int x = 1; x < countX - 1; x++){
            for (int y = 1; y < countY - 1; y++){
                uint32_t index = x + countX * y;
                uint32_t top = x + countX * (y - 1);
                uint32_t bot = x + countX * (y + 1);
                uint32_t rgt = index + 1;
                uint32_t lft = index - 1;

                float value = ((float)vecDP[index] + a * ((float)vecD[top] + (float)vecD[bot] + (float)vecD[rgt] + (float)vecD[lft])) / aS;

                vecD[index] = value;
            }
        }
        
        //Boundary();
    }

    void Advect(float dt){
        int x0, x1, y0, y1;
        float s0, s1, t0, t1;

        float dtX = dt * (float)countX;
        float dtY = dt * (float)countY;

        for (int x = 1; x < countX - 1; x++){
            for (int y = 1; y < countY - 1; y++){
                uint32_t index = x + countX * y;
                float xA = (float)x - dtX * (float)vecX[index];
                float yA = (float)y - dtY * (float)vecY[index];

                if(xA < 0.5f) xA = 0.5f;
                if(xA > countX + 0.5f) xA = countX + 0.5f;
                x0 = (int)xA;
                x1 = x0 + 1;

                if(yA < 0.5f) yA = 0.5f;
                if(yA > countY + 0.5f) yA = countY + 0.5f;
                y0 = (int)yA;
                y1 = y0 + 1;

                s1 = xA - x0;
                s0 = 1.0f - s1;
                t1 = yA - y0;
                t0 = 1.0f - t1;
                
                float td00 = t0 * (float)vecDP[Mathematics::Constrain(x0 + countX * y0, 0, index)];
                float td01 = t1 * (float)vecDP[Mathematics::Constrain(x0 + countX * y1, 0, index)];
                float td10 = t0 * (float)vecDP[Mathematics::Constrain(x1 + countX * y0, 0, index)];
                float td11 = t1 * (float)vecDP[Mathematics::Constrain(x1 + countX * y1, 0, index)];
                
                float value = s0 * (td00 + td01) + s1 * (td10 + td11);

                vecD[index] = value;
            }
        }
        
        //Boundary();
    }


    void SineField(float ratio, float period, float amplitude){
        for(int x = 0; x < countX; x++){
            for(int y = 0; y < countY; y++){
                float posX = (((float)x) / ((float)countX) - 0.5f) * 2.0f * size.X;
                float posY = (((float)y) / ((float)countY) - 0.5f) * 2.0f * size.Y;

                uint32_t index = x + countX * y;

                vecX[index] = Mathematics::Constrain(sinf((posX + posY) / (period * 6.28f * 1000.0f) + ratio * 6.28f) * amplitude, -1.0f, 1.0f) * 127.0f;
                vecY[index] = Mathematics::Constrain(cosf((posX - posY) / (period * 6.28f * 1000.0f) + ratio * 6.28f) * amplitude, -1.0f, 1.0f) * 127.0f;
                vecD[index] = Mathematics::Constrain((sinf((posX + posY) / (period * 6.28f * 50.0f)) + cosf((posX - posY) / (period * 6.28f * 50.0f))) * amplitude, -1.0f, 1.0f) * 127.0f;
            }
        }
    }

    void StepField(float ratio, float period, float intensity){
        float offsetX = sinf(ratio * 2.0f * Mathematics::MPI * 2.0f) * period;
        float offsetY = cosf(ratio * 2.0f * Mathematics::MPI * 2.0f) * period; 

        for(int x = 0; x < countX; x++){
            for(int y = 0; y < countY; y++){
                float posX = (((float)x) / ((float)countX) - 0.5f) * 2.0f * size.X + offsetX;
                float posY = (((float)y) / ((float)countY) - 0.5f) * 2.0f * size.Y + offsetY;

                uint32_t index = x + countX * y;
                
                bool xOdd = (int)(posX * 0.3f / (10.0f / period)) % 2;
                bool yOdd = (int)(posY * 0.3f / (10.0f / period)) % 2;

                vecX[index] = xOdd ? 127 : -128;
                vecY[index] = yOdd ? 127 : -128;
                if (xOdd != yOdd) vecD[index] = Mathematics::Constrain(vecD[index] + intensity, 0, 127);
                
            }
        }
    }

    void MovingSquareField(float ratio, float period, float intensity){
        float offsetX = sinf(ratio * 2.0f * Mathematics::MPI * 2.0f) * period;
        float offsetY = cosf(ratio * 2.0f * Mathematics::MPI * 2.0f) * period; 

        for(int x = 0; x < countX; x++){
            for(int y = 0; y < countY; y++){
                float posX = (((float)x) / ((float)countX) - 0.5f) * 2.0f * size.X + offsetX;
                float posY = (((float)y) / ((float)countY) - 0.5f) * 2.0f * size.Y + offsetY;

                uint32_t index = x + countX * y;

                if (posX < period / 2.0f && posX > -period / 2.0f && posY < period / 2.0f && posY > -period / 2.0f){
                    //vecX[index] = 0;
                    //vecY[index] = 0;
                    vecD[index] = Mathematics::Constrain(vecD[index] + intensity, 0, 127);
                }
                else {
                    //vecX[index] = -intensity;
                    //vecY[index] = -128;
                    //vecD[index] = 0;
                }
            }
        }
    }
    
    void SpiralField(float ratio, float period, float amplitude){
        for(int x = 0; x < countX; x++){
            for(int y = 0; y < countY; y++){
                float posX = (((float)x) / ((float)countX) - 0.5f) * 2.0f * size.X;
                float posY = (((float)y) / ((float)countY) - 0.5f) * 2.0f * size.Y;

                float magn = powf(posX * posX + posY * posY, 0.5f);

                uint32_t index = x + countX * y;

                vecX[index] = Mathematics::Constrain((posX * cosf(2.0f * magn * period / 40.0f)) * 0.01f * amplitude, -1.0f, 1.0f) * 127.0f;// / (size.X / 2.0f);
                vecY[index] = Mathematics::Constrain((posY * sinf(2.0f * magn * period / 40.0f)) * 0.01f * amplitude, -1.0f, 1.0f) * 127.0f;// / (size.Y / 2.0f);
            }
        }
    }

    //Simplified pixel rasterizer
    void ObjectField(Object3D* object, float intensity) {
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
                    vecD[index] = Mathematics::Constrain(vecD[index] + intensity, 0, 127);
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

    uint16_t GetCountX(){
        return countX;
    }

    uint16_t GetCountY(){
        return countY;
    }

    void RenderDensity(){
        this->density = true;
    }

    void RenderVector(){
        this->density = false;
    }

    void SetSize(float sizeX, float sizeY){
        this->size.X = sizeX;
        this->size.Y = sizeY;
    }

    void SetPosition(float posX, float posY){
        this->position.X = posX;
        this->position.Y = posY;
    }

    void SetRotation(float rotation){
        this->rotation = rotation;
    }

    uint32_t GetVectorAtPosition(float x, float y, bool &inBounds){//interpolates 2D vector from field
        Vector2D input = Vector2D(x, y);

        input = input - position + size / 2.0f;

        //rotate input coordinate to local coordinate
        if (!Mathematics::IsClose(rotation, 0.0f, 0.001f)){
            input = input.Rotate(rotation, size / 2.0f);//rotate by center coordinate
        }

        inBounds = input.X > 0  && input.X < size.X &&
                   input.Y > 0  && input.Y < size.Y;

        if (inBounds){
            float scaleX = Mathematics::Map(input.X, 0, size.X, 0, countX - 1);
            float scaleY = Mathematics::Map(input.Y, 0, size.Y, 0, countY - 1);
            uint16_t colX = (uint16_t)floorf(scaleX);
            uint16_t rowY = (uint16_t)floorf(scaleY);
            
            //Vector corners
            uint32_t q11 = colX + countX * rowY;
            //Vector2D q12 = vectors[(colX + 1) + countX * rowY];
            //Vector2D q21 = vectors[colX + countX * (rowY + 1)];
            //Vector2D q22 = vectors[(colX + 1) + countX * (rowY + 1)];

            //weights between vectors
            //Vector2D ratio = Vector2D(scaleX - colX, input.Y - rowY);

            return q11;//BilinearInterpolation(ratio, q11, q12, q21, q22);
        }
        else{
            return 0;
        }
    }

    //Render density map of vector field, no magnitude will be black, direction specifies color
    RGBColor GetRGB(Vector3D position, Vector3D normal, Vector3D uvw) override{
        bool inBounds = false;
        uint32_t index = GetVectorAtPosition(position.X, position.Y, inBounds);

        if (inBounds){
            float x = ((float)vecX[index]) / 127.0f;
            float y = ((float)vecY[index]) / 127.0f;
            float d = ((float)vecD[index]) / 127.0f;

            float ratio = (atan2f(y, x) / Mathematics::MPI + 1.0f) / 2.0f;//0.0 -> 1.0f around circle
            float magn = Mathematics::Constrain(powf(x * x + y * y, 0.5f), 0.0f, 1.0f);
            
            RGBColor gradient;
            
            if (density){
                if (d < 0.0f) return RGBColor(0,0,0);
                gradient = colorDirection->GetRGB(Vector3D(d, 0, 0), Vector3D(), Vector3D());
                //gradient = RGBColor::InterpolateColors(RGBColor(0, 0, 0), RGBColor(255, 255, 255), (d + 1.0f) / 2.0f);

                if(d > 0.5f) gradient = RGBColor::InterpolateColors(gradient, RGBColor(255, 255, 255), (d - 0.5f) * 2.0f);
                else gradient = RGBColor::InterpolateColors(RGBColor(0, 0, 0), gradient, d * 2.0f);
            }
            else{
                gradient = colorDirection->GetRGB(Vector3D(ratio, 0, 0), Vector3D(), Vector3D());
                if(magn > 0.5f) gradient = RGBColor::InterpolateColors(gradient, RGBColor(255, 255, 255), (magn - 0.5f) * 2.0f);
                else gradient = RGBColor::InterpolateColors(RGBColor(0, 0, 0), gradient, magn * 2.0f);
            }

            return gradient;
        }
        else{
            return RGBColor(0, 0, 0);
        }
    }

};
