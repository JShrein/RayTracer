#ifndef BRDF_H
#define BRDF_H

#include "ShadeRec.h"
#include "Sampler.h"
#include "Vector3D.h"
#include "RGBColor.h"

class BRDF 
{
public:
	BRDF();
	BRDF(const BRDF& brdf);
	virtual ~BRDF();

	virtual BRDF* clone()const = 0;
	BRDF& operator=(const BRDF& brdf);

	// Need a pointer to a sampler
	void set_sampler(Sampler* sp);

	// f returns BRDF itself (unless it contains Dirac delta function)
	// Constant of proportionality, wi (omega i) = irradiance (incoming light), wo (omega o) = radiance (outgoing light)
	virtual RGBColor f(const ShadeRec& sr, const Vector3D& wi, const Vector3D& wo) const;

	// Compute direction of reflected rays for simulating reflective materials and diffuse-diffuse light transport
	// wi not constant because we will use it to return direction wi
	virtual RGBColor sample_f(const ShadeRec& sr, Vector3D& wi, const Vector3D& wo, float& pdf) const;
	virtual RGBColor sample_f(const ShadeRec& sr, Vector3D& wi, const Vector3D& wo) const;

	// Returns bihemispheral reflectance (rho_hh)
	virtual RGBColor rho(const ShadeRec& sr, const Vector3D& wo) const;

protected:
	Sampler* sampler_ptr;
};

#endif // BRDF_H