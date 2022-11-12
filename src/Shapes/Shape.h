#pragma once

#include "..\Math\Vector2D.h"

class Shape {
protected:
    Vector2D center;//shape centered on this point
    Vector2D size;//shape large enough to fit within rectangle
    float rotation;

public:
    Shape(Vector2D center, Vector2D size, float rotation) : center(center), size(size), rotation(rotation){}

    void SetCenter(Vector2D center){
        this->center = center;
    }

    void Translate(Vector2D offset){
        this->center = center + offset;
    }

    Vector2D GetCenter(){
        return center;
    }

    void SetSize(Vector2D size){
        this->size = size;
    }

    void Scale(Vector2D scale){
        this->size = size * scale;
    }

    Vector2D GetSize(){
        return size;
    }

    void SetRotation(float rotation){
        this->rotation = rotation;
    }

    void Rotate(float offset){
        this->rotation = rotation + offset;
    }

    float GetRotation(){
        return rotation;
    }

    virtual bool IsInShape(Vector2D point) = 0;

};
