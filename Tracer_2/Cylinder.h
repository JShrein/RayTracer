#ifndef __CYLINDER__
#define __CYLINDER__

#include "GeometricObject.h"

class ShadeRec;

class Cylinder : public GeometricObject {
public:
	Cylinder();
	Cylinder(Point3D center, double r);
	Cylinder(const Cylinder& Cylinder);

	virtual Cylinder* clone() const;
	virtual ~Cylinder();

	Cylinder& operator=(const Cylinder& Cylinder);

	void set_yRange(const double yMin, const double yMax);
	void set_center(const Point3D& c);
	void set_center(const double x, const double y, const double z);
	void set_radius(const double r);
	void set_color(const RGBColor& c);
	void set_color(float r, float g, float b);

	virtual RGBColor get_color();
	virtual bool hit(const Ray& ray, double& t, ShadeRec& s) const;

private:
	double yMinimum;
	double yMaximum;
	Point3D center;
	double radius;
	RGBColor color;

	static const double kEpsilon;
};

inline void Cylinder::set_yRange(const double yMin = 0, const double yMax = 0)
{
	yMinimum = yMin;
	yMaximum = yMax;
}

inline void Cylinder::set_center(const Point3D& c)
{
	center = c;
}

inline void Cylinder::set_center(const double x, const double y, const double z)
{
	center.x = x;
	center.y = y;
	center.z = z;
}

inline void Cylinder::set_radius(const double r)
{
	radius = r;
}

inline void Cylinder::set_color(const RGBColor& c)
{
	color = c;
}

inline void Cylinder::set_color(float r, float g, float b)
{
	color = RGBColor(r, g, b);
}

inline RGBColor Cylinder::get_color()
{
	return color;
}

#endif // __CYLINDER__