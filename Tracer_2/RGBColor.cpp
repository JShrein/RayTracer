#include <math.h>
#include "RGBColor.h"

// Constructors
RGBColor::RGBColor()
	: r(0.0), 
	  g(0.0), 
	  b(0.0)
{ }

RGBColor::RGBColor(float c)
	: r(c), 
	  g(c), 
	  b(c)
{ }

RGBColor::RGBColor(float _r, float _g, float _b)
	: r(_r), 
	  g(_g), 
	  b(_b)
{ }

RGBColor::RGBColor(const RGBColor& c)
	: r(c.r), 
	  g(c.g), 
	  b(c.b)
{ }


// Destructor
RGBColor::~RGBColor()
{ }


// Assignment operator
RGBColor& RGBColor::operator= (const RGBColor& rhs) 
{
	if (this == &rhs)
		return *this;

	r = rhs.r; 
	g = rhs.g; 
	b = rhs.b;

	return *this;
}


// Raise each color component to power p
RGBColor RGBColor::powc(float p) const 
{
	return RGBColor(pow(r, p), pow(g, p), pow(b, p));
}