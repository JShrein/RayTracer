#include "AmbientOccluder.h"
#include "MultiJittered.h"
#include "World.h"

// Constructor
AmbientOccluder::AmbientOccluder()
	: Light(),
	ls(1.0),
	color(1.0), // White light by default
	minAmt(0.0),
	u(0.0),
	v(0.0),
	w(0.0),
	sampler_ptr(new MultiJittered(64))
{ }

AmbientOccluder::AmbientOccluder(const AmbientOccluder& a)
	: Light(a),
	ls(a.ls),
	color(a.color),
	minAmt(a.minAmt),
	u(a.u),
	v(a.v),
	w(a.w)
{ 
	if (a.sampler_ptr)
		sampler_ptr = a.sampler_ptr->clone();
	else  sampler_ptr = NULL;
}

// Clone
Light* AmbientOccluder::clone() const
{
	return new AmbientOccluder(*this);
}

// Assignment operator
AmbientOccluder& AmbientOccluder::operator= (const AmbientOccluder& a) {
	if (this == &a)
		return *this;

	Light::operator= (a);

	ls = a.ls;
	color = a.color;
	minAmt = a.minAmt;
	u = a.u;
	v = a.v;
	w = a.w;

	if (sampler_ptr) {
		delete sampler_ptr;
		sampler_ptr = NULL;
	}

	if (a.sampler_ptr)
		sampler_ptr = a.sampler_ptr->clone();

	return *this;
}

// Destructor
AmbientOccluder::~AmbientOccluder()
{
	if (sampler_ptr) {
		delete sampler_ptr;
		sampler_ptr = NULL;
	}
}

void AmbientOccluder::setSampler(Sampler* s_ptr)
{
	if (sampler_ptr != NULL) {
		delete sampler_ptr;
		sampler_ptr = NULL;
	}

	rootNumSamples = s_ptr->getRootNumSamples();
	numSamples = s_ptr->getNumSamples();
	sampler_ptr = s_ptr;

	sampler_ptr->mapSamplesToHemisphere(1);
}

bool AmbientOccluder::inShadow(const Ray& ray, const ShadeRec& sr) const
{
	double t;
	int numObj = sr.w.objects.size();

	for (int i = 0; i < numObj; i++)
	{
		if (sr.w.objects[i]->shadowHit(ray, t))
			return true;
	}
	return false;
}

// Get direction
Vector3D AmbientOccluder::getDir(ShadeRec& s) 
{
	Point3D sp = sampler_ptr->sampleHemisphere();
	return sp.x * u + sp.y * v + sp.z * w;
}

// radiance
RGBColor AmbientOccluder::L(ShadeRec& sr)
{
	w = sr.normal;
	v = w ^ Vector3D(0.0072, 1.0, 0.0034); // using a nasty up vector to make sure we maintain linear independence
	v.normalize();
	u = v ^ w;

	Ray shadowRay;
	shadowRay.o = sr.hitPoint;
	shadowRay.d = getDir(sr);

	if (inShadow(shadowRay, sr))
		return minAmt * ls * color;
	return ls * color;
}
