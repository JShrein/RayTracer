#ifndef LIGHT_H
#define LIGHT_H

#include "Vector3D.h"
#include "ShadeRec.h"
#include "RGBColor.h"

class Light
{
public:
	Light();
	Light(const Light& light);
	Light& operator= (const Light& light);

	// Clone
	virtual Light* clone() const = 0;
	
	//Destructor
	virtual ~Light();
	
	virtual Vector3D getDir(ShadeRec& sr) = 0;
	virtual Point3D getPos();
	virtual void setPos(const Point3D& p);
	virtual void setPos(const float px, const float py, const float pz);
	virtual RGBColor L(ShadeRec& sr);
	virtual bool inShadow(const Ray& ray, const ShadeRec& sr) const;

	void setShadows(bool s);
	bool castShadows() const;

	void setAttenuate(bool a);
	bool doAttenuation() const;

	void setAttenPower(double _p);
	double getAttenPower() const;

protected:
	bool shadows;
	bool attenuate;
	double p; // Attenuateion power
};

#endif // LIGHT_H
