#include "Light.h"

Light::Light()
	: attenuate(false),
	  shadows(false),
	  p(0)
{ }

Light::Light(const Light& light)
	: attenuate(light.attenuate),
	  shadows(light.shadows),
	  p(light.p)
{ }

Light& Light::operator= (const Light& light)
{
	if (this == &light)
		return *this;

	attenuate = light.attenuate;
	shadows = light.shadows;
	p = light.p;

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

bool Light::castShadows() const
{
	return shadows;
}

void Light::setAttenuate(bool a)
{
	attenuate = a;
}

bool Light::doAttenuation() const
{
	return attenuate;
}

void Light::setAttenPower(double _p)
{
	p = _p;
}

double Light::getAttenPower() const
{
	return p;
}