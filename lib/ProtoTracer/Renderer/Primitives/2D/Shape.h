#pragma once

#include "..\..\..\Utils\Math\Vector2D.h"

class Shape {
protected:
    Vector2D center; // shape centered on this point
    Vector2D size;   // shape large enough to fit within rectangle
    float rotation;

public:
    Shape(Vector2D center, Vector2D size, float rotation);

    void SetCenter(Vector2D center);
    void Translate(Vector2D offset);
    Vector2D GetCenter();

    void SetSize(Vector2D size);
    void Scale(Vector2D scale);
    Vector2D GetSize();

    void SetRotation(float rotation);
    void Rotate(float offset);
    float GetRotation();

    virtual bool IsInShape(Vector2D point) = 0;
};
