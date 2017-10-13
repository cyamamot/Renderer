/*
Camera class that defines how the scene is viewed as well as antialiasing of the scene
*/

#pragma once
#include "glm/glm.hpp"
#include "Scene.h"
#include "Bitmap.h"

using namespace glm;

class Camera {
private:
	//matrix defining how camera view scene
	mat4x4 lookAtMatrix;
	//resolution
	int resWidth, resHeight;
	float FOVY, FOVX;
	float aspect;
	//bmp instance which allows scene to be turned into .bmp pixel by pixel
	Bitmap *bmp;
	//number of samples for pixel jittering
	int xSamples;
	int ySamples;
	//whether to apply certain antialiasing techniques
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

