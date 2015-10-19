#include "MultipleObjects.h"
#include "World.h"

// Constructors
MultipleObjects::MultipleObjects(void)
	: Tracer()
{ }

MultipleObjects::MultipleObjects(World* _worldPtr)
	: Tracer(_worldPtr)
{ }


// destructor
MultipleObjects::~MultipleObjects(void) 
{ }


// Trace ray
RGBColor MultipleObjects::traceRay(const Ray& ray) const {
	ShadeRec sr(world_ptr->hitBareBonesObject(ray)); // sr is copy constructed

	if (sr.hitAnObject)
		return (sr.color);
	else
		return (world_ptr->backgroundColor);
}

RGBColor MultipleObjects::traceRay(const Ray ray, const int depth) const
{
	// TODO: Implement depth, currently exactly the same as traceRay(const Ray& ray)
	ShadeRec sr(world_ptr->hitBareBonesObject(ray)); // sr is copy constructed

	if (sr.hitAnObject)
		return (sr.color);
	else
		return (world_ptr->backgroundColor);
}