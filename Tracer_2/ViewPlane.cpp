#include "ViewPlane.h"
#include <iostream>

// Constructors
ViewPlane::ViewPlane()
	: hRes(400),
	vRes(400),
	s(1.0),
    sampler_ptr(NULL),
	numSamples(1),
	rootNumSamples(1),
	gamma(1.0),
	invGamma(1.0),
	showOutOfGamut(false)
{ }

ViewPlane::ViewPlane(const ViewPlane& vp)
	: hRes(vp.hRes),
	vRes(vp.vRes),
	s(vp.s),
	numSamples(vp.numSamples),
	rootNumSamples(vp.rootNumSamples),
	gamma(vp.gamma),
	invGamma(vp.invGamma),
	sampler_ptr(vp.sampler_ptr),
	showOutOfGamut(vp.showOutOfGamut)
{ }


// Assignment operator
ViewPlane& ViewPlane::operator= (const ViewPlane& vp) {
	if (this == &vp)
		return *this;

	hRes = vp.hRes;
	vRes = vp.vRes;
	s = vp.s;
	numSamples = vp.numSamples;
	rootNumSamples = vp.rootNumSamples;
	gamma = vp.gamma;
	invGamma = vp.invGamma;
	sampler_ptr = vp.sampler_ptr;
	showOutOfGamut = vp.showOutOfGamut;

	return *this;
}

// Destructor
ViewPlane::~ViewPlane() {}

void ViewPlane::setSampler(Sampler* sp)
{
	if (sampler_ptr != NULL) {
		delete sampler_ptr;
	    sampler_ptr = NULL;
	}

	rootNumSamples = sp->getRootNumSamples();
	numSamples = sp->getNumSamples();
	sampler_ptr = sp;
}

void ViewPlane::setSamples(const int n)
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
