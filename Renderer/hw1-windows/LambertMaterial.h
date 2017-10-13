////////////////////////////////////////
// LambertMaterial.h
////////////////////////////////////////

#pragma once

#include "Material.h"
#include <iostream>
#include "glm/glm.hpp"
#include <random>

////////////////////////////////////////////////////////////////////////////////

#define PI 3.14159265

class LambertMaterial:public Material {
public:

	LambertMaterial() {}
	void ComputeReflectance(Color &col, const glm::vec3 &in, const glm::vec3 &out, const Intersection &hit) {
		if (dot(out, hit.Normal) < 0) {
			col = Color(0, 0, 0);
			return;
		}
		Color temp = DiffuseColor;
		col.Multiply(temp);
		col.Scale(dot(out, hit.Normal));
	}
	void GenerateSample(const Intersection &isect, const glm::vec3 &inDir, glm::vec3 &outDir, Color &outColor) {
		std::random_device rand_dev;
		std::mt19937 generator(rand_dev());
		std::uniform_real_distribution<double> distribution(0.0, 1.0);
		double s = distribution(generator);
		double t = distribution(generator);
		double u = 2 * PI * s;
		double v = sqrt(1 - t);
		glm::vec3 temp = isect.Normal - glm::vec3(temp[0] - 1, temp[1] - 1, temp[2] - 1);
		glm::vec3 j = isect.Normal;
		glm::vec3 i = glm::cross(temp, j);
		glm::vec3 k = glm::cross(i, j);
		outDir = glm::normalize((v * cos(u) * i) + (sqrt(t) * j) + (v * sin(u) * k));
		outColor = DiffuseColor;

		////////////////////////////////////////////////////////////////////////////////////
		if (dot(outDir, isect.Normal) < 0) {
			outColor.Set(0, 0, 0);
			//outDir = glm::vec3(0, 0, 0);
		}
		////////////////////////////////////////////////////////////////////////////////////
	}
	void SetColor(Color col) {
		DiffuseColor = col;
	}

private:
	Color DiffuseColor;
};

////////////////////////////////////////////////////////////////////////////////
