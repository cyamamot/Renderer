/*
single node of bounding box tree spatial data structure to improve render performance
*/

#pragma once

#include "Intersection.h"
#include "Ray.h"
#include "Triangle.h"
#include "vector"


class BoxTreeNode {
public:
	//creates bounding box node
	BoxTreeNode();
	~BoxTreeNode();
	//determines whether a ray intersects this box
	bool Intersect(const Ray &ray, Intersection &hit);
	//constructs this box around specified triangles in mesh
	void Construct(int count, std::vector<Triangle>& tri);
	void ScaleBox(int count, std::vector<Triangle>& tri);
	//divide current bounding box along specified axis
	void DivideAlongX(const int count, double lengthX, std::vector<Triangle>& tri);
	void DivideAlongY(const int count, double lengthY, std::vector<Triangle>& tri);
	void DivideAlongZ(const int count, double lengthZ, std::vector<Triangle>& tri);

private:
	//sets bounds of box
	glm::vec3 BoxMin, BoxMax;
	//children of box (box tree is a recursive data structure)
	BoxTreeNode *Child1, *Child2;
	const static int MaxTrianglesPerBox = 1;
	//pointer to array of all triangles in box
	Triangle* Tri;
	//number of triangles in current box
	int numTris;
};
