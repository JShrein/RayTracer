#include "ViewPlane.h"

// Constructors
ViewPlane::ViewPlane(void)
	: hres(400),
	vres(400),
	s(1.0),
	numSamples(1),
	rootNumSamples(1),
	gamma(1.0),
	inv_gamma(1.0),
	show_out_of_gamut(false)
{ }

ViewPlane::ViewPlane(const ViewPlane& vp)
	: hres(vp.hres),
	vres(vp.vres),
	s(vp.s),
	numSamples(vp.numSamples),
	rootNumSamples(vp.rootNumSamples),
	gamma(vp.gamma),
	inv_gamma(vp.inv_gamma),
	sampler_ptr(vp.sampler_ptr),
	show_out_of_gamut(vp.show_out_of_gamut)
{ }


// Assignment operator
ViewPlane& ViewPlane::operator= (const ViewPlane& rhs) {
	if (this == &rhs)
		return *this;

	hres = rhs.hres;
	vres = rhs.vres;
	s = rhs.s;
	numSamples = rhs.numSamples;
	rootNumSamples = rhs.rootNumSamples;
	gamma = rhs.gamma;
	inv_gamma = rhs.inv_gamma;
	sampler_ptr = rhs.sampler_ptr;
	show_out_of_gamut = rhs.show_out_of_gamut;

	return *this;
}

// Destructor
ViewPlane::~ViewPlane(void) {}

void ViewPlane::setSampler(Sampler* sp)
{
	if (sampler_ptr) {
		delete sampler_ptr;
		sampler_ptr = NULL;
	}

	rootNumSamples = sp->getRootNumSamples();
	numSamples = sp->getNumSamples();
	sampler_ptr = sp;
}

void ViewPlane::set_samples(const int n)
{
	numSamples = n;
	rootNumSamples = (int)sqrt(n);

	if (sampler_ptr) {
		delete sampler_ptr;
		sampler_ptr = NULL;
	}

	if (numSamples > 1)
	{
		sampler_ptr = new MultiJittered(numSamples);
	}
	else
	{
		sampler_ptr = new Regular(1);
	}
}