#include "RayTrace.h"
#include "glm/ext.hpp"

RayTrace::RayTrace(Scene& scn) {
	Scn = &scn;
	MaxDepth = 10;
}

bool RayTrace::TraceRay(const Ray &ray, Intersection &hit, int depth) {
	hit.Shade = Color::BLACK;
	bool intersected = Scn->Intersect(ray, hit);
	if (intersected == false) {
		hit.Shade = Scn->GetSkyColor();
		return false;
	}
	Ray shadow;
	shadow.time = ray.time;
	Scn->findShadow(shadow, hit);
	Scn->findIntensity(hit, ray);
	if (depth >= MaxDepth) {
		return true;
	}
	Color outColor;
	Ray newRay;
	newRay.Origin = hit.Position + (0.00025f * hit.Normal);
	newRay.time = ray.time;
	Intersection newHit;
	hit.Mtl->GenerateSample(hit, ray.Direction, newRay.Direction, outColor);
	TraceRay(newRay, newHit, depth + 1);
	newHit.Shade.Multiply(outColor);
	hit.Shade.Add(newHit.Shade);
	return true;
}

void RayTrace::turnOffPath() {
	MaxDepth = 0;
}