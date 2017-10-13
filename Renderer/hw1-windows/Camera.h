#pragma once
#include "glm/glm.hpp"
#include "Scene.h"
#include "Bitmap.h"

using namespace glm;

class Camera {
private:
	mat4x4 lookAtMatrix;
	int resWidth, resHeight;
	float FOVY, FOVX;
	float aspect;
	Bitmap *bmp;
	int xSamples;
	int ySamples;
	bool supersample;
	bool jitter;
	bool shirley;
	bool DOF;
	bool Path;
	float focalPoint;
	float aperture;

public:
	Camera() {
		supersample = false;
		jitter = false;
		shirley = false;
		DOF = false;
		Path = true;
	}
	void LookAt(vec3 pos, vec3 look, vec3 up);
	void SetResolution(int x, int y);
	void SetFOV(float fov);
	void SetAspect(float asp);
	void Render(Scene scn);
	int RenderPixel(int i, int j, Scene &scn);
	void SaveBitmap(const char *filename);

	void SetSuperSample(int xsamples, int ysamples);
	void SetJitter(bool enable);
	void SetShirley(bool enable);
	void SetDepthOfField(float fp, float radius);
	void PathTracingOff();
}; 

