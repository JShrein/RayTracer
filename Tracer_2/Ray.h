#ifndef RAY_H
#define RAY_H

#include "Point3D.h"
#include "Vector3D.h"

class Ray {
public:
	// Ray origin
	Point3D o;
	// Ray direction
	Vector3D d;

public:
	// Constructors/Destructor
	Ray();
	Ray(const Point3D& origin, const Vector3D& dir);
	Ray(const Ray& ray);
	~Ray();

	// operator overloads
	Ray& operator=(const Ray& ray);
};

#endif // RAY_H