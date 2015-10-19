#include "Plane.h"

const double Plane::kEpsilon = 0.001;

Plane::Plane()
	: GeometricObject(), point(0.0), normal(0, 1, 0)
{ }

Plane::Plane(const Point3D& p, const Normal& n)
	: GeometricObject(), point(p), normal(n)
{
	normal.normalize();
}

Plane::Plane(const Plane& plane)
	: GeometricObject(plane), point(plane.point), normal(plane.normal)
{ }


// Clone
Plane* Plane::clone(void) const {
	return (new Plane(*this));
}

// Assignment operator
Plane& Plane::operator= (const Plane& rhs)	{

	if (this == &rhs)
		return (*this);

	GeometricObject::operator= (rhs);

	point = rhs.point;
	normal = rhs.normal;

	return (*this);
}

// destructor
Plane::~Plane(void)
{ }


// Hit
bool Plane::hit(const Ray& ray, double& tmin, ShadeRec& sr) const {
	float t = float((point - ray.o) * normal / (ray.d * normal));

	if (t > kEpsilon) {
		tmin = t;
		sr.normal = normal;
		sr.localHitPoint = ray.o + t * ray.d;

		return (true);
	}

	return(false);
}