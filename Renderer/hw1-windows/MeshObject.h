////////////////////////////////////////
// MeshObject.h
////////////////////////////////////////

#pragma once

#include "Object.h"
#include "Triangle.h"

////////////////////////////////////////////////////////////////////////////////

class MeshObject:public Object {
public:
	MeshObject();
	~MeshObject();

	Triangle *Triangles;

	bool Intersect(const Ray &ray,Intersection &hit);

	void MakeBox(float x,float y,float z,Material *mtl=0);

	bool LoadPLY(const char *filename, Material *mtl);

	void Smooth();

	int returnNumTriangles();

private:
	int NumVertexes,NumTriangles;
	Vertex *Vertexes;

};

////////////////////////////////////////////////////////////////////////////////
