/*
Subclass of Light class which defines a DirectLight (infinitely far away)
*/

#pragma once

#include "Light.h"

using namespace glm;

class DirectLight : public Light {
public:
	DirectLight() {}
	//calculates amount of light that hits pos, sets col of light, direction to light, and the light's position
	float Illuminate(const vec3 &pos, Color &col, vec3 &toLight, vec3 &ltPos);
	//Set direction of light
	void SetDirection(vec3 &dir);
	//Set color of light
	void SetBaseColor(Color col);
	//Set intensity of light
	void SetIntensity(float intensity);
	//get direction of light (opposite of direction)
	vec3 getDirection(const glm::vec3& start);

private:
	vec3 Direction;
};