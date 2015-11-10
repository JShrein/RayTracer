#ifndef AABB_H
#define AABB_H

#include "Ray.h"
#include "Point3D.h"

// Axis-Aligned Bounding Box
class AABB
{
public:
	double x0, y0, z0, x1, y1, z1;

public:
	AABB();
	AABB(const double x0, const double y0, const double z0, const double x1, const double y1, const double z1);
	AABB(const Point3D& a, const Point3D& b);
	AABB(const AABB& box);
	~AABB();

	AABB& operator=(const AABB& box);
	
	bool hit(const Ray& ray) const;
	// Test if ray starts inside grid
	bool inside(const Point3D& p);
};

#endif // AABB_H