#pragma once

#include "Object3D.h"

typedef struct Scene {
public:
	Object3D** objects;
	int numObjects;

	Scene(Object3D** objects, int numObjects){
		this->objects = objects;
		this->numObjects = numObjects;
	}

} Scene;
