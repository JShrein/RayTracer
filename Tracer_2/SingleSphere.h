#ifndef SINGLE_SPHERE_H
#define SINGLE_SPHERE_H

#include "Tracer.h"

class SingleSphere : public Tracer {
public:

	SingleSphere();

	SingleSphere(World* _worldPtr);

	virtual ~SingleSphere();

	virtual RGBColor traceRay(const Ray& ray) const;
	virtual RGBColor traceRay(const Ray ray, const int depth) const;
};

#endif // SINGLE_SPHERE_H
