#ifndef RGB_COLOR_H
#define RGB_COLOR_H

// <Red, Green, Blue> color representation
// Range[0.0, 1.0]
class RGBColor 
{
public:
	float	r, g, b;

public:
	// Constructors/Destructor
	RGBColor();
	RGBColor(float c);
	RGBColor(float _r, float _g, float _b);
	RGBColor(const RGBColor& c);
	~RGBColor();

	// Operator overloads
	RGBColor& operator= (const RGBColor& c);
	RGBColor operator+ (const RGBColor& c) const;
	RGBColor& operator+= (const RGBColor& c);
	RGBColor operator* (const float a) const;
	RGBColor& operator*= (const float a);
	RGBColor operator/ (const float a) const;
	RGBColor& operator/= (const float a);
	RGBColor operator* (const RGBColor& c) const;
	bool operator== (const RGBColor& c) const;

	// raise components to a power
	RGBColor powc(float p) const;

	// the average of the components
	float average() const;
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
inline float RGBColor::average() const 
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


#endif // RGB_COLOR_H
