////////////////////////////////////////
// Intersection.h
////////////////////////////////////////

#pragma once

#include "Color.h"
#include "glm/glm.hpp"
#include <vector>
class Material;

////////////////////////////////////////////////////////////////////////////////

class Intersection {
public:
	Intersection() { HitDistance = 1e10; Mtl = 0; hitIndex = -1; skipLight = std::vector<int>(0); }

public:
	// Ray intersection data
	float HitDistance;
	glm::vec3 Position;
	glm::vec3 Normal;
	Material *Mtl;
	int hitIndex;
	std::string type;
	std::vector<int> skipLight;
	glm::vec3 TangentU;
	glm::vec3 TangentV;

	// Shaded color
	Color Shade;
};

////////////////////////////////////////////////////////////////////////////////
