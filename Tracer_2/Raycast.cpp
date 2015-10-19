#include "RayCast.h"
#include "World.h"
#include "ShadeRec.h"
#include "Material.h"
#include <iostream>

// Constructor
RayCast::RayCast(void)
	: Tracer()
{ }

RayCast::RayCast(World* _worldPtr)
	: Tracer(_worldPtr)
{ }

// Destructor
RayCast::~RayCast(void) 
{ }


// Trace ray
RGBColor RayCast::traceRay(const Ray& ray) const {
	ShadeRec sr(world_ptr->hitObjects(ray));

	if (sr.hitAnObject) {
		sr.ray = ray;
		return (sr.mat_ptr->shade(sr));
	}
	else
		return (world_ptr->backgroundColor);
}

// Since this is just ray casting, depth parameter isn't used
RGBColor RayCast::traceRay(const Ray ray, const int depth) const {
	ShadeRec sr(world_ptr->hitObjects(ray));

	if (sr.hitAnObject) {
		sr.ray = ray;

		return sr.mat_ptr->shade(sr);
	}
	else
		return world_ptr->backgroundColor;
}