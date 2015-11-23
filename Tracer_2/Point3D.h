#ifndef __POINT3D__
#define __POINT3D__

#include "Matrix.h"
#include "Vector3D.h"

class Point3D 
{
public:
	double x, y, z;

	// Constructors/Destructor
	Point3D();
	Point3D(const double a);
	Point3D(const double a, const double b, const double c);
	Point3D(const Point3D& p);
	~Point3D();

	// Operator overloads
	Point3D& operator= (const Point3D& p);
	Point3D operator- () const;
	Vector3D operator- (const Point3D& p) const;
	Point3D operator+ (const Vector3D& v) const;
	Point3D operator- (const Vector3D& v) const;
	Point3D operator* (const double a) const;
	
	// distance functions
	double d_squared(const Point3D& p) const;
	double distance(const Point3D& p) const;
};


// inlined member functions
// Point3D = -Point3D
inline Point3D Point3D::operator- () const 
{
	return Point3D(-x, -y, -z);
}

// Vector3D = Point3D - Point3D
inline Vector3D Point3D::operator- (const Point3D& p) const 
{
	return Vector3D(x - p.x, y - p.y, z - p.z);
}

// Point3D = Point3D + Vector3D
inline Point3D Point3D::operator+ (const Vector3D& v) const 
{
	return Point3D(x + v.x, y + v.y, z + v.z);
}

// Point3D = Point3D - Vector3D
inline Point3D Point3D::operator- (const Vector3D& v) const 
{
	return Point3D(x - v.x, y - v.y, z - v.z);
}

// Point3D = Point3D * double
inline Point3D Point3D::operator* (const double a) const 
{
	return Point3D(x * a, y * a, z * a);
}

// the square of the distance between the two points as a member function
inline double Point3D::d_squared(const Point3D& p) const 
{
	return (x - p.x) * (x - p.x) +
		   (y - p.y) * (y - p.y) +
		   (z - p.z) * (z - p.z);
}




// inlined non-member function
// Point3D = double * Point3D
Point3D operator* (double a, const Point3D& p);
inline Point3D operator* (double a, const Point3D& p)
{
	return Point3D(a * p.x, a * p.y, a * p.z);
}



// non-inlined non-member function
// Point3D = Matrix * Point3D
Point3D operator* (const Matrix& mat, const Point3D& p);

#endif
