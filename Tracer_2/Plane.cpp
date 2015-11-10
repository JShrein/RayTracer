#include "Plane.h"

const double Plane::kEpsilon = 0.00001;

Plane::Plane()
	: GeometricObject(), 
	point(0.0), 
	normal(0, 1, 0)
{ }

Plane::Plane(const Point3D& p, const Normal& n)
	: GeometricObject(), 
	point(p), 
	normal(n)
{
	normal.normalize();
}

Plane::Plane(const Plane& p)
	: GeometricObject(p), 
	point(p.point), 
	normal(p.normal)
{ }


// Clone
Plane* Plane::clone() const 
{
	return new Plane(*this);
}

// Assignment operator
Plane& Plane::operator= (const Plane& p)	
{

	if (this == &p)
		return (*this);

	GeometricObject::operator= (p);

	point = p.point;
	normal = p.normal;

	return *this;
}

// destructor
Plane::~Plane()
{ }


// Hit
bool Plane::hit(const Ray& ray, double& tmin, ShadeRec& sr) const 
{
	float t = float((point - ray.o) * normal / (ray.d * normal));

	if (t > kEpsilon) {
		tmin = t;
		sr.normal = normal;
		sr.localHitPoint = ray.o + t * ray.d;

		return (true);
	}

	return(false);
}

bool Plane::shadowHit(const Ray& ray, double& tMin) const
{
	double t = (point - ray.o) * normal / (ray.d * normal);

	if (t > kEpsilon) {
		tMin = t;
		return true;
	}
	return false;
}