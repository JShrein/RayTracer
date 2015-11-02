#include "Lambertian.h"

// Constructors
Lambertian::Lambertian()
	: BRDF(),
	  kd(0),
	  cd(0)
{ }
/*
Lambertian::Lambertian(float diffuseReflectionCoeff, float diffuseColor)
	: BRDF(),
	  kd(diffuseReflectionCoeff),
	  cd(diffuseColor)
{ }
*/
Lambertian::Lambertian(const Lambertian& lamb)
	: BRDF(lamb),
	  kd(lamb.kd),
	  cd(lamb.cd)
{ }

Lambertian::~Lambertian()
{ }

Lambertian* Lambertian::clone() const 
{
	return new Lambertian(*this);
}

Lambertian& Lambertian::operator=(const Lambertian& lamb)
{
	if (this == &lamb)
		return *this;

	BRDF::operator=(lamb);

	kd = lamb.kd;
	cd = lamb.cd;
	
	return *this;
}


/*
RGBColor Lambertian::sample_f(const ShadeRec& sr, Vector3D& wi, const Vector3D& wo, float& pdf)
{
	// Need to get surface normal, from which we will construct orthonormal basis vectors and around which hemisphere is aligned 
	Vector3D w = sr.normal;
	Vector3D v = Vector3D(0.0034, 1, 0.0071) ^ w;
	v.normalize();
	Vector3D u = v ^ w;

	Point3D sp = sampler_ptr->sampleHemisphere();
	wi = sp.x * u + sp.y * v + sp.z * w;
	wi.normalize();

	pdf = sr.normal * wi * INV_PI;

	return kd * cd * INV_PI;b
}
*/

RGBColor Lambertian::rho(const ShadeRec& sr, const Vector3D& wo) const
{
	return kd * cd;
}