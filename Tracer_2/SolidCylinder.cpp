#include "SolidCylinder.h"
#include "OpenCylinder.h"
#include "Disk.h"

SolidCylinder::SolidCylinder()
	: CompoundObject()
{ 
	objects.push_back(new Disk(Point3D(0, 0, 0), 1, Normal(0, -1, 0)));
	objects.push_back(new Disk(Point3D(0, 1, 0), 1, Normal(0, 1, 0)));
	objects.push_back(new OpenCylinder(0, 1, 1));
	aabb = AABB(-1, 0, -1, 1, 1, 1);
}

SolidCylinder::SolidCylinder(const double yMin, const double yMax, const double radius)
	: CompoundObject()
{
	objects.push_back(new Disk(Point3D(0, yMin, 0), radius, Normal(0, -1, 0)));
	objects.push_back(new Disk(Point3D(0, yMax, 0), radius, Normal(0, 1, 0)));
	objects.push_back(new OpenCylinder(yMin, yMax, radius));
	aabb = AABB(-radius, yMin, -radius, radius, yMax, radius);
}

SolidCylinder::SolidCylinder(const SolidCylinder& sc)
	: CompoundObject(sc),
	  aabb(sc.aabb)
{ }

SolidCylinder::~SolidCylinder()
{ }

SolidCylinder& SolidCylinder::operator= (const SolidCylinder& sc)
{
	if (this == &sc)
		return *this;

	aabb = sc.aabb;

	return *this;
}

SolidCylinder* SolidCylinder::clone() const
{
	return new SolidCylinder(*this);
}

AABB SolidCylinder::getAABB()
{
	return aabb;
}

bool SolidCylinder::hit(const Ray& ray, double& tMin, ShadeRec& sr) const
{
	if (aabb.hit(ray))
		return CompoundObject::hit(ray, tMin, sr);
	else
		return false;
}

bool SolidCylinder::shadowHit(const Ray& ray, double& tMin) const
{
	if (aabb.hit(ray))
		return CompoundObject::shadowHit(ray, tMin);
	else
		return false;
}