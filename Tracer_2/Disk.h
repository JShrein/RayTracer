#ifndef DISK_H
#define DISK_H

#include "GeometricObject.h"

class Disk : public GeometricObject
{
public:
	Point3D center;
	double radius;
	double rSquared;
	Normal normal;

public:
	Disk();
	Disk(const Point3D& center);
	Disk(const Point3D& center, double radius);
	Disk(const Point3D& center, double radius, Normal n);
	Disk(const Disk& d);
	~Disk();

	Disk& operator=(const Disk& d);

	Disk* clone() const;

	virtual bool hit(const Ray& ray, double& tMin, ShadeRec& sr) const;
	virtual bool shadowHit(const Ray& ray, double& tMin) const;
};

#endif // DISK_H