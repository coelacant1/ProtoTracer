#pragma once

#include "Mathematics.h"
#include "Vector3D.h"

class Plane {
public:
	Vector3D Centroid;
	Vector3D Normal;

	Plane() {}

	Plane(Vector3D centroid, Vector3D normal) {
        this->Centroid = centroid;
        this->Normal = normal;
    }

	String ToString() {
		String centroid = Centroid.ToString();
		String normal = Normal.ToString();

		return "[ " + centroid + ", " + normal + " ]";
	}

};
