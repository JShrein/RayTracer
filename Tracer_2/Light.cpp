#include "Light.h"

Light::Light()
{ }

Light::Light(const Light& light)
{ }

Light& Light::operator= (const Light& light)
{
	if (this == &light)
		return *this;
	return *this;
}

//Destructor
Light::~Light()
{ }

RGBColor Light::L(ShadeRec& sr)
{
	return black;
}