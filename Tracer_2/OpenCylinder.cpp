#include "OpenCylinder.h"
#include <cmath>

// This uses the value of kEpsilon defined in Constants.h
// default constructor
OpenCylinder::OpenCylinder()
	: GeometricObject(),
	  y0(-1.0),
	  y1(1.0),
	  radius(1.0),
	  invRadius(1.0)
{ }

// constructor
OpenCylinder::OpenCylinder(const double yMin, const double yMax, const double r)
	: GeometricObject(),
	  y0(yMin),
	  y1(yMax),
	  radius(r),
	  invRadius(1.0 / radius)
{ }

// copy constructor
OpenCylinder::OpenCylinder(const OpenCylinder& c)
	: GeometricObject(c),
	y0(c.y0),
	y1(c.y1),
	radius(c.radius),
	invRadius(c.invRadius)
{ }

// clone
OpenCylinder* OpenCylinder::clone() const 
{
	return new OpenCylinder(*this);
}


// assignment operator
OpenCylinder& OpenCylinder::operator= (const OpenCylinder& oc)
{
	if (this == &oc)
		return *this;

	GeometricObject::operator= (oc);

	y0 = oc.y0;
	y1 = oc.y1;
	radius = oc.radius;
	invRadius = oc.invRadius;

	return *this;
}


// destructor
OpenCylinder::~OpenCylinder() {}

// hit
// The code reverses the normal when the ray hits the inside surface, allows both
// sides to be shaded, but completely messes up transparency.
bool OpenCylinder::hit(const Ray& ray, double& tmin, ShadeRec& sr) const 
{
	double t;

	double a = ray.d.x * ray.d.x + ray.d.z * ray.d.z;
	double b = 2.0 * (ray.o.x * ray.d.x + ray.o.z * ray.d.z);
	double c = ray.o.x * ray.o.x + ray.o.z * ray.o.z - radius * radius;
	double disc = b * b - 4.0 * a * c;


	if (disc < 0.0)
		return(false);
	else {
		double e = sqrt(disc);
		double denom = 1.0 / (2.0 * a);
		t = (-b - e) * denom;    // smaller root

		if (t > kEpsilon) {
			double yhit = ray.o.y + t * ray.d.y;

			if (yhit > y0 && yhit < y1)
			{
				tmin = t;
				sr.normal = Normal((ray.o.x + t * ray.d.x) * invRadius, 0.0, (ray.o.z + t * ray.d.z) * invRadius);

				// test for hitting from inside

				if (-ray.d * sr.normal < 0.0)
					sr.normal = -sr.normal;

				sr.localHitPoint = ray.o + tmin * ray.d;

				return true;
			}
		}

		t = (-b + e) * denom;    // larger root

		if (t > kEpsilon)
		{
			double yhit = ray.o.y + t * ray.d.y;

			if (yhit > y0 && yhit < y1)
			{
				tmin = t;
				sr.normal = Normal((ray.o.x + t * ray.d.x) * invRadius, 0.0, (ray.o.z + t * ray.d.z) * invRadius);

				// test for hitting inside surface

				if (-ray.d * sr.normal < 0.0)
					sr.normal = -sr.normal;

				sr.localHitPoint = ray.o + tmin * ray.d;

				return true;
			}
		}
	}

	return false;
}


bool OpenCylinder::shadowHit(const Ray& ray, double& tMin) const
{

	double t;

	double a = ray.d.x * ray.d.x + ray.d.z * ray.d.z;
	double b = 2.0 * (ray.o.x * ray.d.x + ray.o.z * ray.d.z);
	double c = ray.o.x * ray.o.x + ray.o.z * ray.o.z - radius * radius;
	double disc = b * b - 4.0 * a * c;


	if (disc < 0.0)
		return(false);
	else {
		double e = sqrt(disc);
		double denom = 1.0 / (2.0 * a);
		t = (-b - e) * denom;    // smaller root

		if (t > kEpsilon)
		{
			double yhit = ray.o.y + t * ray.d.y;

			if (yhit > y0 && yhit < y1)
			{
				tMin = t;
				Normal normal((ray.o.x + t * ray.d.x) * invRadius, 0.0, (ray.o.z + t * ray.d.z) * invRadius);

				// test for hitting from inside
				if (-ray.d * normal < 0.0)
					normal = normal;

				return true;
			}
		}

		t = (-b + e) * denom;    // larger root

		if (t > kEpsilon) 
		{
			double yhit = ray.o.y + t * ray.d.y;

			if (yhit > y0 && yhit < y1) 
			{
				tMin = t;
				Normal normal((ray.o.x + t * ray.d.x) * invRadius, 0.0, (ray.o.z + t * ray.d.z) * invRadius);

				// test for hitting inside surface

				if (-ray.d * normal < 0.0)
					normal = -normal;

				return true;
			}
		}
	}
	return false;
}
