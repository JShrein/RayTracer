#include "Box.h"
#include "Constants.h"
#include "Maths.h"

Box::Box()
	: x0(-1), y0(-1), z0(-1), x1(1), y1(1), z1(1)
{ }

Box::Box(const double _x0, const double _y0, const double _z0, const double _x1, const double _y1, const double _z1)
	: x0(_x0), y0(_y0), z0(_z0), x1(_x1), y1(_y1), z1(_z1)
{ }

Box::Box(const Point3D& a, const Point3D& b)
	: x0(a.x), y0(a.y), z0(a.z), x1(b.x), y1(b.y), z1(b.z)
{ }

Box::Box(const Box& box)
	: x0(box.x0), y0(box.y0), z0(box.z0), x1(box.x1), y1(box.y1), z1(box.z1)
{ }

Box::~Box()
{ }


Box& Box::operator=(const Box& box)
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

Box* Box::clone() const
{
	return new Box(*this);
}

bool Box::hit(const Ray& ray, double& tMin, ShadeRec& sr) const
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
	int faceIn, faceOut;

	// Largest entering t value
	if (txMin > tyMin)
	{
		t0 = txMin;
		faceIn = (a >= 0.0) ? 0 : 3;
	}
	else
	{
		t0 = tyMin;
		faceIn = (b >= 0.0) ? 1 : 4;
	}
	if (tzMin > t0)
	{
		t0 = tzMin;
		faceIn = (c >= 0.0) ? 2 : 5;
	}

	// Smallest exiting t value
	if (txMax < tyMax)
	{
		t1 = txMax;
		faceOut = (a >= 0.0) ? 3 : 0;
	}
	else
	{
		t1 = tyMax;
		faceOut = (b >= 0.0) ? 4 : 1;
	}
	if (tzMax < t1)
	{
		t1 = tzMax;
		faceOut = (c >= 0.0) ? 5 : 2;
	}

	if (t0 < t1 && t1 > kEpsilon)
	{
		if (t0 > kEpsilon)
		{
			tMin = t0;
			sr.normal = getNormal(faceIn);
		}
		else
		{
			tMin = t1;
			sr.normal = getNormal(faceOut);
		}
		sr.localHitPoint = ray.o + tMin * ray.d;
		return true;
	}
	else
	{
		return false;
	}
}

bool Box::shadowHit(const Ray& ray, double& tMin) const
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
	int faceIn, faceOut;

	// Largest entering t value
	if (txMin > tyMin)
	{
		t0 = txMin;
		faceIn = (a >= 0.0) ? 0 : 3;
	}
	else
	{
		t0 = tyMin;
		faceIn = (b >= 0.0) ? 1 : 4;
	}
	if (tzMin > t0)
	{
		t0 = tzMin;
		faceIn = (c >= 0.0) ? 2 : 5;
	}

	// Smallest exiting t value
	if (txMax < tyMax)
	{
		t1 = txMax;
		faceOut = (a >= 0.0) ? 3 : 0;
	}
	else
	{
		t1 = tyMax;
		faceOut = (b >= 0.0) ? 4 : 1;
	}
	if (tzMax < t1)
	{
		t1 = tzMax;
		faceOut = (c >= 0.0) ? 5 : 2;
	}

	if (t0 < t1 && t1 > kEpsilon)
	{
		if (t0 > kEpsilon)
		{
			tMin = t0;
			//sr.normal = getNormal(faceIn);
		}
		else
		{
			tMin = t1;
			//sr.normal = getNormal(faceOut);
		}
		//sr.localHitPoint = ray.o + tMin * ray.d;
		return true;
	}
	else
	{
		return false;
	}
}

// Test if ray start inside grid
bool Box::inside(const Point3D& p)
{
	return (p.x > x0 && p.x < x1) && (p.y > y0 && p.y < y1) && (p.z > z0 && p.z < z1);
}

Normal Box::getNormal(const int hitFace) const
{
	switch (hitFace)
	{
	case 0: return Normal(-1, 0, 0);
	case 1: return Normal(0, -1, 0);
	case 2: return Normal(0, 0, -1);
	case 3: return Normal(1, 0, 0);
	case 4: return Normal(0, 1, 0);
	case 5: return Normal(0, 0, 1);
	}
	// Just here to suppress control path warning
	return Normal(0, 0, 0);
}