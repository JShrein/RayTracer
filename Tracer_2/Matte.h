#ifndef __MATTE__
#define __MATTE__

#include "Material.h"
#include "Lambertian.h"

// Matte material
class Matte : public Material {
public:

	Matte(void);
	Matte(const Matte& m);

	virtual Material* clone(void) const;

	Matte& operator= (const Matte& rhs);

	~Matte(void);

	void setKA(const float k);
	void setKD(const float k);
	void setCD(const RGBColor c);
	void setCD(const float r, const float g, const float b);
	void setCD(const float c);
	virtual RGBColor shade(ShadeRec& sr);

private:
	Lambertian*		ambient_brdf;
	Lambertian*		diffuse_brdf;
};


// set ambient term
// Lambertian has no ka, so kd = ka
// Notice ambient_brdf
inline void Matte::setKA(const float ka) 
{
	ambient_brdf->setKA(ka);
}


// // Set diffuse coefficient
inline void Matte::setKD(const float kd) 
{
	diffuse_brdf->setKD(kd);
}

// Set color
inline void Matte::setCD(const RGBColor c) 
{
	ambient_brdf->setCD(c);
	diffuse_brdf->setCD(c);
}

// Set color
inline void Matte::setCD(const float r, const float g, const float b) 
{
	ambient_brdf->setCD(r, g, b);
	diffuse_brdf->setCD(r, g, b);
}

// Set color
inline void Matte::setCD(const float c) 
{
	ambient_brdf->setCD(c);
	diffuse_brdf->setCD(c);
}

#endif