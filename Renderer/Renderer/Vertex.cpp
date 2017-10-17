#include "Vertex.h"

void Vertex::Set(const glm::vec3 &p, const glm::vec3 &n, const glm::vec3 &t) { 
	Position = p; 
	Normal = n; 
	TexCoord = t; 
}