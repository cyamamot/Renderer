//http://www.cs.utah.edu/~michael/brdfs/jgtbrdf.pdf

#pragma once
#include "Material.h"
#include <iostream>
#include "glm/glm.hpp"
#include <algorithm>

#define PI 3.14159265


class AshikhminMaterial : public Material {
public:
	AshikhminMaterial() {
		nu = 1;
		nv = 1;
	}
	void ComputeReflectance(Color &col, const glm::vec3 &in, const glm::vec3 &out, const Intersection &hit) {
		if (dot(out, hit.Normal) < 0) {
			col = Color(0, 0, 0);
			return;
		}
		glm::vec3 k1 = normalize(out);
		glm::vec3 k2 = normalize(-in);
		glm::vec3 u = normalize(hit.TangentU);
		glm::vec3 v = normalize(hit.TangentV);
		glm::vec3 n = normalize(hit.Normal);
		glm::vec3 h = normalize((k1 + k2));
		double temps1 = sqrt((nu + 1.0) * (nv + 1.0)) / (8 * PI);
		double F = Rs + ((1.0 - Rs) * (pow(1.0 - dot(k1, h), 5)));
		double expTemp = ((nu * dot(h, u) * dot(h, u)) + (nv * dot(h, v) * dot(h, v))) / (1.0 - (dot(h, n) * dot(h, n)));
		double temps2 = pow(dot(h, n), expTemp) / (dot(h, k1) * std::max(dot(n, k1), dot(n, k2)));
		float ps = temps1 * temps2 * F;
		double tempd3 = (1.0 - pow(1.0 - (dot(n, k2) / 2.0f), 5));
		double tempd2 = (1.0 - pow(1.0 - (dot(n, k1) / 2.0f), 5));
		float pd = (28.0 / (12.0 * PI)) * Rd * (1.0 - Rs) * tempd3 * tempd2;
		Color finalColor;
		Color RsTemp = specularLevel;
		Color RdTemp = diffuseLevel;
		RsTemp.Scale(ps);
		RdTemp.Scale(pd);
		finalColor.Set(0, 0, 0);
		finalColor.Add(RsTemp);
		finalColor.Add(RdTemp);
		col.Multiply(finalColor);
	}
	void GenerateSample(const Intersection &isect, const glm::vec3 &inDir, glm::vec3 &outDir, Color &outColor) {
		std::random_device rand_dev;
		std::mt19937 generator(rand_dev());
		std::uniform_real_distribution<double> distribution(0.0, 1.0);
		double random = distribution(generator);
		Color diffColor, specColor;
		vec3 diffuseRay, specularRay;
		GenerateDiffuseSample(isect, inDir, diffuseRay, diffColor);
		GenerateSpecularSample(isect, inDir, specularRay, specColor);
		outColor = diffColor;
		outColor.Add(specColor);
		if (random <= Rd) {
			outDir = diffuseRay;
			outColor = diffColor;
		}
		else {
			outDir = specularRay;
			outColor = specColor;
		}

	}
	void GenerateDiffuseSample(const Intersection &isect, const glm::vec3 &inDir, glm::vec3 &outDir, Color &outColor) {
		LambertMaterial tempMtl;
		tempMtl.GenerateSample(isect, inDir, outDir, outColor);
		Color diffTemp = diffuseLevel;
		diffTemp.Scale(Rd);
		outColor = diffTemp;
	}
	void GenerateSpecularSample(const Intersection &isect, const glm::vec3 &inDir, glm::vec3 &outDir, Color &outColor) {
		std::random_device rand_dev;
		std::mt19937 generator(rand_dev());
		std::uniform_real_distribution<double> distribution(0.0, 1.0); 
		double random1 = distribution(generator);
		double random2 = distribution(generator);
		float phi = Phi(random1);
		float cosTheta = pow((1.0 - random2), 1.0 / ((nu * cos(phi) * cos(phi)) + (nv * sin(phi) * sin(phi)) + 1.0));
		float sinTheta = sqrt(1.0 - cosTheta);
		vec3 a = normalize(isect.Normal);
		vec3 b = normalize(isect.TangentU);
		vec3 c = normalize(isect.TangentV);
		vec3 h = normalize((sinTheta * cos(phi) * b) + (sinTheta * sin(phi) * c) + (cosTheta * a));
		outDir = normalize((2.0 * dot(h, -inDir) * h) - -inDir);
		Color specTemp = specularLevel;
		specTemp.Scale(Rs);
		outColor = specTemp;
		if (dot(outDir, isect.Normal) < 0) {
			outColor.Set(0, 0, 0);
			//outDir = vec3(0, 0, 0);
		}
	}
	float Phi(float E1) {
		float phi;
		if (E1 >= 0 && E1 < 0.25) {
			E1 = (1.0 - (4.0 * (0.25 - E1)));
			phi = atan(sqrt((nu + 1.0) / (nv + 1.0)) * tan(PI * E1 / 2.0));
		}
		else if (E1 >= 0.25 && E1 < 0.5) {
			E1 = (1.0 - (4.0 * (0.5 - E1)));
			phi = PI - atan(sqrt((nu + 1.0) / (nv + 1.0)) * tan(PI * E1 / 2.0));
		}
		else if (E1 >= 0.5 && E1 < 0.75) {
			E1 = (1.0 - (4.0 * (0.75 - E1)));
			phi = -PI + atan(sqrt((nu + 1.0) / (nv + 1.0)) * tan(PI * E1 / 2.0));
		}
		else if (E1 >= 0.75 && E1 <= 1.0) {
			E1 = (1.0 - (4.0 * (1.0 - E1)));
			phi = (2.0 * PI) - atan(sqrt((nu + 1.0) / (nv + 1.0)) * tan(PI * E1 / 2.0));
		}
		return phi;
	}
	void SetSpecularLevel(float level) {
		Rs = level;
	}
	void SetDiffuseLevel(float level) {
		Rd = level;
	}
	void SetDiffuseColor(Color col) {
		glm::vec3 values = col.getValues();
		diffuseLevel.Set(values[0], values[1], values[2]);
	}
	void SetSpecularColor(Color col) {
		glm::vec3 values = col.getValues();
		specularLevel.Set(values[0], values[1], values[2]);
	}
	void SetRoughness(float u, float v) {
		nu = u;
		nv = v;
	}

private:
	Color specularLevel, diffuseLevel;
	float Rd, Rs;
	float nu, nv;
};
