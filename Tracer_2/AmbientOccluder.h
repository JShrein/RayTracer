#ifndef AMBIENT_OCCLUDER_H
#define AMBIENT_OCCLUDER_H

#include "Light.h"
#include "Sampler.h"

#include "ShadeRec.h"

class AmbientOccluder : public Light
{
public:
	AmbientOccluder();
	AmbientOccluder(const AmbientOccluder& a);
	virtual Light* clone() const;
	AmbientOccluder& operator= (const AmbientOccluder& ao);
	virtual ~AmbientOccluder();

	void scale_radiance(const float b);
	void setColor(const float c);
	void setColor(const RGBColor& c);
	void setColor(const float r, const float g, const float b);
	void setMinAmt(const float c);

	void setSampler(Sampler* sampler_ptr);
	virtual bool inShadow(const Ray& ray, const ShadeRec& sr) const;
	virtual Vector3D getDir(ShadeRec& s);
	virtual RGBColor L(ShadeRec& s);

private:
	Vector3D	u, v, w;  // Will compute orthonormal basis for hit point
	Sampler*	sampler_ptr;
	int			numSamples;
	int			rootNumSamples;
	float		ls;
	float		minAmt;	// Instead of just returning black, use some min amount of color.  More realistic since some light will usually reach occluded area
	RGBColor	color;
};

// Scale Radiance
inline void AmbientOccluder::scale_radiance(const float b)
{
	ls = b;
}

// Set color (grayscale value)
inline void AmbientOccluder::setColor(const float c)
{
	color.r = c; color.g = c; color.b = c;
}

// Set color (RGBColor)
inline void AmbientOccluder::setColor(const RGBColor& c)
{
	color = c;
}

// Set color (float r, g, b)
inline void AmbientOccluder::setColor(const float r, const float g, const float b)
{
	color.r = r;
	color.g = g;
	color.b = b;
}

inline void AmbientOccluder::setMinAmt(const float c)
{
	minAmt = c;
}

#endif // AMBIENT_OCCLUDER_H