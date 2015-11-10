#ifndef PINHOLE_H
#define PINHOLE_H

//#include "Camera.h"
#include "World.h"
#include "Point2D.h"

class Pinhole : public Camera
{
public:
	// Constructors
	Pinhole();
	Pinhole(const Point3D& eye, const Point3D& look);
	Pinhole(const Point3D& eye, const Point3D& look, const float dist);
	Pinhole(const Point3D& eye, const Point3D& look, const float dist, const float zf);
	Pinhole(const Pinhole& p);
	
	// Destructor
	~Pinhole();

	virtual Camera* clone() const;

	Pinhole& operator=(const Pinhole& p);

	// Setters/Getters
	void setDistance(const float dist);
	void setZoom(const float zf);
	Vector3D getDir(const Point2D& p) const;

	virtual void renderScene(World& w);
private:
	// Viewplane distance
	float d;
	// zoom factor
	float zoom;
};

// Inline member functions
inline void Pinhole::setDistance(const float dist)
{
	d = dist;
}

inline void Pinhole::setZoom(const float zf)
{
	zoom = zf;
}

#endif // PINHOLE_H