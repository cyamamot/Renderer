/*
Class defining Raytrace function responsible for spawning rays and using their information to create final values
*/
#pragma once
#include "Scene.h"
#include "glm/glm.hpp"

class RayTrace {
public:
	RayTrace(Scene &s);
	bool TraceRay(const Ray &ray, Intersection &hit, int depth = 1);
	void turnOffPath();

private:
	Scene *Scn;
	// Settings
	int MaxDepth;
	// Statistics
	int PrimaryRays;
	int SecondaryRays;
	int ShadowRays;
};