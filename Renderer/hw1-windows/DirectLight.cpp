#include "DirectLight.h"

using namespace glm;


	void DirectLight::SetBaseColor(Color col) {
		BaseColor = col;
	}
	void DirectLight::SetIntensity(float intensity) {
		Intensity = intensity;
	}
