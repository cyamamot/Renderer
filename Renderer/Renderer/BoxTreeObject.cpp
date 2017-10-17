#include "BoxTreeObject.h"
#include <iostream>

BoxTreeObject::BoxTreeObject() {
	RootNode = new BoxTreeNode();
}

BoxTreeObject::~BoxTreeObject() {
	delete RootNode;
}

void BoxTreeObject::Construct(MeshObject& mesh) {
	std::vector<Triangle> triangles;
	for (int i = 0; i < mesh.returnNumTriangles(); i++) {
		triangles.push_back(mesh.Triangles[i]);
	}
	//construct nodes of total tree recursively
	RootNode->Construct(mesh.returnNumTriangles(), triangles);
}

bool BoxTreeObject::Intersect(const Ray& ray, Intersection& hit) {
	//determine intersection recursively
	return RootNode->Intersect(ray, hit);
}
