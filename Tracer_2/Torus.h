#ifndef TORUS_H
#define TORUS_H

#include "GeometricObject.h"
#include "Point3D.h"
#include "RGBColor.h"

class Torus : public GeometricObject
{
public:
	Torus();
	Torus(const Torus& t);

	virtual Torus* clone() const;
private:
	Point3D center;
	double radius;
	//RGBColor color;
};

#endif