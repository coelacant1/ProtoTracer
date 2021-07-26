#pragma once

#include "Object3D.h"
#include "Light.h"

//contains an array of objects containing triangles
//contains an array of lights

typedef struct Scene {
private:
	bool noLights = false;
	Light light;

public:
	Object3D** objects;
	Light* lights;
	int numObjects;
	int numLights;

	Scene(Object3D** objects, int numObjects){
		this->objects = objects;
		this->numObjects = numObjects;
		noLights = true;

		numLights = 1;
		lights = new Light[1];

		lights[0].Set(Vector3D(1000, 0, 0), Vector3D(255, 255, 255), 1000.0f, 0.75f, 0.25f);
	}

	Scene(Object3D** objects, Light* lights, int numObjects, int numLights) {
		this->objects = objects;
		this->lights = lights;
		this->numObjects = numObjects;
		this->numLights = numLights;
	}

	~Scene(){
		if(noLights){
			delete lights;
		}
	}

} Scene;
