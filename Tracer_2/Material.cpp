#include "Material.h"

// Constructors
Material::Material() 
{ }

Material::Material(const Material& m) 
{ }

// Assignment operator
Material& Material::operator= (const Material& rhs) 
{
	if (this == &rhs)
		return *this;

	return *this;
}

// Destructor
Material::~Material(void)
{ }

// Shade
RGBColor Material::shade(ShadeRec& sr) 
{
	return (black);
}
