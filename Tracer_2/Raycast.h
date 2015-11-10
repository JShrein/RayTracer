#ifndef RAYCAST_H
#define RAYCAST_H

#include "Tracer.h"

class RayCast : public Tracer 
{
public:
	RayCast();
	RayCast(World* _worldPtr);

	virtual ~RayCast();

	virtual RGBColor traceRay(const Ray& ray) const;
	virtual RGBColor traceRay(const Ray ray, const int depth) const;
};

#endif // RAYCAST_H