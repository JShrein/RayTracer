#include "Cylinder.h"
#include <cmath>

const double Cylinder::kEpsilon = 0.001;

// Default Constructor
Cylinder::Cylinder()
	: GeometricObject(),
	center(0.0),
	radius(1.0)
{ }

// Constructor
Cylinder::Cylinder(Point3D c, double r)
	: GeometricObject(),
	center(c),
	radius(r)
{ }

Cylinder* Cylinder::clone() const {
	return new Cylinder(*this);
}

// Copy ctor
Cylinder::Cylinder(const Cylinder& Cylinder)
	: GeometricObject(Cylinder),
	center(Cylinder.center),
	radius(Cylinder.radius)
{ }

// Assignment operator
Cylinder& Cylinder::operator=(const Cylinder& rhs)
{
	if (this == &rhs)
		return *this;

	GeometricObject::operator=(rhs);

	center = rhs.center;
	radius = rhs.radius;

	return *this;
}

// Destructor
Cylinder::~Cylinder()
{ }

// Cylinder hit
bool Cylinder::hit(const Ray& ray, double& tmin, ShadeRec& sr) const {
	double t;
	Vector3D temp = ray.o - center;
	double a = ray.d * ray.d;
	double b = 2.0 * temp * ray.d;
	double c = temp * temp - radius * radius;
	double disc = b * b - 4.0 * a * c;

	if (disc < 0.0)
	{
		return false;
	}
	else
	{
		double e = sqrt(disc);
		double denom = 1.0 / 2.0 * a;
		double r = 1.0 / radius;
		t = (-b - e) * denom;

		if (t > kEpsilon)
		{
			tmin = t;
			sr.normal = (temp + t * ray.d) * r;
			sr.localHitPoint = ray.o + t * ray.d;
			return true;
		}

		t = (-b + e) * denom;

		if (t > kEpsilon)
		{
			tmin = t;
			sr.normal = (temp + t * ray.d) * r;
			sr.localHitPoint = ray.o + t * ray.d;
			return true;
		}
	}

	return false;
}