#include "Constants.h"
#include "GeometricObject.h"
#include "Material.h"

// Default constructor
GeometricObject::GeometricObject()
{ }

GeometricObject::GeometricObject(const GeometricObject& object)  
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
