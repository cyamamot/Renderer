#pragma once

#include "Light.h"
#include <iostream>

using namespace glm;

class PointLight : public Light {

public:
	PointLight() {}
	void SetBaseColor(Color col);
	void SetIntensity(float intensity);
	float Illuminate(const glm::vec3 &pos, Color &col, glm::vec3 &toLight, glm::vec3 &ltPos) {
		toLight = Position - pos;
		toLight = glm::normalize(toLight);
		float bright = Intensity / (length(toLight) * length(toLight)); 
		col = BaseColor;
		ltPos = Position;
		return bright;
	}
	void SetPosition(vec3 pos) {
		Position = pos;
	}
	vec3 getDirection(const glm::vec3& start) {
		return normalize(Position - start);
	}

private:
	vec3 Position;
};