/*
Class that defines a single instance of a MeshObject
*/

#pragma once

#include "Object.h"

class InstanceObject : public Object {
public:
	InstanceObject() {}
	InstanceObject(Object &obj);
	//determines if given ray intersects the instance and sets hit if it does
	bool Intersect(const Ray &ray, Intersection &hit);
	//set MeshObject of instance
	void SetChild(Object &obj);
	//set matrix which transforms MeshObject child into the given instance
	void SetMatrix(glm::mat4x4 &mtx);
	//set material of this insatnce
	void setMaterial(Material*& mtl);

private:
	//Transformation matrix
	glm::mat4x4 Matrix;
	//Precalculated inverse transform of Matrix
	glm::mat4x4 Inverse; 
	Object *Child;
	Material* Mtl;
};
