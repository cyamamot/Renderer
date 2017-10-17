#include "MetalMaterial.h"

void MetalMaterial::ComputeReflectance(Color &col, const glm::vec3 &in, const glm::vec3 &out, const Intersection &hit) {
	//glm::vec3 temp = glm::normalize(glm::dot(-in, hit.Normal) * hit.Normal) - (2 * -in);
	//glm::vec3 temp = glm::normalize(glm::dot(out, hit.Normal) * hit.Normal) - (2 * out);
	glm::vec3 temp = glm::normalize((2.0 * dot(out, hit.Normal) * hit.Normal) - out);
	if ((-in[0] == temp[0]) && (-in[1] == temp[1]) && (-in[2] && temp[2])) {
		col = DiffuseColor;
	}
	else col = Color::BLACK;
}

void MetalMaterial::GenerateSample(const Intersection &isect, const glm::vec3 &inDir, glm::vec3 &outDir, Color &outColor) {
	outColor = DiffuseColor;
	outDir = glm::normalize((2 * (glm::dot(-inDir, isect.Normal)) * isect.Normal) - -inDir);
}
void MetalMaterial::SetColor(Color col) {
	DiffuseColor = col;
}