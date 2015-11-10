#ifndef BOX_H
#define BOX_H

#include "GeometricObject.h"

// Box
class Box : public GeometricObject
{
public:
	double x0, y0, z0, x1, y1, z1;

public:
	Box();
	Box(const double x0, const double y0, const double z0, const double x1, const double y1, const double z1);
	Box(const Point3D& a, const Point3D& b);
	Box(const Box& box);
	~Box();

	Box& operator=(const Box& box);
	virtual Box* clone() const;

	virtual bool hit(const Ray& ray, double& tMin, ShadeRec& sr) const;
	virtual bool shadowHit(const Ray& ray, double& tMin) const;
	// Test if ray starts inside grid
	bool inside(const Point3D& p);

	Normal getNormal(const int hitFace) const;
};

#endif // BOX_H