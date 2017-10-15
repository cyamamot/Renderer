/*
Class defining Metal Material subclass of Material class
*/

#pragma once

#include "Material.h"
#include <iostream>
#include "glm/glm.hpp"

class MetalMaterial : public Material {

public:
MetalMaterial() {}
void ComputeReflectance(Color &col, const glm::vec3 &in, const glm::vec3 &out, const Intersection &hit);
void GenerateSample(const Intersection &isect, const glm::vec3 &inDir, glm::vec3 &outDir, Color &outColor);
void SetColor(Color col);

private:
	Color DiffuseColor;
};