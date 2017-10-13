#pragma once

#include "Intersection.h"
#include "Ray.h"
#include "Triangle.h"
#include "vector"


class BoxTreeNode {
public:
	BoxTreeNode();
	~BoxTreeNode();
	bool Intersect(const Ray &ray, Intersection &hit);
	void Construct(int count, Triangle **tri);

private:
	glm::vec3 BoxMin, BoxMax;
	BoxTreeNode *Child1, *Child2;
	const static int MaxTrianglesPerBox = 1;
	Triangle *Tri;
	int numTris;
};
