/*
Abstract Class defining charcteristics of Light, superclass of Direct and Point Lights
*/

#pragma once

#include "Color.h"
#include "glm/glm.hpp"
#include <string>


class Light {
public:
	Light()
	{Intensity=1.0; BaseColor=Color::WHITE;}

	void SetBaseColor(const Color &col)		{BaseColor=col;}
	void SetIntensity(float i)				{Intensity=i;}
	//pure virtual functions that subclasses override
	virtual glm::vec3 getDirection(const glm::vec3& start) = 0;
	virtual float Illuminate(const glm::vec3 &pos, Color &col, glm::vec3 &toLight, glm::vec3 &ltPos) = 0;

protected:
	float Intensity;
	Color BaseColor;		// Actual color is Intensity*BaseColor
};

