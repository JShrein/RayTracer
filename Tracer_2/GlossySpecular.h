#ifndef GLOSSY_SPECULAR_H
#define GLOSSY_SPECULAR_H

#include "BRDF.h"

class GlossySpecular : public BRDF
{
public:
	GlossySpecular();
	GlossySpecular(const GlossySpecular& gs);
	~GlossySpecular();

	virtual GlossySpecular* clone() const;
	GlossySpecular& operator=(const GlossySpecular& gs);

	void setKS(const float specCoeff);								// Specular Coefficient
	void setEXP(const float specExp);								// Specular Exponent
	void setCD(const RGBColor& color);								// Specular color
	void setCD(const float r, const float g, const float b);		// Specular Color
	void setCD(const float c);										// Specular Color

	virtual RGBColor f(const ShadeRec& sr, const Vector3D& wo, const Vector3D& wi) const;
	// PDF is probability distribution function
	//virtual RGBColor sample_f(const ShadeRec& sr, Vector3D& wi, const Vector3D& wo, float& pdf);
private:
	// Specular Reflection Coefficient
	float ks;
	// Specular Color
	RGBColor cd;
	// Specular exponent
	float exp;
};

inline void GlossySpecular::setKS(const float specCoeff)
{
	ks = specCoeff;
}

inline void GlossySpecular::setEXP(const float specExp)
{
	exp = specExp;
}

inline void GlossySpecular::setCD(const RGBColor& color)
{
	cd = color;
}

inline void GlossySpecular::setCD(const float r, const float g, const float b)
{
	cd.r = r;
	cd.g = g;
	cd.b = b;
}

inline void GlossySpecular::setCD(const float c)
{
	cd.r = c;
	cd.g = c;
	cd.b = c;
}

#endif // GLOSSY_SPECULAR_H