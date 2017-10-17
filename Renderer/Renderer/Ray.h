/*
Class defining Ray cast by the Raytracer
*/
#pragma once

#include "glm/glm.hpp"
#include <random>


class Ray 
{
public:
	glm::vec3 Origin;
	glm::vec3 Direction;
	//randomly sets the time the ray was fired (only applies for objects in motion)
	float time;

	void setTime();
};
