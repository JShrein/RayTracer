#ifndef LAMBERTIAN_H
#define LAMBERTIAN_H

#include "BRDF.h"

class Lambertian : public BRDF
{
public:
	Lambertian();
	//Lambertian(float diffuseReflectionCoeff, float diffuseColor);
	Lambertian(const Lambertian& lamb);
	~Lambertian();

	virtual Lambertian* clone() const;
	Lambertian& operator=(const Lambertian& lamb);

	void setKA(const float ka);
	void setKD(const float diffuseCoefficient);
	void setCD(const RGBColor& color);
	void setCD(const float r, const float g, const float b);
	void setCD(const float c);

	virtual RGBColor f(const ShadeRec& sr, const Vector3D& wo, const Vector3D& wi) const;
	// PDF is probability distribution function
	//virtual RGBColor sample_f(const ShadeRec& sr, Vector3D& wi, const Vector3D& wo, float& pdf);
	virtual RGBColor rho(const ShadeRec& sr, const Vector3D& wo) const;
private:
	// Diffuse Reflection Coefficient
	float kd;
	// Diffuse Color
	RGBColor cd;
};

inline void Lambertian::setKA(const float diffuseCoefficient)
{
	kd = diffuseCoefficient;
}

inline void Lambertian::setKD(const float diffuseCoefficient)
{
	kd = diffuseCoefficient;
}

inline void Lambertian::setCD(const RGBColor& color)
{
	cd = color;
}

inline void Lambertian::setCD(const float r, const float g, const float b)
{
	cd.r = r;
	cd.g = g;
	cd.b = b;
}

inline void Lambertian::setCD(const float c)
{
	cd.r = c;
	cd.g = c;
	cd.b = c;
}

inline RGBColor Lambertian::f(const ShadeRec& sr, const Vector3D& wo, const Vector3D& wi) const
{
	return kd * cd * (float)INV_PI;
}


#endif // LAMBERTIAN_H