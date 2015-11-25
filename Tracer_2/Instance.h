#ifndef INSTANCE_H
#define INSTANCE_H

#include "GeometricObject.h"
#include "Matrix.h"

class Instance : public GeometricObject
{
public:
	// Constructors/Destructor
	Instance();
	Instance(GeometricObject* object_ptr);
	Instance(const Instance& instance);
	virtual ~Instance();

	virtual Instance* clone() const;
	Instance& operator= (const Instance& rhs);

	void setObject(GeometricObject* object_ptr);
	void texTransform(const bool transform);
	virtual void computeAABB();
	virtual AABB getAABB();
	virtual Material* getMat() const;
	virtual void setMat(Material* material_ptr);
	virtual bool hit(const Ray& ray, double& tmin, ShadeRec& sr) const;


	// Matrix Transformations
	// Translation
	void translate(const Vector3D& trans);
	void translate(const double dx, const double dy, const double dz);

	// Scale
	void scale(const Vector3D& s);
	void scale(const double a, const double b, const double c);

	// Rotations
	virtual void rotateX(const double angle);
	virtual void rotateY(const double angle);
	virtual void rotateZ(const double angle);

	// Shear
	void shear(const Matrix& m);

private:
	GeometricObject*	obj_ptr;
	Matrix				inverseMat;
	static 	Matrix		transformation;
	AABB				aabb;
	bool				doTextureTransform;
};

#endif // INSTANCE_H


inline void Instance::texTransform(const bool transform) 
{
	doTextureTransform = transform;
}
