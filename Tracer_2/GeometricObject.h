#ifndef __GEOMETRIC_OBJECT__
#define __GEOMETRIC_OBJECT__

#include "Point3D.h"
#include "Ray.h"
#include "ShadeRec.h"
#include "RGBColor.h"

class ShadeRec;

class GeometricObject {
public:
	GeometricObject();
	GeometricObject(const GeometricObject& object);

	virtual ~GeometricObject();
	virtual bool hit(const Ray& ray, double& tmin, ShadeRec& sr) const = 0;
	virtual RGBColor get_color() = 0;

protected:
	RGBColor color;
	GeometricObject& operator=(const GeometricObject& rhs);
};

#endif // __GEOMETRIC_OBJECT__