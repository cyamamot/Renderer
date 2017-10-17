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
	//determines whether the hit point is in the shadow of anything else
	Scn->findShadow(shadow, hit);
	Scn->findIntensity(hit, ray);
	if (depth >= MaxDepth) {
		return true;
	}
	Color outColor;
	Ray newRay;
	//spawns new ray based on initial ray and the object
	newRay.Origin = hit.Position + (0.00025f * hit.Normal);
	newRay.time = ray.time;
	Intersection newHit;
	hit.Mtl->GenerateSample(hit, ray.Direction, newRay.Direction, outColor);
	//Traces the ray created from the reflection of the initial ray off the object
	TraceRay(newRay, newHit, depth + 1);
	newHit.Shade.Multiply(outColor);
	//returns final color returned by full path raytracing including shadows
	hit.Shade.Add(newHit.Shade);
	return true;
}

void RayTrace::turnOffPath() {
	MaxDepth = 0;
}