#ifndef WHITTED_H
#define WHITTED_H

#include "Tracer.h"

class Whitted : public Tracer 
{
public:
	Whitted();
	Whitted(World* _worldPtr);

	virtual ~Whitted();

	virtual RGBColor traceRay(const Ray& ray) const;
	virtual RGBColor traceRay(const Ray ray, const int depth) const;
};

#endif // WHITTED_H