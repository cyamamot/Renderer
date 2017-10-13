////////////////////////////////////////
// Triangle.h
////////////////////////////////////////

#pragma once

#include "Vertex.h"
#include "Material.h"
#include "Ray.h"
#include "algorithm"

////////////////////////////////////////////////////////////////////////////////

class Triangle {
public:
	int index;

	glm::vec3 center;

	Triangle();

	bool Intersect(const Ray &ray, Intersection &hit) const;

	void Init(Vertex *v0, Vertex *v1, Vertex *v2, Material *m) {
		Vtx[0] = v0; Vtx[1] = v1; Vtx[2] = v2; Mtl = m;
		setCenter();
	}
	float area(glm::vec3 vec) const;

	Vertex* GetVtx(int vert);

	Material* GetMtl();

	void setCenter();

private:
	Vertex *Vtx[3];
	Material *Mtl;
};

////////////////////////////////////////////////////////////////////////////////
