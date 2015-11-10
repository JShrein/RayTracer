#ifndef VECTOR3D_H
#define VECTOR3D_H

class Matrix;
class Normal;
class Point3D;

class Vector3D 
{
public:
	double	x, y, z;

public:
	// Constructors/Destructor
	Vector3D();
	Vector3D(double a);
	Vector3D(double x, double y, double z);
	Vector3D(const Vector3D& v);
	Vector3D(const Normal& n);
	Vector3D(const Point3D& p);
	~Vector3D();

	// Operator overloads
	Vector3D& operator= (const Vector3D& vec);
	Vector3D& operator= (const Normal& norm);
	Vector3D& operator= (const Point3D& p);
	Vector3D operator- () const;
	Vector3D operator* (const double a) const;
	Vector3D operator/ (const double a) const;
	Vector3D operator+ (const Vector3D& v) const;
	Vector3D& operator+= (const Vector3D& v);
	Vector3D operator- (const Vector3D& v) const;

	// Dot Product
	double operator* (const Vector3D& b) const;
	// Cross Product
	Vector3D operator^ (const Vector3D& v) const;

	// Vector magnitude and squared length
	double length();
	double len_squared();

	// Normalize vector
	void normalize();
	// Normalize and return vector
	Vector3D& hat();
};


// inlined member functions

// unary minus
// reverse and return NEW vector (does not change current vector)
// this allows ShadeRec objects to be declared as constant arguments in many shading
// functions that reverse the direction of a ray that's stored in the ShadeRec object
inline Vector3D Vector3D::operator- () const 
{
	return Vector3D(-x, -y, -z);
}

// Squared vector magnitude
inline double Vector3D::len_squared() 
{
	return x * x + y * y + z * z;
}

// Vector3D = Vector3D * double
inline Vector3D Vector3D::operator* (const double a) const 
{
	return Vector3D(x * a, y * a, z * a);
}

// Vector3D = Vector3D / double
inline Vector3D Vector3D::operator/ (const double a) const 
{
	return Vector3D(x / a, y / a, z / a);
}

// Vector3D = Vector3D + Vector3D
inline Vector3D Vector3D::operator+ (const Vector3D& v) const
{
	return Vector3D(x + v.x, y + v.y, z + v.z);
}

// Vector3D = Vector3D - Vector3D
inline Vector3D Vector3D::operator- (const Vector3D& v) const
{
	return Vector3D(x - v.x, y - v.y, z - v.z);
}

// Vector dot product
inline double Vector3D::operator* (const Vector3D& v) const 
{
	return x * v.x + y * v.y + z * v.z;
}

// Vector cross product
inline Vector3D Vector3D::operator^ (const Vector3D& v) const 
{
	return Vector3D(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
}

// // Vector3D += Vector3D
inline Vector3D& Vector3D::operator+= (const Vector3D& v) 
{
	x += v.x; y += v.y; z += v.z;
	return *this;
}


// inlined non-member function

// Vector3D = double * Vector3D
Vector3D operator* (const double a, const Vector3D& v);
inline Vector3D operator* (const double a, const Vector3D& v)
{
	return Vector3D(a * v.x, a * v.y, a * v.z);
}


// non-inlined non-member function
// Vector3D = Matrix * Vector3D
Vector3D operator* (const Matrix& mat, const Vector3D& v);

#endif // VECTOR3D_H