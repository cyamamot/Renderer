#pragma once
#include "Object.h"

class InstanceObject : public Object {

public:
	InstanceObject() {}
	InstanceObject(Object &obj) {
		Mtl = NULL;
		SetChild(obj);
	}
	bool Intersect(const Ray &ray, Intersection &hit);
	void SetChild(Object &obj);
	void SetMatrix(glm::mat4x4 &mtx);
	void setMaterial(Material*& mtl);

private:
	glm::mat4x4 Matrix;
	glm::mat4x4 Inverse; 
	Object *Child;
	Material* Mtl;
};
