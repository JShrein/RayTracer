#include "GlossySpecular.h"

// Constructors
GlossySpecular::GlossySpecular()
	: BRDF(),
	ks(0),
	exp(1.0),
	cd(0)
{ }

GlossySpecular::GlossySpecular(const GlossySpecular& gs)
	: BRDF(gs),
	ks(gs.ks),
	exp(gs.exp),
	cd(gs.cd)
{ }

GlossySpecular::~GlossySpecular()
{ }

GlossySpecular* GlossySpecular::clone() const
{
	return new GlossySpecular(*this);
}

GlossySpecular& GlossySpecular::operator=(const GlossySpecular& gs)
{
	if (this == &gs)
		return *this;

	BRDF::operator=(gs);

	ks = gs.ks;
	exp = gs.exp;
	cd = gs.cd;

	return *this;
}


RGBColor GlossySpecular::f(const ShadeRec& sr, const Vector3D& wo, const Vector3D& wi) const
{
	// wi, n, wo are coplanar (plane of incidence)
	// wo = awi + bn
	// wo . n = (awi + bn) . n = awi . n + bn . n
	// wo . n = awi . n + b, n . n = 1
	// wi . n == wo . n
	// b = wi . n - awi . n, b = (1 - a)wi . n
	// wo . n' = awi . n' + bn . n', n . n' = 0 (n' is perp of n which is ortho to n, and both are unit length)
	// -wi . n' = awi . n' ( wi . n' = -wo . n')
	// a = -1
	// wo = awi + bn
	// wo = -wi + (1 - a)wi . n * n
	// wo = -wi + 2(wi . n) * n
	RGBColor L;		// Outgoing radiance  (defaults to (0,0,0))
	float ndotwi = sr.normal * wi;		// wi.normal == wo.normal, 
	Vector3D r(-wi + 2.0 * sr.normal * ndotwi);		// 
	float rdotwo = r * wo;

	if (rdotwo > 0.0)
	{
		L = ks * pow(rdotwo, exp);
	}
	return L;
}

/*
RGBColor GlossySpecular::sample_f(const ShadeRec& sr, Vector3D& wi, const Vector3D& wo, float& pdf)
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

return ks * cd * INV_PI;b
}
*/
