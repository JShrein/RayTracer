#ifndef __AMBIENT__
#define __AMBIENT__

#include "Light.h"

class Ambient : public Light 
{
public:
	Ambient();
	Ambient(const Ambient& a);
	virtual Light* clone() const;
	Ambient& operator= (const Ambient& rhs);
	virtual ~Ambient(void);
	void scale_radiance(const float b);
	void setColor(const float c);
	void setColor(const RGBColor& c);
	void setColor(const float r, const float g, const float b);
	virtual Vector3D getDir(ShadeRec& s);
	virtual RGBColor L(ShadeRec& s);

private:

	float		ls;
	RGBColor	color;
};

// Scale Radiance
inline void Ambient::scale_radiance(const float b) 
{
	ls = b;
}

// Set color (grayscale value)
inline void Ambient::setColor(const float c) 
{
	color.r = c; color.g = c; color.b = c;
}

// Set color (RGBColor)
inline void Ambient::setColor(const RGBColor& c) 
{
	color = c;
}

// Set color (float r, g, b)
inline void Ambient::setColor(const float r, const float g, const float b) 
{
	color.r = r;
	color.g = g; 
	color.b = b;
}


#endif