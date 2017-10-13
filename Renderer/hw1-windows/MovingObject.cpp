#include "MovingObject.h"

bool MovingObject::Intersect(const Ray &ray, Intersection &hit) {
	Ray ray2;
	glm::mat4x4 Matrix = interpolate(initialMatrix, finalMatrix, ray.time);
	glm::mat4x4 Inverse = inverse(Matrix);
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
void MovingObject::SetChild(Object &obj) {
	Child = &obj;
}
void MovingObject::SetInitialFinalMatrix(glm::mat4x4 &init, glm::mat4x4 &fin) {
	initialMatrix = init;
	finalMatrix = fin;
}
void MovingObject::setMaterial(Material*& mtl) {
	Mtl = mtl;
}