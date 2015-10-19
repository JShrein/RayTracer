#ifndef __RGB_COLOR__
#define __RGB_COLOR__

// This file contains the declaration of the class RGBColor

//------------------------------------------------------------ class RGBColor

class RGBColor {

public:
	float	r, g, b;

public:
	// Constructors
	RGBColor(void);
	RGBColor(float c);
	RGBColor(float _r, float _g, float _b);
	RGBColor(const RGBColor& c);

	// Destructor
	~RGBColor(void);

	// assignment operator
	RGBColor& operator= (const RGBColor& rhs);

	// addition
	RGBColor operator+ (const RGBColor& c) const;

	// compound addition
	RGBColor& operator+= (const RGBColor& c);

	// multiplication by a float on the right
	RGBColor operator* (const float a) const;

	// compound multiplication by a float on the right
	RGBColor& operator*= (const float a);
	
	// division by a float
	RGBColor operator/ (const float a) const;

	// compound division by a float
	RGBColor& operator/= (const float a);

	// component-wise multiplication
	RGBColor operator* (const RGBColor& c) const;

	// are two RGBColours the same?
	bool operator== (const RGBColor& c) const;

	// raise components to a power
	RGBColor powc(float p) const;

	// the average of the components
	float average(void) const;
};


// inlined member functions

// Addition of colors
inline RGBColor RGBColor::operator+ (const RGBColor& c) const 
{
	return RGBColor(r + c.r, g + c.g, b + c.b);
}

// Aggregate addition of color + color
inline RGBColor& RGBColor::operator+= (const RGBColor& c) 
{
	r += c.r; 
	g += c.g; 
	b += c.b;
	return *this;
}


// Multiply by scalar
inline RGBColor RGBColor::operator* (const float a) const 
{
	return RGBColor(r * a, g * a, b * a);
}


// Aggregate multiplication by scalar
inline RGBColor& RGBColor::operator*= (const float a) {
	r *= a; 
	g *= a; 
	b *= a;
	return *this;
}


// Divide by scalar
inline RGBColor RGBColor::operator/ (const float a) const 
{
	return RGBColor(r / a, g / a, b / a);
}


// Aggregate division by scalar
inline RGBColor& RGBColor::operator/= (const float a) 
{
	r /= a; 
	g /= a; 
	b /= a;
	return *this;
}

// Color * Color
inline RGBColor RGBColor::operator* (const RGBColor& c) const 
{
	return RGBColor(r * c.r, g * c.g, b * c.b);
}


// Comparison operator
inline bool RGBColor::operator== (const RGBColor& c) const 
{
	return (r == c.r && g == c.g && b == c.b);
}


// Get the average of color components
inline float RGBColor::average(void) const 
{
	return float(0.333333333333 * (r + g + b));
}


// inline non-member functions

// scalar * color
RGBColor operator* (const float a, const RGBColor& c);

inline RGBColor operator* (const float a, const RGBColor& c) 
{
	return RGBColor(a * c.r, a * c.g, a * c.b);
}


#endif
