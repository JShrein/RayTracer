#include "Constants.h"
#include "GeometricObject.h"
#include "Material.h"

// Default constructor
GeometricObject::GeometricObject()
	: mat_ptr(NULL)
{ }

GeometricObject::GeometricObject(const GeometricObject& object) 
	: mat_ptr(object.mat_ptr)
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

bool GeometricObject::shadowHit(const Ray& ray, double& tMin) const
{
	return false;
}

void GeometricObject::addObject(GeometricObject* object_ptr) 
{ }

// set axis-aligned bounding box
void GeometricObject::setAABB() 
{ }

// get axis-aligned bounding box
AABB GeometricObject::getAABB() 
{
	return AABB();
}