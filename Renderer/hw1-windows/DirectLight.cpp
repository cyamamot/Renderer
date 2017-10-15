#include "DirectLight.h"

using namespace glm;

float DirectLight::Illuminate(const vec3 &pos, Color &col, vec3 &toLight, vec3 &ltPos){
	toLight = normalize(-Direction);
	toLight = (-Direction);
	col = BaseColor;
	//light's position is infinitely far away
	ltPos = pos - (Direction * 1000000.0f);
	return Intensity;
}

void DirectLight::SetDirection(vec3 &dir) {
	Direction = normalize(dir);
}

void DirectLight::SetBaseColor(Color col) {
	BaseColor = col;
}

void DirectLight::SetIntensity(float intensity) {
	Intensity = intensity;
}

vec3 DirectLight::getDirection(const glm::vec3& start) {
	return normalize(-Direction);
}
