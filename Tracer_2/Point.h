#ifndef __POINTLIGHT__
#define __POINTLIGHT__

#include "Light.h"
#include "Vector3D.h"
#include "Point3D.h"
#include "RGBColor.h"

#include "World.h"
#include "ShadeRec.h"


class Point : public Light {
public:
	Point();
	Point(const Point& dl);
	virtual ~Point(void);

	virtual Point* clone() const;
	Point& operator= (const Point& rhs);

	void scaleRadiance(const float b);
	void setColor(const float c);
	void setColor(const RGBColor& c);
	void setColor(const float r, const float g, const float b);
	void setPos(const Point3D& d);
	void setPos(float dx, float dy, float dz);

	virtual Vector3D getDir(ShadeRec& sr);
	virtual RGBColor L(ShadeRec& sr);

private:
	float		ls;
	RGBColor	color;
	Vector3D	pos;
};


// inline member functions
// Scale radiance
inline void
Point::scaleRadiance(const float b)
{
	ls = b;
}

// Set color
inline void Point::setColor(const float c)
{
	color.r = c; 
	color.g = c; 
	color.b = c;
}

inline void Point::setColor(const RGBColor& c)
{
	color = c;
}

inline void Point::setColor(const float r, const float g, const float b)
{
	color.r = r; 
	color.g = g; 
	color.b = b;
}

// Set direction
inline void Point::setPos(const Point3D& d)
{
	pos = d;
}

inline void Point::setPos(const float dx, const float dy, const float dz)
{
	pos.x = dx; 
	pos.y = dy; 
	pos.z = dz;
}


#endif // __POINTLIGHT__
