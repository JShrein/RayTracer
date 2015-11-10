#ifndef SOLID_CYLINDER_H
#define SOLID_CYLINDER_H

#include "CompoundObject.h"

class SolidCylinder : public CompoundObject
{
public:
	AABB aabb;
public:
	SolidCylinder();
	SolidCylinder(const double yMin, const double yMax, const double radius);
	SolidCylinder(const SolidCylinder& sc);
	virtual ~SolidCylinder();

	SolidCylinder& operator= (const SolidCylinder& sc);
	virtual SolidCylinder* clone() const;

	virtual AABB getAABB();
	
	virtual bool SolidCylinder::hit(const Ray& ray, double& tMin, ShadeRec& sr) const;
	virtual bool SolidCylinder::shadowHit(const Ray& ray, double& tMin) const;
};

#endif // SOLID_CYLINDER_H