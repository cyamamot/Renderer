#pragma once

#include "Light.h"

using namespace glm;

class DirectLight : public Light {
public:
	DirectLight() {}
	float Illuminate(const vec3 &pos, Color &col, vec3 &toLight, vec3 &ltPos) {
		toLight = normalize(-Direction);
		toLight = (-Direction);
		col = BaseColor;
		ltPos = pos - (Direction * 1000000.0f); 
		return Intensity;
	}
	void SetDirection(vec3 &dir) { Direction = normalize(dir); }
	void SetBaseColor(Color col);
	void SetIntensity(float intensity);

	vec3 getDirection(const glm::vec3& start) {
		return normalize(-Direction);
	}

private:
	vec3 Direction;
};