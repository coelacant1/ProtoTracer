#pragma once

#include "Object3D.h"
#include "Light.h"

//contains an array of objects containing triangles
//contains an array of lights

typedef struct Scene {
public:
	Object3D** objects;
	Light* lights;
	int numObjects;
	int numLights;

	Scene(Object3D** objects, Light* lights, int numObjects, int numLights) {
		this->objects = objects;
		this->lights = lights;
		this->numObjects = numObjects;
		this->numLights = numLights;
	}

} Scene;
