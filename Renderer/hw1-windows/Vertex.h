/*
Class defining Vertex class
Most basic building block of Objects
*/
#pragma once

#include "glm/glm.hpp"

class Vertex {
public:
	void Set(const glm::vec3 &p, const glm::vec3 &n, const glm::vec3 &t);

public:
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec3 TexCoord;
};


