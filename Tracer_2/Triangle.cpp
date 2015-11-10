#include "Triangle.h"

Triangle::Triangle()
	: GeometricObject(),
	  v0(0, 0, 0), v1(0, 0, 1), v2(1, 0, 0),
	  normal(0, 1, 0)
{ }

Triangle::Triangle(const Point3D& a, const Point3D& b, const Point3D& c)
	: GeometricObject(),
	  v0(a), v1(b), v2(c)
{ 
	normal = (v1 - v0) ^ (v2 - v0);
	normal.normalize();
}

// copy ctor
Triangle::Triangle(const Triangle& t)
	: GeometricObject(t),
	v0(t.v0),
	v1(t.v1),
	v2(t.v2),
	normal(t.normal)
{ }

Triangle::~Triangle()
{ }

Triangle* Triangle::clone() const 
{
	return new Triangle(*this);
}

// Assignment operator
Triangle& Triangle::operator=(const Triangle& t)
{
	if (this == &t)
		return *this;

	GeometricObject::operator=(t);

	v0 = t.v0;
	v1 = t.v1;
	v2 = t.v2;
	normal = t.normal;

	return *this;
}

bool Triangle::hit(const Ray& ray, double& tMin, ShadeRec& sr) const
{
	double a = v0.x - v1.x, b = v0.x - v2.x, c = ray.d.x, d = v0.x - ray.o.x;
	double e = v0.y - v1.y, f = v0.y - v2.y, g = ray.d.y, h = v0.y - ray.o.y;
	double i = v0.z - v1.z, j = v0.z - v2.z, k = ray.d.z, l = v0.z - ray.o.z;

	double m = f * k - g * j, n = h * k - g * l, p = f * l - h * j;
	double q = g * i - e * k, s = e * j - f * i;

	double invDenom = 1.0 / (a * m + b * q + c * s);

	double e1 = d * m - b * n - c * p;
	double beta = e1 * invDenom;

	if (beta < 0.0)
		return false;

	double r = r = e * l - h * i;
	double e2 = a * n + d * q + c * r;
	double gamma = e2 * invDenom;

	if (gamma < 0.0)
		return false;

	if (beta + gamma > 1.0)
		return false;

	double e3 = a * p - b * r + d * s;
	double t = e3 * invDenom;

	if (t < kEpsilon)
		return false;

	tMin = t;
	sr.normal = normal;
	sr.localHitPoint = ray.o + t * ray.d;

	return true;
}

bool Triangle::shadowHit(const Ray& ray, double& tMin) const
{
	double a = v0.x - v1.x, b = v0.x - v2.x, c = ray.d.x, d = v0.x - ray.o.x;
	double e = v0.y - v1.y, f = v0.y - v2.y, g = ray.d.y, h = v0.y - ray.o.y;
	double i = v0.z - v1.z, j = v0.z - v2.z, k = ray.d.z, l = v0.z - ray.o.z;

	double m = f * k - g * j, n = h * k - g * l, p = f * l - h * j;
	double q = g * i - e * k, s = e * j - f * i;

	double invDenom = 1.0 / (a * m + b * q + c * s);

	double e1 = d * m - b * n - c * p;
	double beta = e1 * invDenom;

	if (beta < 0.0)
		return false;

	double r = r = e * l - h * i;
	double e2 = a * n + d * q + c * r;
	double gamma = e2 * invDenom;

	if (gamma < 0.0)
		return false;

	if (beta + gamma > 1.0)
		return false;

	double e3 = a * p - b * r + d * s;
	double t = e3 * invDenom;

	if (t < kEpsilon)
		return false;

	tMin = t;

	return true;
}