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

Point3D Light::getPos()
{
	return Point3D(0, 0, 0);
}

void Light::setPos(const Point3D& lightPos)
{
}

void Light::setPos(const float x, const float y, const float z)
{

}

RGBColor Light::L(ShadeRec& sr)
{
	return black;
}

bool Light::inShadow(const Ray& ray, const ShadeRec& sr) const
{
	return false;
}

void Light::setShadows(bool s)
{
	shadows = s;
}

bool Light::castShadows()
{
	return true;
}