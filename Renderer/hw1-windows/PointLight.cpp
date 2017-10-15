#include "PointLight.h"

using namespace glm;

void PointLight::SetBaseColor(Color col) {
	BaseColor = col;
}

void PointLight::SetIntensity(float intensity) {
	Intensity = intensity;
}

float PointLight::Illuminate(const glm::vec3 &pos, Color &col, glm::vec3 &toLight, glm::vec3 &ltPos) {
	toLight = Position - pos;
	toLight = glm::normalize(toLight);
	float bright = Intensity / (length(toLight) * length(toLight));
	col = BaseColor;
	ltPos = Position;
	return bright;
}

void PointLight::SetPosition(vec3 pos) {
	Position = pos;
}

vec3 PointLight::getDirection(const glm::vec3& start) {
	return normalize(Position - start);
}
