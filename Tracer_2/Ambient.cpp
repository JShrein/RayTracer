#include "Ambient.h"

// Constructor
Ambient::Ambient(void)
	: Light(),
	ls(1.0),
	color(1.0) // White light by default
{ }

Ambient::Ambient(const Ambient& a)
	: Light(a),
	ls(a.ls),
	color(a.color)
{ }

// Clone
Light* Ambient::clone(void) const 
{
	return new Ambient(*this);
}

// Assignment operator
Ambient& Ambient::operator= (const Ambient& rhs) {
	if (this == &rhs)
		return *this;

	Light::operator= (rhs);

	ls = rhs.ls;
	color = rhs.color;

	return *this;
}

// Destructor
Ambient::~Ambient(void) 
{ }

// Get direction
Vector3D Ambient::getDir(ShadeRec& s) {
	return Vector3D(0.0);
}

// radiance
RGBColor Ambient::L(ShadeRec& sr) 
{
	return ls * color;
}
