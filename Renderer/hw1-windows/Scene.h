/*
Class defining the Scene, which contains all objects and lights 
*/
#pragma once

#include "Object.h"
#include "Light.h"
#include <vector>
#include <iostream>
#include "Material.h"
#include "glm/ext.hpp"
#include <algorithm>


class Scene {
public:
	Scene();
	void AddObject(Object &obj);
	void AddLight(Light &lgt);
	void SetSkyColor(const Color sky);

	int GetNumLights();
	Light &GetLight(int i);
	Color GetSkyColor();

	bool Intersect(const Ray &ray, Intersection &hit);

	void findIntensity(Intersection &hit, const Ray& ray);
	void findShadow(Ray &ray, Intersection &hit);

private:
	std::vector<Object*> Objects;
	std::vector<Light*> Lights;
	Color SkyColor;
};

