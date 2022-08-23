#pragma once

#include "Object3D.h"

class Scene {
private:
	const int maxObjects;
	Object3D** objects;
	unsigned int numObjects = 0;

	void RemoveElement(unsigned int element){
		for(unsigned int i = element; i < numObjects; i++){
            objects[i] = objects[i + 1];
        }
	}

public:
	Scene(unsigned int maxObjects) : maxObjects(maxObjects) {
		objects = new Object3D*[maxObjects];
	}

	~Scene(){
		delete[] objects;
	}

	void AddObject(Object3D* object){
		objects[numObjects] = object;

		numObjects++;
	}

	void RemoveObject(unsigned int i){
		if (i <= numObjects && i > 0){
			RemoveElement(i);

			numObjects--;
		}
	}

	void RemoveObject(Object3D* object){
		//check if pointers are equal for all objects, if so delete and shift array
		for(unsigned int i = 0; i < numObjects; i++){
			if(objects[i] == object){
				RemoveElement(i);
				break;
			}
		}
	}

	Object3D** GetObjects(){
		return objects;
	}

	uint8_t GetObjectCount(){
		return numObjects;
	}

};
