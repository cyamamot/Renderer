#include "Triangle.h"
#include <iostream>

using namespace glm;

	Triangle::Triangle() {
	}

	float Triangle::area(vec3 vec) const {
		return sqrt((vec[0] * vec[0]) + (vec[1] * vec[1]) + (vec[2] * vec[2]));
	}

	bool Triangle::Intersect(const Ray &ray, Intersection &hit) const {
		float detM = dot(-ray.Direction, cross((Vtx[1]->Position - Vtx[0]->Position), (Vtx[2]->Position - Vtx[0]->Position)));
		if (detM == 0) return false;
		float t = dot((ray.Origin - Vtx[0]->Position), cross((Vtx[1]->Position - Vtx[0]->Position), (Vtx[2]->Position - Vtx[0]->Position))) / detM;
		double alpha = dot(-ray.Direction, cross((ray.Origin - Vtx[0]->Position), (Vtx[2]->Position - Vtx[0]->Position))) / detM;
		double beta = dot(-ray.Direction, cross((Vtx[1]->Position - Vtx[0]->Position), (ray.Origin - Vtx[0]->Position))) / detM;
		if (alpha >= 0 && beta >= 0 && alpha + beta < 1 && t > 0) {
			if (hit.type == "shadow") {
				hit.HitDistance = t;
				hit.hitIndex = index;
				hit.Position = ray.Origin + ray.Direction * t;
				return true;
			}
			if (hit.HitDistance > t) {
				hit.HitDistance = t;
				hit.Position = ray.Origin + ray.Direction * t;
				vec3 norm = Vtx[0]->Normal * (float)(1.0 - alpha - beta) + Vtx[1]->Normal * (float)alpha + Vtx[2]->Normal * (float)beta;
				hit.Normal = normalize(norm);
				if (dot(hit.Normal, ray.Direction) > 0) hit.Normal = -hit.Normal;
				hit.Mtl = Mtl;
				hit.hitIndex = index;
				hit.TangentU = glm::cross(glm::vec3(0, 1, 0), hit.Normal);
				if (glm::length(hit.TangentU) < 0.0001)
					hit.TangentU = glm::cross(glm::vec3(1, 0, 0), hit.Normal);
				hit.TangentU = glm::normalize(hit.TangentU);
				hit.TangentV = glm::cross(hit.Normal, hit.TangentU);
				return true;
			}
		}
		else return false;
	}

	Vertex* Triangle::GetVtx(int vert) {
		if (Vtx[vert] != NULL) return Vtx[vert];
	}

	Material* Triangle::GetMtl() {
		return Mtl;
	}

	void Triangle::setCenter() {
		center = (Vtx[0]->Position + Vtx[1]->Position + Vtx[2]->Position) / 3.0f;
	}

/////////////////////////////////////////////////////////////////////////////