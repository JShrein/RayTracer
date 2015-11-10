#include "Tracer.h"

// Constructors
Tracer::Tracer()
	: world_ptr(NULL)
{ }

Tracer::Tracer(World* _worldPtr)
	: world_ptr(_worldPtr)
{ }

// Destructor
Tracer::~Tracer() 
{
	if (world_ptr)
		world_ptr = NULL;
}

// Trace Ray
// Returns red to make errors apparent
RGBColor Tracer::traceRay(const Ray& ray) const 
{
	return red;
}

RGBColor Tracer::traceRay(const Ray ray, const int depth) const 
{
	return red;
}

RGBColor Tracer::traceRay(const Ray ray, float& tMin, const int depth) const 
{
	return red;
}