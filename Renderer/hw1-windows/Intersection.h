
#pragma once

#include "Color.h"
#include "glm/glm.hpp"
#include <vector>

class Material;

class Intersection {
public:
	Intersection();

public:
	// Ray intersection data
	float HitDistance;
	//Location of hit
	glm::vec3 Position;
	//normal at hit
	glm::vec3 Normal;
	Material *Mtl;
	//index of triangle hit
	int hitIndex;
	//type of hit (shadow vs raycasted intersection)
	std::string type;
	//vector of lights to skip when calculating lighting (if light is within mesh, etc...)
	std::vector<int> skipLight;
	glm::vec3 TangentU;
	glm::vec3 TangentV;

	// Shaded color
	Color Shade;
};


