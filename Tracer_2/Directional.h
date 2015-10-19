#ifndef __DIRECTIONAL__
#define __DIRECTIONAL__

#include "Light.h"
#include "Vector3D.h"
#include "RGBColor.h"

#include "World.h"
#include "ShadeRec.h"


class Directional : public Light {
public:
	Directional();
	Directional(const Directional& dl);
	virtual ~Directional(void);

	virtual Directional* clone() const;
	Directional& operator= (const Directional& rhs);

	void scaleRadiance(const float b);
	void setColor(const float c);
	void setColor(const RGBColor& c);
	void setColor(const float r, const float g, const float b);
	void setDir(Vector3D d);
	void setDir(float dx, float dy, float dz);

	virtual Vector3D getDir(ShadeRec& sr);
	virtual RGBColor L(ShadeRec& sr);

private:
	float		ls;
	RGBColor	color;
	Vector3D	dir;		
};


// inline member functions
// Scale radiance
inline void
Directional::scaleRadiance(const float b) 
{
	ls = b;
}

// Set color
inline void Directional::setColor(const float c) 
{
	color.r = c; color.g = c; color.b = c;
}

inline void Directional::setColor(const RGBColor& c) 
{
	color = c;
}

inline void Directional::setColor(const float r, const float g, const float b) 
{
	color.r = r; color.g = g; color.b = b;
}

// Set direction
inline void Directional::setDir(Vector3D d) 
{
	dir = d;
	dir.normalize();
}

inline void Directional::setDir(float dx, float dy, float dz) 
{
	dir.x = dx; dir.y = dy; dir.z = dz;
	dir.normalize();
}


#endif

