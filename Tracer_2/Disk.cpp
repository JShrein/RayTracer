#include "Disk.h"

Disk::Disk()
	: GeometricObject(),
	  center(Point3D(0,0,0)),
	  radius(1.0),
	  rSquared(1.0),
	  normal(Normal(0, 1, 0))
{ }

Disk::Disk(const Point3D& c)
	: GeometricObject(),
	  center(c),
	  radius(1.0),
	  rSquared(1.0),
  	  normal(Normal(0,1,0))
{ }

Disk::Disk(const Point3D& c, double r)
	: GeometricObject(),
	  center(c),
	  radius(1.0),
	  rSquared(1.0),
	  normal(Normal(0,1,0))
{ }

Disk::Disk(const Point3D& c, double r, Normal n)
	: GeometricObject(),
	  center(c),
	  radius(r),
	  rSquared(r*r),
	  normal(n)
{ }

// copy ctor
Disk::Disk(const Disk& d)
	: GeometricObject(d),
	  center(d.center),
	  radius(d.radius),
	  rSquared(d.rSquared),
	  normal(d.normal)
{ }

Disk::~Disk()
{ }

// Assignment operator
Disk& Disk::operator=(const Disk& d)
{
	if (this == &d)
		return *this;

	GeometricObject::operator=(d);

	center = d.center;
	radius = d.radius;
	rSquared = d.rSquared;
	normal = d.normal;

	return *this;
}


Disk* Disk::clone() const
{
	return new Disk(*this);
}

bool Disk::hit(const Ray& ray, double& tMin, ShadeRec& sr) const
{
	double t = (center - ray.o) * normal / (ray.d * normal);

	if (t <= kEpsilon)
		return false;

	Point3D p = ray.o + t * ray.d;

	if (center.d_squared(p) < rSquared)
	{
		tMin = t;
		sr.normal = normal;
		sr.localHitPoint = p;
		return true;
	}
	else
		return false;
}

bool Disk::shadowHit(const Ray& ray, double& tMin) const
{
	double t = (center - ray.o) * normal / (ray.d * normal);

	if (t <= kEpsilon)
		return false;

	Point3D p = ray.o + t * ray.d;

	if (center.d_squared(p) < rSquared)
	{
		tMin = t;
		return true;
	}
	else
		return false;
}
