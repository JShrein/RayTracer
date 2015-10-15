#ifndef __RGB_COLOR__
#define __RGB_COLOR__

// This file contains the declaration of the class RGBColor

//------------------------------------------------------------ class RGBColor

class RGBColor {

public:
	float	r, g, b;

public:

	RGBColor(void);										// default constructor
	RGBColor(float c);									// constructor
	RGBColor(float _r, float _g, float _b);				// constructor
	RGBColor(const RGBColor& c); 						// copy constructor

	~RGBColor(void);									// destructor

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

// ----------------------------------------------------------------------- operator+
// addition of two colors

inline RGBColor
RGBColor::operator+ (const RGBColor& c) const {
	return (RGBColor(r + c.r, g + c.g, b + c.b));
}


// ----------------------------------------------------------------------- operator+=
// compound addition of two colors

inline RGBColor&
RGBColor::operator+= (const RGBColor& c) {
	r += c.r; g += c.g; b += c.b;
	return (*this);
}


// ----------------------------------------------------------------------- operator*
// multiplication by a float on the right

inline RGBColor
RGBColor::operator* (const float a) const {
	return (RGBColor(r * a, g * a, b * a));
}


// ----------------------------------------------------------------------- operator*=
// compound multiplication by a float on the right

inline RGBColor&
RGBColor::operator*= (const float a) {
	r *= a; g *= a; b *= a;
	return (*this);
}


// ----------------------------------------------------------------------- operator/
// division by float

inline RGBColor
RGBColor::operator/ (const float a) const {
	return (RGBColor(r / a, g / a, b / a));
}


// ----------------------------------------------------------------------- operator/=
// compound division by float

inline RGBColor&
RGBColor::operator/= (const float a) {
	r /= a; g /= a; b /= a;
	return (*this);
}



// ----------------------------------------------------------------------- operator*
// component-wise multiplication of two colors

inline RGBColor
RGBColor::operator* (const RGBColor& c) const {
	return (RGBColor(r * c.r, g * c.g, b * c.b));
}


// ----------------------------------------------------------------------- operator==
// are two RGBColors the same?

inline bool
RGBColor::operator== (const RGBColor& c) const {
	return (r == c.r && g == c.g && b == c.b);
}


// ----------------------------------------------------------------------- average
// the average of the three components

inline float RGBColor::average(void) const {
	return float((0.333333333333 * (r + g + b)));
}




// inlined non-member function

// ----------------------------------------------------------------------- operator*
// multiplication by a float on the left

RGBColor
operator* (const float a, const RGBColor& c);

inline RGBColor
operator* (const float a, const RGBColor& c) {
	return (RGBColor(a * c.r, a * c.g, a * c.b));
}


#endif
