#pragma once
#include "Object.h"

class MovingObject : public Object {
public:
	MovingObject() {}
	MovingObject(Object &obj) {
		Mtl = NULL;
		SetChild(obj);
	}
	//Tests for intersection with object in motion
	bool Intersect(const Ray &ray, Intersection &hit);
	void SetChild(Object &obj);
	//set initial and final positions of the child mesh
	void SetInitialFinalMatrix(glm::mat4x4 &init, glm::mat4x4 &fin);
	void setMaterial(Material*& mtl);

private:
	//start position of this matrix
	glm::mat4x4 initialMatrix;
	//end position of this matrix
	glm::mat4x4 finalMatrix;
	Object *Child;
	Material* Mtl;
};
