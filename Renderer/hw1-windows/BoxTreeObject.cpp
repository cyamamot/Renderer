#include "BoxTreeObject.h"
#include <iostream>

BoxTreeObject::BoxTreeObject() {
	RootNode = new BoxTreeNode();
}
BoxTreeObject::~BoxTreeObject() {
	delete RootNode;
}
void BoxTreeObject::Construct(MeshObject &mesh) {
	RootNode->Construct(mesh.returnNumTriangles(), &(mesh.Triangles));
}
bool BoxTreeObject::Intersect(const Ray &ray, Intersection &hit) {
	return RootNode->Intersect(ray, hit);
}
