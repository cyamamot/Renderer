#pragma once
#include "Vertex.h"
#include "Material.h"
#include "Ray.h"
#include "algorithm"
#include "LambertMaterial.h"
#include "Object.h"
#include "glm/glm.hpp"
#include "glm/ext.hpp"

class Plane : public Object {
public:
	Plane(glm::vec3 d, glm::vec3 norm, Material *m = 0) {
		distance = glm::dot(norm, d);
		normal = norm;
		if (m == 0) Mtl = new LambertMaterial;
	}
	~Plane() { 
		delete Mtl; 
	}
	bool Intersect(const Ray &ray, Intersection &hit);
	int index;
	void setMaterial(Material*& mtl) {
		Mtl = mtl;
	}

private:
	float distance;
	glm::vec3 normal;
	Material* Mtl;
};