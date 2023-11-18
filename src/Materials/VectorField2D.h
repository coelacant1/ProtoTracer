#pragma once

#include "..\Math\Vector2D.h"
#include "..\Render\Triangle2D.h"
#include "..\Render\Object3D.h"

class VectorField2D : public Material {
private:
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
    VectorField2D(uint16_t x, uint16_t y);

    ~VectorField2D();

    void Boundary();

    void Diffuse(float viscosity, float dt);

    void Advect(float dt);

    void SineField(float ratio, float period, float amplitude);

    void StepField(float ratio, float period, float intensity);

    void MovingSquareField(float ratio, float period, float intensity);

    void SpiralField(float ratio, float period, float amplitude);

    void ObjectField(Object3D* object, float intensity);

    uint16_t GetCountX();

    uint16_t GetCountY();

    void RenderDensity();

    void RenderVector();

    void SetSize(float sizeX, float sizeY);

    void SetPosition(float posX, float posY);

    void SetRotation(float rotation);

    uint32_t GetVectorAtPosition(float x, float y, bool& inBounds);

    RGBColor GetRGB(Vector3D position, Vector3D normal, Vector3D uvw) override;
};
