#pragma once

#include "Object.h"
#include "Light.h"
#include <vector>
#include <iostream>
#include "Material.h"
#include "glm/ext.hpp"
#include <algorithm>


class Scene {
public:
	Scene()										{SkyColor.Set(0.2f,0.2f,0.5f);}

	void AddObject(Object &obj)					{Objects.push_back(&obj);}
	void AddLight(Light &lgt)					{Lights.push_back(&lgt);}
	void SetSkyColor(const Color sky)			{SkyColor=sky;}

	int GetNumLights()							{return Lights.size();}
	Light &GetLight(int i)						{return *Lights[i];}
	Color GetSkyColor()							{return SkyColor;}

	bool Intersect(const Ray &ray,Intersection &hit) {
		bool success=false;
		for(unsigned int i=0;i<Objects.size();i++)
			if (Objects[i]->Intersect(ray, hit)) {
				if (hit.type == "shadow") {
					return true;
				}
				success = true;
			}
		return success;
	}

	void findIntensity(Intersection &hit, const Ray& ray) {
		float intensity;
		Color color;
		glm::vec3 toLight;
		glm::vec3 ltPos;
		if (hit.skipLight.size() == Lights.size()) return;
		for (unsigned int i = 0; i < Lights.size(); i++) {
			if (std::find(hit.skipLight.begin(), hit.skipLight.end(), i) == hit.skipLight.end()) {
				intensity = Lights[i]->Illuminate(hit.Position, color, toLight, ltPos);
				hit.Mtl->ComputeReflectance(color, ray.Direction, toLight, hit);
				color.Scale(intensity);
				hit.Shade.Add(color);
			}
		}
	}
	void findShadow(Ray &ray, Intersection &hit) {
		for (int i = 0; i < Lights.size(); i++) {
			ray.Origin = hit.Position + (0.00025f * hit.Normal);
			ray.Direction = Lights[i]->getDirection(hit.Position);
			Intersection shadeHit;
			shadeHit.type = "shadow";
			Intersect(ray, shadeHit);
			Color color;
			glm::vec3 toLight;
			glm::vec3 ltPos;
			glm::vec3 out;
			Lights[i]->Illuminate(hit.Position, color, toLight, ltPos);
			if (shadeHit.hitIndex == -1 || glm::distance(shadeHit.Position, hit.Position) > glm::distance(ltPos, hit.Position)) {
				continue;
			}
			if (shadeHit.hitIndex != -1 && shadeHit.HitDistance > 0.001 && shadeHit.hitIndex != hit.hitIndex) {		
				hit.skipLight.push_back(i);
			}
		}
	}

private:
	std::vector<Object*> Objects;
	std::vector<Light*> Lights;
	Color SkyColor;
};

////////////////////////////////////////////////////////////////////////////////
