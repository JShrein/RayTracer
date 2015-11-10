#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "GeometricObject.h"

class Triangle : public GeometricObject
{
public:
	Point3D v0, v1, v2;
	Normal normal;

public:
	Triangle();
	Triangle(const Point3D& a, const Point3D& b, const Point3D& c);
	Triangle(const Triangle& t);
	~Triangle();

	virtual Triangle* clone() const;
	
	Triangle& operator=(const Triangle& t);

	virtual bool hit(const Ray& ray, double& tMin, ShadeRec& sr) const;
	virtual bool shadowHit(const Ray& ray, double& tMin) const;
};

#endif // TRIANGLE_H