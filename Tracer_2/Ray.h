#ifndef __RAY__
#define __RAY__

#include "Point3D.h"
#include "Vector3D.h"

class Ray {
public:
	Point3D o;											// Ray origin
	Vector3D d;											// Ray direction

	Ray(void);											// Default Constructor
	Ray(const Point3D& origin, const Vector3D& dir);	// Constructor
	Ray(const Ray& ray);								// Copy constructor

	Ray& operator=(const Ray& rhs);						// Assignment operator
			
	~Ray(void);											// Destructor
};

#endif // __RAY__