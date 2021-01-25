#pragma once
#pragma once

#include "Quaternion.h"
#include "Triangle3D.h"
#include "Vector2D.h"

class Triangle2D {
public:
	Vector2D p1;
	Vector2D p2;
	Vector2D p3;
  Vector2D v0;
  Vector2D v1;
	Vector3D normal;
  Vector3D* t3p1;
  Vector3D* t3e1;
  Vector3D* t3e2;

	Triangle2D() {
		p1 = Vector2D();
		p2 = Vector2D();
		p3 = Vector2D();
	}

	Triangle2D(Vector2D p1, Vector2D p2, Vector2D p3) {
		p1 = Vector2D(p1);
		p2 = Vector2D(p2);
		p3 = Vector2D(p3);

    v0 = p2 - p1;
    v1 = p3 - p1;
	}

	Triangle2D(Quaternion camQ, Vector3D camV, Triangle3D t) {
		camV.X = -camV.X;
		camV.Y = -camV.Y;
		p1 = camQ.UnrotateVector(Vector3D(*t.p1)) - camV;
		p2 = camQ.UnrotateVector(Vector3D(*t.p2)) - camV;
		p3 = camQ.UnrotateVector(Vector3D(*t.p3)) - camV;

		normal = t.Normal();
    
    t3p1 = t.p1;
    t3e1 = &t.edge1;
    t3e2 = &t.edge2;
    
    v0 = p2 - p1;
    v1 = p3 - p1;
	}

	void Translate(Vector2D p) {
		p1 = p1 + p;
		p2 = p2 + p;
		p3 = p3 + p;

    v0 = p2 - p1;
    v1 = p3 - p1;
	}

	bool DidIntersect(Vector2D ray, Vector3D* color) {
		Vector2D v2 = ray - p1;
		float den = v0.X * v1.Y - v1.X * v0.Y;
		float v = (v2.X * v1.Y - v1.X * v2.Y) / den;
		float w = (v0.X * v2.Y - v2.X * v0.Y) / den;
		float u = 1.0f - v - w;

		color->X = v;
		color->Y = w;
		color->Z = u;

		return u > 0 && v > 0 && w > 0;
	}

	String ToString() {
		return p1.ToString() + " " + p2.ToString() + " " + p3.ToString();
	}
};
