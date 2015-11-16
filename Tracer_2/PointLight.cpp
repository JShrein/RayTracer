#include "PointLight.h"

PointLight::PointLight()
	: Light(),
	  ls(1.0),
	  color(RGBColor(255)),
	  pos(0.0, 0.0, 0.0)
{ }

PointLight::PointLight(const PointLight& pl)
	: Light(pl),
	  ls(pl.ls),
	  color(pl.color),
	  pos(pl.pos)
{ }

PointLight::~PointLight()
{ }

Light* PointLight::clone() const
{
	return new PointLight(*this);
}

PointLight& PointLight::operator= (const PointLight& point)
{
	if (this == &point)
		return *this;

	Light::operator= (point);

	ls = point.ls;
	color = point.color;
	pos = point.pos;

	return *this;
}


Vector3D PointLight::getDir(ShadeRec& sr)
{
	// get unit direction lightPos - obj hit point
	return (pos - sr.hitPoint).hat();
}

Point3D PointLight::getPos()
{
	return pos;
}

RGBColor PointLight::L(ShadeRec& sr)
{
	return ls * color;
}

bool PointLight::inShadow(const Ray& ray, const ShadeRec& sr) const
{
	double t;
	int numObj = sr.w.objects.size();
	double d = pos.distance(ray.o);

	for (int i = 0; i < numObj; i++)
	{
		if (sr.w.objects[i]->shadowHit(ray, t) && t < d)
		{
			return true;
		}
	}
	return false;
}