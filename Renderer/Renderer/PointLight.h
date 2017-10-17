/*
Class defining Pointlight subclass of Light class
*/
#pragma once

#include "Light.h"
#include <iostream>

using namespace glm;

class PointLight : public Light {

public:
	PointLight() {}
	void SetBaseColor(Color col);
	void SetIntensity(float intensity);
	//returns distance to light, the color of the light, and the light position
	float Illuminate(const glm::vec3 &pos, Color &col, glm::vec3 &toLight, glm::vec3 &ltPos);
	void SetPosition(vec3 pos);
	vec3 getDirection(const glm::vec3& start);

private:
	vec3 Position;
};