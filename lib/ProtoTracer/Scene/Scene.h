#pragma once

#include "Screenspace\Effect.h"
#include "Objects\Object3D.h"

class Scene {
private:
	const int maxObjects;
	Object3D** objects;
	unsigned int numObjects = 0;
    Effect* effect;
    bool doesUseEffect = false;

	void RemoveElement(unsigned int element);

public:
	Scene(unsigned int maxObjects);
	~Scene();

    bool UseEffect();
	void EnableEffect();
	void DisableEffect();
    
    Effect* GetEffect();
	void SetEffect(Effect* effect);

	void AddObject(Object3D* object);
	void RemoveObject(unsigned int i);
	void RemoveObject(Object3D* object);

	Object3D** GetObjects();
	uint8_t GetObjectCount();
};
