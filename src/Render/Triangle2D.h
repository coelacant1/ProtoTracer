#pragma once

#include "..\Materials\Material.h"
#include "..\Math\Transform.h"
#include "..\Math\Vector2D.h"
#include "Triangle3D.h"
#include "BoundingBox2D.h"

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
        float v2lX = x - p1X;
        float v2lY = y - p1Y;

        v = (v2lX * v1Y - v1X * v2lY) * denominator;
        if (v <= 0.0f) return false;
        if (v >= 1.0f) return false;

        w = (v0X * v2lY - v2lX * v0Y) * denominator;
        if (w <= 0.0f) return false;
        if (w >= 1.0f) return false;

        u = 1.0f - v - w;
        if (u <= 0.0f) return false;

        return true;
    }

    bool DidIntersect(BoundingBox2D& bbox) {
        Vector2D axes[] = { {1.0f, 0.0f}, {0.0f, 1.0f}, {-1.0f * (p2Y - p1Y), p2X - p1X},
                            {-1.0f * (p3Y - p1Y), p3X - p1X}, {-1.0f * (p3Y - p2Y), (p3Y - p2Y)} }; // axes for SAT-based intersection testing

        Vector2D c = (bbox.GetMinimum() + bbox.GetMaximum()) * 0.5f;
        Vector2D e = (bbox.GetMaximum() - bbox.GetMinimum()) * 0.5f;

        for (const Vector2D& axis : axes) {
            //project vertices and bbox onto axis, relative to bbox center
            float p0 = axis.X * (p1X - c.X) + axis.Y * (p1Y - c.Y);
            float p1 = axis.X * (p2X - c.X) + axis.Y * (p2Y - c.Y);
            float p2 = axis.X * (p3X - c.X) + axis.Y * (p3Y - c.Y);

            float r = e.X * fabsf(axis.X) + e.Y * fabsf(axis.Y);

            //if the projected ranges dont overlap then the axis is separating
            if (fmaxf(-1.0f * fmaxf(p0, fmaxf(p1, p2)), fminf(p0, fminf(p1, p2))) > r)
                return false;
        }

        return true;
    }

    String ToString() {
        return Vector2D(p1X, p1Y).ToString() + " " + Vector2D(p2X, p2Y).ToString() + " " + Vector2D(p3X, p3Y).ToString();
    }
};
