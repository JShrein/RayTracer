#ifndef GEOMETRIC_OBJECT_H
#define GEOMETRIC_OBJECT_H

#include "Point3D.h"
#include "Ray.h"
#include "ShadeRec.h"
#include "RGBColor.h"
#include "AABB.h"

class Material;
class ShadeRec;

class GeometricObject {
public:
	GeometricObject();
	GeometricObject(const GeometricObject& object);

	virtual ~GeometricObject();
	virtual bool hit(const Ray& ray, double& t, ShadeRec& sr) const = 0;
	virtual bool shadowHit(const Ray& ray, double& tMin) const;

	virtual GeometricObject* clone() const = 0;

	//virtual RGBColor get_color() = 0;

	Material* getMat() const;
	void setMat(Material* material_ptr);

	virtual void setAABB();
	virtual AABB getAABB();

	// Compound Objects
	virtual void addObject(GeometricObject* object_ptr);

protected:
	//RGBColor color;
	GeometricObject& operator=(const GeometricObject& obj);
	mutable Material* mat_ptr;
};

inline Material* GeometricObject::getMat() const
{
	return mat_ptr;
}

#endif // GEOMETRIC_OBJECT_H