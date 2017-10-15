/*
Class defining Mesh of inputted .ply model (Triangles, Vertices, Smoothing info, etc...)
*/
#pragma once

#include "Object.h"
#include "Triangle.h"


class MeshObject:public Object {

public:
	MeshObject();
	~MeshObject();
	Triangle *Triangles;
	//Tests for ray intersection with this object
	bool Intersect(const Ray &ray,Intersection &hit);
	//Creates a Mesh box
	void MakeBox(float x,float y,float z,Material *mtl=0);
	//Loads .ply model and converts to a MeshObject
	bool LoadPLY(const char *filename, Material *mtl);
	//Smooths surface of mesh by taking averages of adjacent normals
	void Smooth();
	int returnNumTriangles();

private:
	int NumVertexes,NumTriangles;
	Vertex *Vertexes;

};

////////////////////////////////////////////////////////////////////////////////
