#pragma once

#include "Arduino.h"
#include "GradientMaterial.h"
#include "..\Math\Vector2D.h"

class VectorField2D : public Material{
private:
    GradientMaterial* colorDirection;
    Vector2D* vectors;
    Vector2D size;
    Vector2D position;
    const uint16_t countX;
    const uint16_t countY;
    float rotation = 0.0f;

    Vector2D BilinearInterpolation(Vector2D input, Vector2D q11, Vector2D q12, Vector2D q21, Vector2D q22){//assuming unit size 1
        Vector2D v2v1;

        float iX = 1.0f - input.X;
        float iY = 1.0f - input.Y;
        float x = input.X;
        float y = input.Y;

        float outX = q11.X * iX * iY + q21.X * x * y + q12.X * iX * y + q22.X * x * y;
        float outY = q11.Y * iX * iY + q21.Y * x * y + q12.Y * iX * y + q22.Y * x * y;

        return Vector2D(outX, outY);
    }

public:
    VectorField2D(uint16_t x, uint16_t y, GradientMaterial* colorDirection) : countX(x), countY(y){
        this->vectors = new Vector2D[x * y];
        this->colorDirection = colorDirection;
    }

    ~VectorField2D(){
        delete vectors;
    }

    void SineField(float ratio, float period, float amplitude){
        for(int x = 0; x < countX; x++){
            for(int y = 0; y < countY; y++){
                float posX = x * size.X;
                float posY = y * size.Y;

                uint32_t index = x + countX * y;

                vectors[index].X = sinf((posX + posY) / (period * 6.28f) + ratio * 6.28f) * amplitude;
                vectors[index].Y = cosf((posX - posY) / (period * 6.28f) + ratio * 6.28f) * amplitude;
            }
        }
    }

    uint16_t GetCountX(){
        return countX;
    }

    uint16_t GetCountY(){
        return countY;
    }

    Vector2D* GetVectors(){
        return vectors;
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

    Vector2D GetVectorAtPosition(float x, float y, bool &inBounds){//interpolates 2D vector from field
        Vector2D input = Vector2D(x, y);

        input = input - position + size / 2.0f;

        //rotate input coordinate to local coordinate
        if (!Mathematics::IsClose(rotation, 0.0f, 0.001f)){
            input = input.Rotate(rotation, size / 2.0f);//rotate by center coordinate
        }


        //input = input.Multiply(size.Subtract(Vector2D(1, 1)));

        inBounds = input.X > 0  && input.X < size.X &&
                   input.Y > 0  && input.Y < size.Y;

        if (inBounds){
            float scaleX = Mathematics::Map(input.X, 0, size.X, 0, countX - 1);
            float scaleY = Mathematics::Map(input.Y, 0, size.Y, 0, countY - 1);
            uint16_t colX = (uint16_t)floorf(scaleX);
            uint16_t rowY = (uint16_t)floorf(scaleY);
            
            //weights between vectors
            Vector2D ratio = Vector2D(scaleX - colX, input.Y - rowY);

            //Vector corners
            Vector2D q11 = vectors[colX + countX * rowY];
            Vector2D q12 = vectors[(colX + 1) + countX * rowY];
            Vector2D q21 = vectors[colX + countX * (rowY + 1)];
            Vector2D q22 = vectors[(colX + 1) + countX * (rowY + 1)];

            return q11;//BilinearInterpolation(ratio, q11, q12, q21, q22);
        }
        else{
            return Vector2D();
        }
    }

    //Render density map of vector field, no magnitude will be black, direction specifies color
    RGBColor GetRGB(Vector3D position, Vector3D normal, Vector3D uvw) override{
        bool inBounds = false;
        Vector2D weighting = GetVectorAtPosition(position.X, position.Y, inBounds);

        if (inBounds){
            float ratio = atan2f(weighting.Y, weighting.X) / 6.28f;//0.0 -> 1.0f around circle

            RGBColor gradient = colorDirection->GetRGB(Vector3D(ratio, 0, 0), Vector3D(), Vector3D());

            RGBColor rgbW = RGBColor::InterpolateColors(RGBColor(255, 255, 255), gradient, 1.0f - weighting.Magnitude() / 2.0f + 0.5f);
            rgbW = RGBColor::InterpolateColors(gradient, RGBColor(0, 0, 0), 1.0f - weighting.Magnitude() / 2.0f);

            return rgbW;
        }
        else{
            return RGBColor(0, 0, 0);
        }
    }

};
