#ifndef PERFECT_SPECULAR_H
#define PERFECT_SPECULAR_H

// Perfect specular reflection for indirect illumination
#include "BRDF.h"
#include "Normal.h"

class PerfectSpecular : public BRDF
{
public:
	PerfectSpecular();
	~PerfectSpecular();

	virtual PerfectSpecular* clone() const;

	void setKR(const float k);
	void setCR(const RGBColor& c);
	void setCR(const float r, const float g, const float b);
	void setCR(const float c);

	virtual RGBColor f(const ShadeRec& sr, const Vector3D& wo, const Vector3D& wi) const;
	virtual RGBColor sample_f(const ShadeRec& sr, const Vector3D& wo, Vector3D& wi) const;
	virtual RGBColor sample_f(const ShadeRec& sr, const Vector3D& wo, Vector3D& wi, float& pdf) const;
	virtual RGBColor rho(const ShadeRec& sr, const Vector3D& wo) const;

private:
	float		kr;			// reflection coefficient
	RGBColor 	cr;			// the reflection colour
};


// set reflection coefficient
inline void PerfectSpecular::setKR(const float k)
{
	kr = k;
}

// set color
inline void PerfectSpecular::setCR(const RGBColor& c)
{
	cr = c;
}

// set color
inline void PerfectSpecular::setCR(const float r, const float g, const float b) 
{
	cr.r = r; cr.g = g; cr.b = b;
}

// set color
inline void PerfectSpecular::setCR(const float c) 
{
	cr.r = c; 
	cr.g = c; 
	cr.b = c;
}

#endif // PERFECT_SPECULAR_H

