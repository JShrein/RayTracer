#ifndef PLANE_H
#define PLANE_H

#include "GeometricObject.h"

class ShadeRec;

class Plane : public GeometricObject {
public:
	Plane();
	Plane(const Point3D& p, const Normal& n);
	Plane(const Plane& plane);
	Plane& operator=(const Plane& p);
	virtual ~Plane();
	Plane* clone() const;

	//void set_color(const RGBColor& c);
	//void set_color(const float r, const float g, const float b);

	virtual bool hit(const Ray& ray, double&t, ShadeRec& s) const;
	bool shadowHit(const Ray& ray, double& tMin) const;
	//virtual RGBColor get_color();


private:
	Point3D point;
	Normal normal;
	//RGBColor color;
	static const double kEpsilon;
};

/*
inline void Plane::set_color(const RGBColor& c)
{
	color = c;
}

inline void Plane::set_color(float r, float g, float b)
{
	color = RGBColor(r, g, b);
}

inline RGBColor Plane::get_color()
{
	return color;
}
*/

#endif // PLANE_H