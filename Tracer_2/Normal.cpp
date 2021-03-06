#include <math.h>
#include "Normal.h"


// default constructor
Normal::Normal()
	: x(0.0), y(0.0), z(0.0)
{}

// constructor
Normal::Normal(double a)
	: x(a), y(a), z(a)
{ }

// constructor
Normal::Normal(double _x, double _y, double _z)
	: x(_x), y(_y), z(_z)
{ }

// copy constructor
Normal::Normal(const Normal& n)
	: x(n.x), y(n.y), z(n.z)
{ }

// constructor
// construct a normal from a vector
Normal::Normal(const Vector3D& v)
	: x(v.x), y(v.y), z(v.z)
{ }

// destructor
Normal::~Normal()
{ }

// operator=
// assignment operator
Normal& Normal::operator= (const Normal& norm) {
	if (this == &norm)
		return *this;

	x = norm.x; y = norm.y; z = norm.z;

	return *this;
}


// operator=
// assignment of a vector to a normal
Normal& Normal::operator= (const Vector3D& vec) 
{
	x = vec.x; y = vec.y; z = vec.z;
	return *this;
}


// operator=
// assignment of a point to a normal
Normal& Normal::operator= (const Point3D& p) {
	x = p.x; y = p.y; z = p.z;
	return *this;
}


// normalize
void Normal::normalize() 
{
	double length = sqrt(x * x + y * y + z * z);
	x /= length; y /= length; z /= length;
}


// non-member function definition

// operator*
// multiplication by a matrix on the left

// a normal is transformed by multiplying it on the left by the transpose of the upper left 3 x 3
// partition of the inverse transformation matrix
Normal operator* (const Matrix& mat, const Normal& n) 
{
	return Normal(mat.m[0][0] * n.x + mat.m[1][0] * n.y + mat.m[2][0] * n.z,
		          mat.m[0][1] * n.x + mat.m[1][1] * n.y + mat.m[2][1] * n.z,
		          mat.m[0][2] * n.x + mat.m[1][2] * n.y + mat.m[2][2] * n.z);
}