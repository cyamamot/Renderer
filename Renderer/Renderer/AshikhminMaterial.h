//http://www.cs.utah.edu/~michael/brdfs/jgtbrdf.pdf
/*
Ashikhmin Material as specified in the paper above
*/
#pragma once
#include "Material.h"
#include "LambertMaterial.h"
#include <iostream>
#include "glm/glm.hpp"
#include <algorithm>

typedef glm::vec3 vec3;

class AshikhminMaterial : public Material 
{
private:
	//Specular and Diffuse colors
	Color specularLevel, diffuseLevel; 
	//specular and diffuse levels
	float Rd, Rs; 
	//components of roughness for material
	float nu, nv;

public:
	AshikhminMaterial() 
	{
		nu = 1;
		nv = 1;
	}
	//computes color reflected off of material
	void ComputeReflectance(Color &col, const glm::vec3 &in, const glm::vec3 &out, const Intersection &hit);
	//generates ray reflected off of material
	void GenerateSample(const Intersection &isect, const glm::vec3 &inDir, glm::vec3 &outDir, Color &outColor);
	//generates diffuse portion of sample reflected off material
	void GenerateDiffuseSample(const Intersection &isect, const glm::vec3 &inDir, glm::vec3 &outDir, Color &outColor);
	//generates speculare portion of sample reflected off material
	void GenerateSpecularSample(const Intersection &isect, const glm::vec3 &inDir, glm::vec3 &outDir, Color &outColor);
	//generates Phi variable as specified in paper (link at top of page)
	float Phi(float E1);
	void SetSpecularLevel(float level);
	void SetDiffuseLevel(float level);
	void SetDiffuseColor(Color col);
	void SetSpecularColor(Color col);
	void SetRoughness(float u, float v);
};
