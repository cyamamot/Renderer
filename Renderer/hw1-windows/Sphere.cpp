#include "Sphere.h"
#include <algorithm>    // std::min
#include "LambertMaterial.h"



Sphere::Sphere(float x, float y, float z, float rad, Material* m) {
	center = glm::vec3(x, y, z);
	radius = rad;
	if(m == 0) Mtl = new LambertMaterial;
}
bool Sphere::Intersect(const Ray &ray, Intersection &hit) {
	float a = glm::dot(ray.Direction, ray.Direction);
	float b = 2 * dot(ray.Direction, ray.Origin - center);
	float c = glm::dot(ray.Origin - center, ray.Origin - center) - (radius * radius);
	float discriminant = (b * b) - (4 * a * c);
	if (discriminant < 0) {
		return false;
	}
	float d1 = (-b - sqrt(discriminant)) / (2 * a);
	float d2 = (-b + sqrt(discriminant)) / (2 * a);
	if (d1 < 0 && d2 > 0) {
		if (d2 > hit.HitDistance) return false;
		glm::vec3 point = ray.Origin + (ray.Direction * d2);
		hit.Position = point;
		hit.HitDistance = d2;
	}
	else if (d2 < 0 && d1 > 0) {
		if (d1 > hit.HitDistance) return false;
		glm::vec3 point = ray.Origin + (ray.Direction * d1);
		hit.Position = point;
		hit.HitDistance = d1;
	}
	else if (d1 == d2) {
		if (d2 > hit.HitDistance) return false;
		glm::vec3 point = ray.Origin + (ray.Direction * d2);
		hit.Position = point;
		hit.HitDistance = d2;
	}
	else {
		if (std::min(d1, d2) > hit.HitDistance) return false;
		glm::vec3 point = ray.Origin + (ray.Direction * std::min(d1, d2));
		hit.Position = point;
		hit.HitDistance = std::min(d1, d2);
	}
	hit.Mtl = Mtl;
	hit.Normal = (hit.Position - center) / radius;
	hit.hitIndex = index;
	//std::cout << "   shadow here : " << hit.hitIndex << ", " << hit.HitDistance << std::endl << std::flush;
	return true;
}