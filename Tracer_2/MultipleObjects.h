#ifndef __MULTIPLE_OBJECTS__
#define __MULTIPLE_OBJECTS__

#include "Tracer.h"

class MultipleObjects : public Tracer {
public:
	MultipleObjects(void);

	MultipleObjects(World* _world_ptr);

	virtual ~MultipleObjects(void);

	virtual RGBColor traceRay(const Ray& ray) const;
	virtual RGBColor traceRay(const Ray ray, const int depth) const;
};

#endif // __MULTIPLE_OBJECTS__