#include "Point.h"

Point::Point()
	: ls(1.0),
	  color(RGBColor(255)),
	  pos(0.0, 0.0, 0.0)
{ }

Point::Point(const Point& dl)
	: ls(dl.ls),
	  color(dl.color),
	  pos(dl.pos)
{ }

Point::~Point(void)
{ }

Point* Point::clone() const
{
	return new Point(*this);
}

Point& Point::operator= (const Point& point)
{
	if (this == &point)
		return *this;

	Light::operator= (point);

	ls = point.ls;
	color = point.color;
	pos = point.pos;

	return *this;
}


Vector3D Point::getDir(ShadeRec& sr)
{
	// get unit direction lightPos - obj hit point
	return (pos - sr.hit_point).hat();
}

Point3D Point::getPos()
{
	return pos;
}

RGBColor Point::L(ShadeRec& sr)
{
	return ls * color;
}

bool Point::inShadow(const Ray& ray, const ShadeRec& sr) const
{
	float t;
	int numObj = sr.w.objects.size();
	float d = pos.distance(ray.o);

	for (int i = 0; i < numObj; i++)
	{
		if (sr.w.objects[i]->shadowHit(ray, t) && t < d)
		{
			return true;
		}
	}
	return false;
}