#include "Scene.h"

Scene::Scene(unsigned int maxObjects) : maxObjects(maxObjects) {
	objects = new Object3D*[maxObjects];
}

Scene::~Scene() {
	delete[] objects;
}

bool Scene::UseEffect() {
	return doesUseEffect;
}

void Scene::EnableEffect() {
	doesUseEffect = true;
}

void Scene::DisableEffect() {
	doesUseEffect = false;
}

Effect* Scene::GetEffect() {
	return effect;
}

void Scene::SetEffect(Effect* effect) {
	this->effect = effect;
}

void Scene::AddObject(Object3D* object) {
	objects[numObjects] = object;
	numObjects++;
}

void Scene::RemoveElement(unsigned int element) {
	for (unsigned int i = element; i < numObjects - 1; i++) {
		objects[i] = objects[i + 1];
	}
}

void Scene::RemoveObject(unsigned int i) {
	if (i < numObjects && i >= 0) {
		RemoveElement(i);
		numObjects--;
	}
}

void Scene::RemoveObject(Object3D* object) {
	for (unsigned int i = 0; i < numObjects; i++) {
		if (objects[i] == object) {
			RemoveElement(i);
			break;
		}
	}
}

Object3D** Scene::GetObjects() {
	return objects;
}

uint8_t Scene::GetObjectCount() {
	return numObjects;
}
