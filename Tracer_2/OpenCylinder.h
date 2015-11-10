#ifndef OPEN_CYLINDER_H
#define OPEN_CYLINDER_H

#include "GeometricObject.h"

class OpenCylinder : public GeometricObject 
{
public:
	OpenCylinder();
	OpenCylinder(const double yMin, const double yMax, const double radius);
	OpenCylinder(const OpenCylinder& c);
	virtual ~OpenCylinder();

	virtual OpenCylinder* clone() const;
	OpenCylinder& operator= (const OpenCylinder& oc);

	virtual bool hit(const Ray& ray, double& t, ShadeRec& sr) const;
	virtual bool shadowHit(const Ray& ray, double& tMin) const;

protected:
	double y0;
	double y1;
	double radius;
	double invRadius;
};

#endif // OPEN_CYLINDER_H
