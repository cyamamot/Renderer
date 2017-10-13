#pragma once
#include "Vertex.h"
#include "Material.h"
#include "Ray.h"
#include "algorithm"
#include "Object.h"

class Sphere : public Object {
public:
	Sphere(float x, float y, float z, float rad, Material* m = 0);
	~Sphere() {
		delete Mtl;
	}
	bool Intersect(const Ray &ray, Intersection &hit);
	int index;
	void setMaterial(Material& mtl) {
		Mtl = &mtl;
	}

private:
	glm::vec3 center;
	float radius;

	Material* Mtl;
};

