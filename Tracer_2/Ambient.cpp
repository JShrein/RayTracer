#include "Ambient.h"

// Constructor
Ambient::Ambient()
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
Light* Ambient::clone() const 
{
	return new Ambient(*this);
}

// Assignment operator
Ambient& Ambient::operator= (const Ambient& amb) {
	if (this == &amb)
		return *this;

	Light::operator= (amb);

	ls = amb.ls;
	color = amb.color;

	return *this;
}

// Destructor
Ambient::~Ambient() 
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
