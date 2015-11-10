#ifndef MULTIPLE_OBJECTS_H
#define MULTIPLE_OBJECTS_H

#include "Tracer.h"

class MultipleObjects : public Tracer {
public:
	MultipleObjects();

	MultipleObjects(World* _world_ptr);

	virtual ~MultipleObjects();

	//virtual RGBColor traceRay(const Ray& ray) const;
	//virtual RGBColor traceRay(const Ray ray, const int depth) const;
};

#endif // MULTIPLE_OBJECTS_H