#include <math.h>
#include "Point3D.h"
#include "Matrix.h"

// Constructors
Point3D::Point3D()
	: x(0),
	  y(0), 
	  z(0)
{ }

Point3D::Point3D(const double c)
	: x(c), 
	  y(c), 
	  z(c)
{ }

Point3D::Point3D(const double a, const double b, const double c)
	: x(a), 
	  y(b), 
	  z(c)
{ }

Point3D::Point3D(const Point3D& p)
	: x(p.x), 
	  y(p.y), 
	  z(p.z)
{ }

// Destructor
Point3D::~Point3D()
{ }

// Assignment operator
Point3D& Point3D::operator= (const Point3D& p) 
{

	if (this == &p)
		return *this;

	x = p.x; y = p.y; z = p.z;

	return *this;
}

// Euclidean distance between 2 points
double Point3D::distance(const Point3D& p) const 
{
	return sqrt((x - p.x) * (x - p.x) +
		        (y - p.y) * (y - p.y) +
		        (z - p.z) * (z - p.z));
}


// Matrix * Point multiplication
Point3D operator* (const Matrix& mat, const Point3D& p) 
{
	return Point3D(mat.m[0][0] * p.x + mat.m[0][1] * p.y + mat.m[0][2] * p.z + mat.m[0][3],
		           mat.m[1][0] * p.x + mat.m[1][1] * p.y + mat.m[1][2] * p.z + mat.m[1][3],
		           mat.m[2][0] * p.x + mat.m[2][1] * p.y + mat.m[2][2] * p.z + mat.m[2][3]);
}