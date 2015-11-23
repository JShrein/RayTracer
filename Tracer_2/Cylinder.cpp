//#include "Cylinder.h"
//#include <cmath>
//
//const double Cylinder::kEpsilon = 0.00001;
//
//// Default Constructor
//Cylinder::Cylinder()
//	: GeometricObject(),
//	center(Point3D(0.0)),
//	radius(1.0)
//{ }
//
//// Constructor
//Cylinder::Cylinder(Point3D c, double r)
//	: GeometricObject(),
//	center(c),
//	radius(r)
//{ }
//
//Cylinder* Cylinder::clone() const {
//	return new Cylinder(*this);
//}
//
//// Copy ctor
//Cylinder::Cylinder(const Cylinder& cyl)
//	: GeometricObject(cyl),
//	center(cyl.center),
//	radius(cyl.radius)
//{ }
//
//// Assignment operator
//Cylinder& Cylinder::operator=(const Cylinder& cyl)
//{
//	if (this == &cyl)
//		return *this;
//
//	GeometricObject::operator=(cyl);
//
//	center = cyl.center;
//	radius = cyl.radius;
//
//	return *this;
//}
//
//// Destructor
//Cylinder::~Cylinder()
//{ }
//
//// Cylinder hit
//bool Cylinder::hit(const Ray& ray, double& tmin, ShadeRec& sr) const {
//	double t;
//
//	Vector3D newPos = ray.o - center;
//
//	double a = ray.d.x * ray.d.x + ray.d.z * ray.d.z;
//	double b = 2.0 * (newPos.x * ray.d.x + newPos.z * ray.d.z);// (ray.o.x * ray.d.x + ray.o.z * ray.d.z);
//	double c = newPos.x * newPos.x + newPos.z * newPos.z - radius * radius;
//	double disc = b * b - 4.0 * a * c;
//
//	if (disc < 0.0)
//	{
//		return false;
//	}
//	else
//	{
//		double e = sqrt(disc);
//		double denom = 1.0 / (2.0 * a);
//		double r = 1.0 / radius;
//
//		t = (-b - e) * denom;
//
//		if (t > kEpsilon)
//		{
//			tmin = t;
//			//sr.normal = (temp + t * ray.d) * r;
//
//			sr.localHitPoint = ray.o + t * ray.d;
//			sr.normal = Normal((newPos.x + t * ray.d.x) * r, 0, (newPos.z + t * ray.d.z) * r);
//			//sr.normal.normalize();
//			
//			if (sr.localHitPoint.y <= yMaximum && sr.localHitPoint.y >= yMinimum)
//			{
//				return true;
//			}
//		}
//
//		t = (-b + e) * denom;
//
//		if (t > kEpsilon)
//		{
//			tmin = t;
//			//sr.normal = (temp + t * ray.d) * r;
//			sr.localHitPoint = ray.o + t * ray.d;
//			sr.normal = Normal((newPos.x + t * ray.d.x) * r, 0, (newPos.z + t * ray.d.z) * r);
//			//sr.normal.normalize();
//
//			if (sr.localHitPoint.y <= yMaximum && sr.localHitPoint.y >= yMinimum)
//			{
//				return true;
//			}
//		}
//	}
//
//	return false;
//}
//
//bool Cylinder::shadowHit(const Ray& ray, double& tMin) const
//{
//	double t;
//
//	Vector3D newPos = ray.o - center;
//
//	double a = ray.d.x * ray.d.x + ray.d.z * ray.d.z;
//	double b = 2.0 * (newPos.x * ray.d.x + newPos.z * ray.d.z);// (ray.o.x * ray.d.x + ray.o.z * ray.d.z);
//	double c = newPos.x * newPos.x + newPos.z * newPos.z - radius * radius;
//	double disc = b * b - 4.0 * a * c;
//
//	if (disc < 0.0)
//	{
//		return false;
//	}
//	else
//	{
//		double e = sqrt(disc);
//		double denom = 1.0 / (2.0 * a);
//		double r = 1.0 / radius;
//
//		t = (-b - e) * denom;
//
//		if (t > kEpsilon)
//		{
//			tMin = t;
//			Point3D hitPoint = ray.o + t * ray.d;
//			if (hitPoint.y <= yMaximum && hitPoint.y >= yMinimum)
//			{
//				return true;
//			}
//			return false;
//		}
//
//		t = (-b + e) * denom;
//
//		if (t > kEpsilon)
//		{
//			tMin = t;
//			Point3D hitPoint = ray.o + t * ray.d;
//
//			if (hitPoint.y <= yMaximum && hitPoint.y >= yMinimum)
//			{
//				return true;
//			}
//			return false;
//		}
//	}
//
//	return false;
//}