#include "Constants.h"
#include "GeometricObject.h"

// Default constructor
GeometricObject::GeometricObject()
{ }

GeometricObject::GeometricObject(const GeometricObject& object)  
{ }

GeometricObject& GeometricObject::operator=(const GeometricObject& rhs) {
	if (this == &rhs)
		return *this;

	return *this;
}

GeometricObject::~GeometricObject() 
{ }


