/*
Class defining Lambert Material subclass of Material class
*/

#pragma once

#include "Material.h"
#include <iostream>
#include "glm/glm.hpp"
#include <random>

#define PI 3.14159265

class LambertMaterial:public Material {
public:
LambertMaterial() {}
//Compute color reflected off material
void ComputeReflectance(Color &col, const glm::vec3 &in, const glm::vec3 &out, const Intersection &hit);
//Generate reflected ray based on incoming ray
void GenerateSample(const Intersection &isect, const glm::vec3 &inDir, glm::vec3 &outDir, Color &outColor);
void SetColor(Color col);

private:
Color DiffuseColor;
};

