// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


#include "Reflective.h"

//  default constructor
Reflective::Reflective()
	: Phong(),
	  reflectiveBRDF(new PerfectSpecular)
{ }


// copy constructor
Reflective::Reflective(const Reflective& rm)
	: Phong(rm) 
{
	if (rm.reflectiveBRDF)
		reflectiveBRDF = rm.reflectiveBRDF->clone();
	else
		reflectiveBRDF = NULL;
}


// assignment operator
Reflective& Reflective::operator= (const Reflective& r) 
{
	if (this == &r)
		return *this;

	Phong::operator=(r);

	if (reflectiveBRDF)
	{
		delete reflectiveBRDF;
		reflectiveBRDF = NULL;
	}

	if (r.reflectiveBRDF)
		reflectiveBRDF = r.reflectiveBRDF->clone();

	return *this;
}


// clone
Reflective* Reflective::clone() const 
{
	return new Reflective(*this);
}


// destructor
Reflective::~Reflective() 
{
	if (reflectiveBRDF)
	{
		delete reflectiveBRDF;
		reflectiveBRDF = NULL;
	}
}


// shade 
RGBColor Reflective::shade(ShadeRec& sr) 
{
	RGBColor L(Phong::shade(sr));  // direct illumination

	Vector3D wo = -sr.ray.d;
	Vector3D wi;
	RGBColor fr = reflectiveBRDF->sample_f(sr, wo, wi);
	Ray reflectedRay(sr.hitPoint, wi);
	//reflectedRay.depth = sr.depth + 1;

	L += fr * sr.w.tracer_ptr->traceRay(reflectedRay, sr.depth + 1) * (sr.normal * wi);

	return (L);
}