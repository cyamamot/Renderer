#include "InstanceObject.h"
#include <iostream>

	bool InstanceObject::Intersect(const Ray &ray, Intersection &hit) {
		Ray ray2;
		ray2.Origin = glm::vec3(Inverse * glm::vec4(ray.Origin, 1));
		ray2.Direction = glm::vec3(Inverse * glm::vec4(ray.Direction, 0));
		if (Child->Intersect(ray2, hit) == false) {
			return false;
		}
		hit.Position = glm::vec3(Matrix * glm::vec4(hit.Position, 1));
		hit.Normal = glm::vec3(Matrix * glm::vec4(hit.Normal, 0));
		hit.HitDistance = glm::distance(ray.Origin, hit.Position); 
		if (Mtl != NULL) hit.Mtl = Mtl;
		return true;
	}
	void InstanceObject::SetChild(Object &obj) {
		Child = &obj;
	}
	void InstanceObject::SetMatrix(glm::mat4x4 &mtx) {
		Matrix = mtx;
		Inverse = inverse(Matrix);
	}
	void InstanceObject::setMaterial(Material*& mtl) {
		Mtl = mtl;
	}

