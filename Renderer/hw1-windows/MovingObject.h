#pragma once
#include "Object.h"

class MovingObject : public Object {
public:
	MovingObject() {}
	MovingObject(Object &obj) {
		Mtl = NULL;
		SetChild(obj);
	}
	bool Intersect(const Ray &ray, Intersection &hit);
	void SetChild(Object &obj);
	void SetInitialFinalMatrix(glm::mat4x4 &init, glm::mat4x4 &fin);
	void setMaterial(Material*& mtl);

private:
	glm::mat4x4 initialMatrix;
	glm::mat4x4 finalMatrix;
	Object *Child;
	Material* Mtl;
};
