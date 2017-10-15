/*
Abstract class that defines Object superclass of other object types
*/
#pragma once

#include "Ray.h"
#include "Intersection.h"

class Object {
public:
	virtual ~Object()	{}
	//Intersection virtual function that other object classes must override
	virtual bool Intersect(const Ray &ray, Intersection &hit)=0;
};

