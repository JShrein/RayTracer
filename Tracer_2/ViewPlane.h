#ifndef VIEWPLANE_H
#define VIEWPLANE_H

#include "Sampler.h"
#include "Hammersley.h"
#include "Jittered.h"
#include "MultiJittered.h"
#include "NRooks.h"
#include "Regular.h"
#include "PureRandom.h"

class ViewPlane 
{
public:
	int hRes;
	int vRes;
	float s;
	int numSamples;
	int rootNumSamples;
	int maxDepth;
	float gamma;
	float invGamma;
	Sampler* sampler_ptr;
	bool showOutOfGamut;

	ViewPlane();
	ViewPlane(const ViewPlane& vp);
	ViewPlane& operator= (const ViewPlane& vp);
	~ViewPlane();

	void setHres(const int hRes);
	void setVres(const int v_res);
	void setPixelSize(const float size);
	void setMaxDepth(const int md);
	void setGamma(const float g);
	void setGamutDisplay(const bool show);

	// Handle sampling
	void setSampler(Sampler* sp);
	void setSamples(const int n);
};

// setHres
inline void ViewPlane::setHres(const int _hRes) 
{
	hRes = _hRes;
}


// setVres
inline void ViewPlane::setVres(const int _vRes) 
{
	vRes = _vRes;
}


// Set pixel size (default 1)
inline void ViewPlane::setPixelSize(const float size) 
{
	s = size;
}

// Set max recursion depth
inline void ViewPlane::setMaxDepth(const int md)
{
	maxDepth = md;
}

// Set gamma correction
inline void ViewPlane::setGamma(const float g) 
{
	gamma = g;
	invGamma = float(1.0 / gamma);
}


// Show pixels that are out of gamut
inline void ViewPlane::setGamutDisplay(const bool show) 
{
	showOutOfGamut = show;
}


#endif // VIEWPLANE_H
