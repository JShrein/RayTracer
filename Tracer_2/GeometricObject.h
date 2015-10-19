#ifndef __GEOMETRIC_OBJECT__
#define __GEOMETRIC_OBJECT__

#include "Point3D.h"
#include "Ray.h"
#include "ShadeRec.h"
#include "RGBColor.h"

class Material;
class ShadeRec;

class GeometricObject {
public:
	GeometricObject();
	GeometricObject(const GeometricObject& object);

	virtual ~GeometricObject();
	virtual bool hit(const Ray& ray, double& t, ShadeRec& sr) const = 0;
	virtual RGBColor get_color() = 0;

	Material* getMat() const;
	void setMat(Material* material_ptr);

protected:
	RGBColor color;
	GeometricObject& operator=(const GeometricObject& obj);
	Material* mat_ptr;
};

inline Material* GeometricObject::getMat() const
{
	return mat_ptr;
}

#endif // __GEOMETRIC_OBJECT__