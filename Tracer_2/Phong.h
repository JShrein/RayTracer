#ifndef PHONG_H
#define PHONG_H

#include "Material.h"
#include "Lambertian.h"
#include "GlossySpecular.h"

class Phong : public Material
{
public:
	Phong();
	Phong(const Phong& p);

	virtual Material* clone() const;

	Phong& operator= (const Phong& p);

	~Phong();

	void setKA(const float k);
	void setKD(const float k);
	void setKS(const float k);
	void setEXP(const float k);
	void setCD(const RGBColor c);
	void setCD(const float r, const float g, const float b);
	void setCD(const float c);
	virtual RGBColor shade(ShadeRec& sr);

private:
	Lambertian*		ambient_brdf;
	Lambertian*		diffuse_brdf;
	GlossySpecular* specular_brdf;
};

// set ambient term
// Lambertian has no ka, so kd = ka
// Notice ambient_brdf
inline void Phong::setKA(const float ka)
{
	ambient_brdf->setKA(ka);
}


// Set diffuse coefficient
inline void Phong::setKD(const float kd)
{
	diffuse_brdf->setKD(kd);
}

// Set specular coefficient
inline void Phong::setKS(const float ks)
{
	specular_brdf->setKS(ks);
}

inline void Phong::setEXP(const float e)
{
	specular_brdf->setEXP(e);
}

// Set color
inline void Phong::setCD(const RGBColor c)
{
	ambient_brdf->setCD(c);
	diffuse_brdf->setCD(c);
}

// Set color
inline void Phong::setCD(const float r, const float g, const float b)
{
	ambient_brdf->setCD(r, g, b);
	diffuse_brdf->setCD(r, g, b);
}

// Set color
inline void Phong::setCD(const float c)
{
	ambient_brdf->setCD(c);
	diffuse_brdf->setCD(c);
}

#endif // PHONG_H
