#include "Sphere.h"
#include <cmath>

const double Sphere::kEpsilon = 0.001;

// Default Constructor
Sphere::Sphere()
	: GeometricObject(),
	  center(0.0),
	  radius(1.0)
{ }

// Constructor
Sphere::Sphere(Point3D c, double r)
	: GeometricObject(),
	  center(c),
	  radius(r)
{ }

Sphere* Sphere::clone() const {
	return new Sphere(*this);
}

// Copy ctor
Sphere::Sphere(const Sphere& sphere)
	: GeometricObject(sphere),
	center(sphere.center),
	radius(sphere.radius)
{ }

// Assignment operator
Sphere& Sphere::operator=(const Sphere& s)
{
	if (this == &s)
		return *this;

	GeometricObject::operator=(s);

	center = s.center;
	radius = s.radius;

	return *this;
}

// Destructor
Sphere::~Sphere() 
{ }

// Sphere hit
bool Sphere::hit(const Ray& ray, double& tmin, ShadeRec& sr) const 
{
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
		double denom = 1.0 / (2.0 * a);
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

bool Sphere::shadowHit(const Ray& ray, double& tMin) const
{
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
			tMin = t;
			return true;
		}

		t = (-b + e) * denom;

		if (t > kEpsilon)
		{
			tMin = t;
			return true;
		}
	}

	return false;
}