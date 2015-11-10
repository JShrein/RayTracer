#include "Directional.h"

// Constructor
Directional::Directional()
	: Light(),
	ls(1.0),
	color(1.0),
	dir(0, 1, 0)
{ }

Directional::Directional(const Directional& dl)
	: Light(dl),
	ls(dl.ls),
	color(dl.color),
	dir(dl.dir)
{ }

// Clone
Light* Directional::clone() const 
{
	return new Directional(*this);
}

// Assignment operator
Directional& Directional::operator= (const Directional& directional)
{
	if (this == &directional)
		return *this;

	Light::operator= (directional);

	ls = directional.ls;
	color = directional.color;
	dir = directional.dir;

	return *this;
}

// Destructor
Directional::~Directional() 
{ }

// Get direction
Vector3D Directional::getDir(ShadeRec& sr) {
	return dir;
}

// radiance
RGBColor Directional::L(ShadeRec& s) 
{
	return ls * color;
}