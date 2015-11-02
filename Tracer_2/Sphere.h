#ifndef __SPHERE__
#define __SPHERE__

#include "GeometricObject.h"

class ShadeRec;

class Sphere : public GeometricObject {
public:
	Sphere();
	Sphere(Point3D center, double r);
	Sphere(const Sphere& sphere);

	virtual Sphere* clone() const;
	virtual ~Sphere();

	Sphere& operator=(const Sphere& sphere);

	void set_center(const Point3D& c);
	void set_center(const double x, const double y, const double z);
	void set_radius(const double r);
	void set_color(const RGBColor& c);
	void set_color(float r, float g, float b);

	virtual RGBColor get_color();
	virtual bool hit(const Ray& ray, double& t, ShadeRec& s) const;
	bool shadowHit(const Ray& ray, float& tMin) const;

private:
	Point3D center;
	double radius;
	RGBColor color;

	static const double kEpsilon;
};

inline void Sphere::set_center(const Point3D& c)
{
	center = c;
}

inline void Sphere::set_center(const double x, const double y, const double z)
{
	center.x = x;
	center.y = y;
	center.z = z;
}

inline void Sphere::set_radius(const double r)
{
	radius = r;
}

inline void Sphere::set_color(const RGBColor& c)
{
	color = c;
}

inline void Sphere::set_color(float r, float g, float b)
{
	color = RGBColor(r, g, b);
}

inline RGBColor Sphere::get_color()
{
	return color;
}

#endif // __SPHERE__