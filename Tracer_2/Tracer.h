#ifndef TRACER_H
#define TRACER_H

#include "Constants.h"
#include "Ray.h"
#include "RGBColor.h"

class World;

// NOTE:***Do not copy-construct or clone Tracer, can't have multiple instances of World***
class Tracer {
public:
	Tracer();
	Tracer(World* _world_ptr);

	virtual ~Tracer();

	virtual RGBColor traceRay(const Ray& ray) const;
	virtual RGBColor traceRay(const Ray ray, const int depth) const;
	virtual RGBColor traceRay(const Ray ray, float& tMin, const int depth) const;

protected:
	World* world_ptr;
};

#endif // TRACER_H