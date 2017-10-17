#pragma once

#include "Object.h"
#include "MeshObject.h"
#include "BoxTreeNode.h"

class BoxTreeObject : public Object
{
public:
	BoxTreeObject();
	~BoxTreeObject();
	//constructs full box tree from individual nodes 
	void Construct(MeshObject &mesh);
	//determines where in the tree, if ever, the ray intersects
	bool Intersect(const Ray &ray, Intersection &hit);

private:
	BoxTreeNode *RootNode;
};
