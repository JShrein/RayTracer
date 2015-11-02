#include "Constants.h"
#include "GeometricObject.h"
#include "Material.h"

// Default constructor
GeometricObject::GeometricObject()
	: mat_ptr(NULL)
{ }

GeometricObject::GeometricObject(const GeometricObject& object) 
	: color(object.color),
	  mat_ptr(object.mat_ptr)
{ }

GeometricObject& GeometricObject::operator=(const GeometricObject& obj) {
	if (this == &obj)
		return *this;

	if (mat_ptr)
	{
		delete mat_ptr;
		mat_ptr = NULL;
	}

	if (obj.mat_ptr)
	{
		mat_ptr = obj.mat_ptr->clone();
	}

	return *this;
}

GeometricObject::~GeometricObject() 
{
	if (mat_ptr)
	{
		delete mat_ptr;
		mat_ptr = NULL;
	}
}

void GeometricObject::setMat(Material* material_ptr)
{
	mat_ptr = material_ptr;
}

bool GeometricObject::shadowHit(const Ray& ray, float& tMin) const
{
	return false;
}