#include "PointLight.h"

using namespace glm;

	void PointLight::SetBaseColor(Color col) {
		BaseColor = col;
	}
	void PointLight::SetIntensity(float intensity) {
		Intensity = intensity;
	}
