#ifndef POINTLIGHT_H
#define POINTLIGHT_H

#include "Light.h"
#include "Vector3D.h"
#include "Point3D.h"
#include "RGBColor.h"

#include "World.h"
#include "ShadeRec.h"


class PointLight : public Light {
public:
	PointLight();
	PointLight(const PointLight& dl);
	virtual ~PointLight();

	virtual Light* clone() const;
	PointLight& operator= (const PointLight& pLight);

	void scaleRadiance(const float b);
	void setColor(const float c);
	void setColor(const RGBColor& c);
	void setColor(const float r, const float g, const float b);
	
	virtual void setPos(const Point3D& p);
	virtual void setPos(const float px, const float py, const float pz);

	virtual Vector3D getDir(ShadeRec& sr);
	virtual Point3D getPos();
	virtual RGBColor L(ShadeRec& sr);
	
	virtual bool inShadow(const Ray& ray, const ShadeRec& sr) const;

private:
	float ls;
	RGBColor color;
	Point3D pos;
};


// inline member functions
// Scale radiance
inline void
PointLight::scaleRadiance(const float b)
{
	ls = b;
}

// Set color
inline void PointLight::setColor(const float c)
{
	color.r = c; 
	color.g = c; 
	color.b = c;
}

inline void PointLight::setColor(const RGBColor& c)
{
	color = c;
}

inline void PointLight::setColor(const float r, const float g, const float b)
{
	color.r = r; 
	color.g = g; 
	color.b = b;
}

// Set direction
inline void PointLight::setPos(const Point3D& p)
{
	pos = p;
}

inline void PointLight::setPos(const float px, const float py, const float pz)
{
	pos.x = px; 
	pos.y = py; 
	pos.z = pz;
}

#endif // POINTLIGHT_H
