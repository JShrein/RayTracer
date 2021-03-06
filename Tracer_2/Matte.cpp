#include "Matte.h"

// Constructors
Matte::Matte()
	: Material(),
	  ambient_brdf(new Lambertian),
	  diffuse_brdf(new Lambertian)
{ }

Matte::Matte(const Matte& m)
	: Material(m)
{
	if (m.ambient_brdf)
		ambient_brdf = m.ambient_brdf->clone();
	else  ambient_brdf = NULL;

	if (m.diffuse_brdf)
		diffuse_brdf = m.diffuse_brdf->clone();
	else  diffuse_brdf = NULL;
}

// Clone
Material* Matte::clone() const
{
	return new Matte(*this);
}

// Assignment operator
Matte& Matte::operator= (const Matte& m) 
{
	if (this == &m)
		return *this;

	Material::operator=(m);

	if (ambient_brdf) {
		delete ambient_brdf;
		ambient_brdf = NULL;
	}

	if (m.ambient_brdf)
		ambient_brdf = m.ambient_brdf->clone();

	if (diffuse_brdf) {
		delete diffuse_brdf;
		diffuse_brdf = NULL;
	}

	if (m.diffuse_brdf)
		diffuse_brdf = m.diffuse_brdf->clone();

	return *this;
}

// Destructor
Matte::~Matte() {

	if (ambient_brdf) {
		delete ambient_brdf;
		ambient_brdf = NULL;
	}

	if (diffuse_brdf) {
		delete diffuse_brdf;
		diffuse_brdf = NULL;
	}
}

// Shade
RGBColor Matte::shade(ShadeRec& sr) {
	Vector3D wo = -sr.ray.d;
	RGBColor L = ambient_brdf->rho(sr, wo) * sr.w.ambient_ptr->L(sr);
	int num_lights = sr.w.lights.size();

	for (int j = 0; j < num_lights; j++) 
	{
		Vector3D wi = sr.w.lights[j]->getDir(sr);
		double ndotwi = sr.normal * wi;

		if (ndotwi > 0.0)
		{
			if (sr.w.lights[j]->doAttenuation())
			{
				double r = (sr.w.lights[j]->getPos() - sr.localHitPoint).length();
				r = pow(r, sr.w.lights[j]->getAttenPower());
				L += diffuse_brdf->f(sr, wo, wi) * sr.w.lights[j]->L(sr) / r * ndotwi;
			}
			else
				L += diffuse_brdf->f(sr, wo, wi) * sr.w.lights[j]->L(sr) * ndotwi;
		}
	}

	return L;
}