#include "AABB.h"
#include "Constants.h"
#include "Maths.h"

AABB::AABB()
	: x0(-1), y0(-1), z0(-1), x1(1), y1(1), z1(1)
{ }

AABB::AABB(const double _x0, const double _y0, const double _z0, const double _x1, const double _y1, const double _z1)
	: x0(_x0), y0(_y0), z0(_z0), x1(_x1), y1(_y1), z1(_z1)
{ }

AABB::AABB(const Point3D& a, const Point3D& b)
	: x0(a.x), y0(a.y), z0(a.z), x1(b.x), y1(b.y), z1(b.z)
{ }

AABB::AABB(const AABB& box)
	: x0(box.x0), y0(box.y0), z0(box.z0), x1(box.x1), y1(box.y1), z1(box.z1)
{ }

AABB::~AABB()
{ }


AABB& AABB::operator=(const AABB& box)
{
	if (this == &box)
		return *this;

	x0 = box.x0;
	y0 = box.y0;
	z0 = box.z0;
	x1 = box.x1;
	y1 = box.y1;
	z1 = box.z1;

	return *this;
}

// We distinguish between hit and inside intersection
bool AABB::hit(const Ray& ray) const
{
	double ox = ray.o.x, oy = ray.o.y, oz = ray.o.z;
	double dx = ray.d.x, dy = ray.d.y, dz = ray.d.z;

	double txMin, tyMin, tzMin;
	double txMax, tyMax, tzMax;

	double a = 1.0 / dx;
	if (a >= 0)
	{
		txMin = (x0 - ox) * a;
		txMax = (x1 - ox) * a;
	}
	else
	{
		txMin = (x1 - ox) * a;
		txMax = (x0 - ox) * a;
	}

	double b = 1.0 / dy;
	if (b >= 0)
	{
		tyMin = (y0 - oy) * b;
		tyMax = (y1 - oy) * b;
	}
	else
	{
		tyMin = (y1 - oy) * b;
		tyMax = (y0 - oy) * b;
	}

	double c = 1.0 / dz;
	if (c >= 0)
	{
		tzMin = (z0 - oz) * c;
		tzMax = (z1 - oz) * c;
	}
	else
	{
		tzMin = (z1 - oz) * c;
		tzMax = (z0 - oz) * c;
	}

	double t0, t1;

	// largest entering t value
	t0 = max3(txMin, tyMin, tzMin);
	t1 = min3(txMax, tyMax, tzMax);

	return t0 < t1 && t1 > kEpsilon;
}

// Test if ray start inside grid
bool AABB::inside(const Point3D& p)
{
	return (p.x > x0 && p.x < x1) && (p.y > y0 && p.y < y1) && (p.z > z0 && p.z < z1);
}