#include "Tracer.h"

// Constructors
Tracer::Tracer(void)
	: world_ptr(NULL)
{}

Tracer::Tracer(World* _worldPtr)
	: world_ptr(_worldPtr)
{}

// Destructor
Tracer::~Tracer(void) {
	if (world_ptr)
		world_ptr = NULL;
}


// Trace Ray
RGBColor Tracer::traceRay(const Ray& ray) const 
{
	return black;
}

RGBColor Tracer::traceRay(const Ray ray, const int depth) const 
{
	return red;
}

RGBColor Tracer::traceRay(const Ray ray, float& tMin, const int depth) const 
{
	return red;
}