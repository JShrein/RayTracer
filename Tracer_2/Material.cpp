#include "Material.h"

// Constructors
Material::Material() 
{ }

Material::Material(const Material& m) 
{ }

// Assignment operator
Material& Material::operator= (const Material& mat) 
{
	if (this == &mat)
		return *this;

	return *this;
}

// Destructor
Material::~Material()
{ }

// Shade
RGBColor Material::shade(ShadeRec& sr) 
{
	return black;
}
