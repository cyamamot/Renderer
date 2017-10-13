#include "Plane.h"


bool Plane::Intersect(const Ray &ray, Intersection &hit) {
	/*float denom = glm::dot(ray.Direction, normal);
	if (denom < 0) return false;
	float t = (distance - glm::dot(ray.Origin, normal)) / denom;
	if (t < 0) return false;
	hit.HitDistance = t;
	hit.Position = ray.Origin + (ray.Direction * t);
	hit.Normal = normal;
	hit.Mtl = mtl;*/

	float denom = glm::dot(ray.Direction, normal);
	if (denom == 0) return false;
	float t = (distance - glm::dot(ray.Origin, normal))/ denom;
	if (t < 0) return false;
	if (t > hit.HitDistance) return false;
	hit.HitDistance = t;
	hit.Position = ray.Origin + (ray.Direction * t);
	hit.Normal = normal;
	hit.Mtl = Mtl;
	hit.hitIndex = index;

	//std::cout << glm::to_string(ray.Origin) << " + " << glm::to_string(ray.Direction) << " = " << 
		//glm::to_string(hit.Position) << "   " << glm::to_string(hit.Normal) << "   " << hit.HitDistance << std::endl;

	return true;
}