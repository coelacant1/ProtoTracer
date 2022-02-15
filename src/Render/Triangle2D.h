#pragma once

#include "..\Materials\Material.h"
#include "..\Math\Transform.h"
#include "Triangle3D.h"
#include "..\Math\Vector2D.h"

class Triangle2D {
private:
    float denominator = 0.0f;

    float p1X, p1Y, p2X, p2Y, p3X, p3Y, v0X, v0Y, v1X, v1Y, v2X, v2Y;
  
public:
	Vector3D* normal;
    Material* material;

    Vector3D* t3p1;
    Vector3D* t3p2;
    Vector3D* t3p3;

	Vector2D* p1UV;
	Vector2D* p2UV;
	Vector2D* p3UV;

    bool hasUV = false;

    float averageDepth = 0.0f;

	Triangle2D(){}

	Triangle2D(Vector2D p1, Vector2D p2, Vector2D p3) {
		p1X = p1.X;
		p1Y = p1.Y;
		p2X = p2.X;
		p2Y = p2.Y;
		p3X = p3.X;
		p3Y = p3.Y;

        v0X = p2X - p1X;
        v0Y = p2Y - p1Y;
        v1X = p3X - p1X;
        v1Y = p3Y - p1Y;
        
        denominator = 1.0f / (v0X * v1Y - v1X * v0Y);
	}

	Triangle2D(Quaternion lookDirection, Transform* camT, Triangle3D* t, Material* material) {
        this->material = material;

        if (t->hasUV){
            this->p1UV = t->p1UV;
            this->p2UV = t->p2UV;
            this->p3UV = t->p3UV;

            this->hasUV = true;
        }

        Vector3D p1 = camT->GetRotation().Multiply(lookDirection).UnrotateVector(*t->p1 - camT->GetPosition());// * transform->GetScale()
        Vector3D p2 = camT->GetRotation().Multiply(lookDirection).UnrotateVector(*t->p2 - camT->GetPosition());
        Vector3D p3 = camT->GetRotation().Multiply(lookDirection).UnrotateVector(*t->p3 - camT->GetPosition());

        averageDepth = (p1.Z + p2.Z + p3.Z) / 3.0f;

		p1X = p1.X;
		p1Y = p1.Y;
		p2X = p2.X;
		p2Y = p2.Y;
		p3X = p3.X;
		p3Y = p3.Y;

        v0X = p2X - p1X;
        v0Y = p2Y - p1Y;
        v1X = p3X - p1X;
        v1Y = p3Y - p1Y;

        denominator = 1.0f / (v0X * v1Y - v1X * v0Y);

		normal = t->Normal();

        t3p1 = t->p1;
        t3p2 = t->p2;
        t3p3 = t->p3;
	}
    
	Triangle2D(Triangle3D* t) {
        averageDepth = (t->p1->Z + t->p2->Z + t->p3->Z) / 3.0f;

		p1X = t->p1->X;
		p1Y = t->p1->Y;
		p2X = t->p2->X;
		p2Y = t->p2->Y;
		p3X = t->p3->X;
		p3Y = t->p3->Y;

        v0X = p2X - p1X;
        v0Y = p2Y - p1Y;
        v1X = p3X - p1X;
        v1Y = p3Y - p1Y;

        denominator = 1.0f / (v0X * v1Y - v1X * v0Y);

        t3p1 = t->p1;
        t3p2 = t->p2;
        t3p3 = t->p3;
	}

    Vector2D GetP1(){
        return Vector2D(p1X, p1Y);
    }

    Vector2D GetP2(){
        return Vector2D(p2X, p2Y);
    }

    Vector2D GetP3(){
        return Vector2D(p3X, p3Y);
    }

    Material* GetMaterial(){
        return material;
    }

    bool DidIntersect(float x, float y, float& u, float& v, float& w) {
        v2X = x - p1X;
        v2Y = y - p1Y;

        v = (v2X * v1Y - v1X * v2Y) * denominator;
        if (v <= 0.0f) return false;
        if (v >= 1.0f) return false;

        w = (v0X * v2Y - v2X * v0Y) * denominator;
        if (w <= 0.0f) return false;
        if (w >= 1.0f) return false;

        u = 1.0f - v - w;
        if (u <= 0.0f) return false;

        return true;
    }

    String ToString() {
        return Vector2D(p1X, p1Y).ToString() + " " + Vector2D(p2X, p2Y).ToString() + " " + Vector2D(p3X, p3Y).ToString();
    }
};
