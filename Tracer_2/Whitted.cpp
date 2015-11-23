#include "Whitted.h"
#include "World.h"
#include "ShadeRec.h"
#include "Material.h"
#include <iostream>

// Constructor
Whitted::Whitted()
	: Tracer()
{ }

Whitted::Whitted(World* _worldPtr)
	: Tracer(_worldPtr)
{ }

// Destructor
Whitted::~Whitted()
{ }


// Trace ray
RGBColor Whitted::traceRay(const Ray& ray) const 
{
	ShadeRec sr(world_ptr->hitObjects(ray));

	if (sr.hitAnObject) {
		sr.ray = ray;
		return sr.mat_ptr->shade(sr);
	}
	else
		return world_ptr->backgroundColor;
}

// Trace ray with depth
RGBColor Whitted::traceRay(const Ray ray, const int depth) const 
{
	if (depth > world_ptr->vp.maxDepth)
		return black;
	else
	{
		ShadeRec sr(world_ptr->hitObjects(ray));

		if (sr.hitAnObject) {
			sr.depth = depth;
			sr.ray = ray;

			return sr.mat_ptr->shade(sr);
		}
		else
			return world_ptr->backgroundColor;
	}
}
