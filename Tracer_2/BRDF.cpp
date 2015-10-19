#include "BRDF.h"

// Constructors
BRDF::BRDF()
	: sampler_ptr(NULL)
{ }

BRDF::BRDF(const BRDF& brdf)
{
	if (brdf.sampler_ptr)
		sampler_ptr = brdf.sampler_ptr->clone();
	else
		sampler_ptr = NULL;
}

BRDF::~BRDF()
{
	if (sampler_ptr)
	{
		delete sampler_ptr;
		sampler_ptr = NULL;
	}
}

BRDF& BRDF::operator=(const BRDF& brdf)
{
	if (this == &brdf)
		return *this;

	if (sampler_ptr) 
	{
		delete sampler_ptr;
		sampler_ptr = NULL;
	}

	if (brdf.sampler_ptr)
		sampler_ptr = brdf.sampler_ptr->clone();

	return *this;
}


void BRDF::set_sampler(Sampler* sp)
{
	sampler_ptr = sp;
	// Let e = 1 for perfect diffuse BRDF
	sampler_ptr->mapSamplesToHemisphere(1);
}

// IN GENERAL WILL WANT TO USE SUBCLASS OF BRDF, BUT MAY USE BRDF FOR MATTE 

// f returns BRDF itself (unless it contains Dirac delta function)
// Constant of proportionality, wi (omega i) = irradiance (incoming light), wo (omega o) = radiance (outgoing light)
RGBColor BRDF::f(const ShadeRec& sr, const Vector3D& wi, const Vector3D& wo) const
{
	return red;  
}

// Compute direction of reflected rays for simulating reflective materials and diffuse-diffuse light transport
// wi not constant because we will use it to return direction wi
RGBColor BRDF::sample_f(const ShadeRec& sr, Vector3D& wi, const Vector3D& wo, float& pdf) const
{
	return red;
}

RGBColor BRDF::sample_f(const ShadeRec& sr, Vector3D& wi, const Vector3D& wo) const
{
	return red;
}

// Returns bihemispheral reflectance (rho_hh)
RGBColor BRDF::rho(const ShadeRec& sr, const Vector3D& wo) const
{
	return red;
}
