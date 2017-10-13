#ifndef CAMERA_HEADER
#define CAMERA_HEADER

#include "Camera.h"
#include <iostream>
#include "PointLight.h"
#include "DirectLight.h"
#include <future>
#include <random>
#include "RayTrace.h"

using namespace glm;


#define PI 3.14159265

	void Camera::LookAt(vec3 pos, vec3 look, vec3 up) {
		vec3 d = pos;
		vec3 c = normalize(d - look);
		vec3 a = normalize(cross(up, c));
		vec3 b = cross(c, a);
		lookAtMatrix = { a.x, a.y, a.z, 0, b.x, b.y, b.z, 0, c.x, c.y, c.z, 0, d.x, d.y, d.z, 1 };
	}
	void Camera::SetResolution(int x, int y) {
		resWidth = x;
		resHeight = y;
	}
	void Camera::SetFOV(float fov) {
		FOVY = fov * PI / 180.0f;
	}
	void Camera::SetAspect(float asp) {
		aspect = asp;
	}
	void Camera::SetDepthOfField(float fp, float radius) {
		DOF = true;
		focalPoint = fp;
		aperture = radius;

	}
	void Camera::Render(Scene scn) {
		FOVX = 2.0f * atan(aspect * tan(FOVY / 2.0f));
		bmp = new Bitmap(resWidth, resHeight);
		std::size_t max = resWidth * resHeight;
		std::size_t cores = std::thread::hardware_concurrency();
		volatile std::atomic<std::size_t> count(0);
		std::vector<std::future<void>> future_vector;
		while (cores--)
			future_vector.emplace_back(
				std::async([=, &scn, &count]()
		{
			while (true)
			{
				std::size_t index = count++;
				if (index >= max)
					break;
				std::size_t x = index % resWidth;
				std::size_t y = index / resWidth;
				bmp->SetPixel(x, y, RenderPixel(x, y, scn));
			}
		}));
		/*for (int i = 0; i < resWidth; i++) {
			for (int j = 0; j < resHeight; j++) {
				std::cout << i << ", " << j << " : " << std::endl;	
				bmp->SetPixel(i, j, RenderPixel(i, j, scn));	
			}
		}*/
	}
	void Camera::SetSuperSample(int xsamples, int ysamples) {
		if (xsamples > 1 || ysamples > 1) {
			xSamples = xsamples;
			ySamples = ysamples;
			supersample = true;
		}
	}
	void Camera::SetJitter(bool enable) {
		jitter = enable;
	}
	void Camera::SetShirley(bool enable) {
		shirley = enable;
	}
	int Camera::RenderPixel(int i, int j, Scene &scn) {
		if (supersample) {
			Color temp;
			temp.Set(0, 0, 0);
			for (float x = 0; x < xSamples; x++) {
				for (float y = 0; y < ySamples; y++) {
					float fx = 0.5f;  
					float fy = 0.5f;  
					if (jitter) {
						std::random_device rand_dev;
						std::mt19937 generator(rand_dev());
						std::uniform_real_distribution<double> distribution(0.0, 1.0);
						fx = distribution(generator);
						fy = distribution(generator);
					}
					if (shirley) {
						float addx, addy;
						if (fx < 0.5f) {
							double temp = -0.5f + sqrt(2.0f * fx);
							if (temp >= 0 && temp <= 1) fx = temp;
						}
						else if (fx >= 0.5f) {
							double temp = 1.5f - sqrt(2.0f - (2.0f * fx));
							if (temp >= 0 && temp <= 1) fx = temp;
						}
						if (fy < 0.5f) {
							double temp = -0.5f + sqrt(2.0f * fy);
							if (temp >= 0 && temp <= 1) fy = temp;
						}
						else if (fy >= 0.5f) {
							double temp = 1.5f - sqrt(2.0f - (2.0f * fy));
							if (temp >= 0 && temp <= 1) fy = temp;
						}
					}
					fx = ((i + (x / xSamples) + (fx / xSamples)) / float(resWidth)) - 0.5f;
					fy = ((j + (y / ySamples) + (fy / ySamples)) / float(resHeight)) - 0.5f;
					vec3 a = vec3(lookAtMatrix[0]);
					vec3 b = vec3(lookAtMatrix[1]);
					vec3 c = vec3(lookAtMatrix[2]);
					vec3 d = vec3(lookAtMatrix[3]);
					float scaleX = 2.0f * tan(FOVX / 2.0f);
					float scaleY = 2.0f * tan(FOVY / 2.0f);
					Ray ray;
					ray.Origin = d;
					ray.Direction = glm::normalize((fx * scaleX * a) + (fy * scaleY * b) - c);
					ray.setTime();
					if (DOF) {
						// http://www.cs.unc.edu/~jpool/COMP870/Assignment2/
						std::random_device rand_dev;
						std::mt19937 generator(rand_dev());
						std::uniform_real_distribution<double> distribution(0.0f, 2.0f * PI);
						std::uniform_real_distribution<double> distribution2(0.0f, 1.0f);
						float angle = distribution(generator);
						float radius = distribution2(generator);
						glm::vec2 circPoint(cos(angle) * radius, sin(angle) * radius);
						vec3 apertureOffset(circPoint[0] * aperture, circPoint[1] * aperture, 0.0f);
						ray.Origin += apertureOffset;
						ray.Direction *= focalPoint;
						ray.Direction -= apertureOffset;
						ray.Direction = normalize(ray.Direction);
					}
					Intersection hit;
					RayTrace rt(scn);///////////////////////////////////////////////////////MOVE this shit into Render() so I dont need to keep redoing this per pixel
					if (!Path) rt.turnOffPath();
					rt.TraceRay(ray, hit, 1);
					temp.Add(hit.Shade);
				}
			}
			temp.Scale(1.0f / (xSamples * ySamples));
			return temp.ToInt();
		}
		else { /////////////////////////////////////////////////////////////////////////NEED TO CHANGE to let shirley and jitter apply to non supersampled too
			float fx = ((float(i) + 0.5f) / float(resWidth)) - 0.5f;
			float fy = ((float(j) + 0.5f) / float(resHeight)) - 0.5f;
			vec3 a = vec3(lookAtMatrix[0]);
			vec3 b = vec3(lookAtMatrix[1]);
			vec3 c = vec3(lookAtMatrix[2]);
			vec3 d = vec3(lookAtMatrix[3]);
			float scaleX = 2.0f * tan(FOVX / 2.0f);
			float scaleY = 2.0f * tan(FOVY / 2.0f);
			Ray ray;
			ray.Origin = d;
			ray.Direction = glm::normalize((fx * scaleX * a) + (fy * scaleY * b) - c);
			ray.setTime();
			if (DOF) {
				// http://www.cs.unc.edu/~jpool/COMP870/Assignment2/
				std::random_device rand_dev;
				std::mt19937 generator(rand_dev());
				std::uniform_real_distribution<double> distribution(0.0f, 2.0f * PI);
				std::uniform_real_distribution<double> distribution2(0.0f, 1.0f);
				float angle = distribution(generator);
				float radius = distribution2(generator);
				glm::vec2 circPoint(cos(angle) * radius, sin(angle) * radius);
				vec3 apertureOffset(circPoint[0] * aperture, circPoint[1] * aperture, 0.0f);
				ray.Origin += apertureOffset;
				ray.Direction *= focalPoint;
				ray.Direction -= apertureOffset;
				ray.Direction = normalize(ray.Direction);
			}
			Intersection hit;
			RayTrace rt(scn);
			if (!Path) rt.turnOffPath();
			rt.TraceRay(ray, hit, 1);
			return hit.Shade.ToInt();
		}
	}
	void Camera::SaveBitmap(const char *filename) {
		bmp->SaveBMP(filename);
	}
	void Camera::PathTracingOff() {
		Path = false;
	}

#endif