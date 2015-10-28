#ifndef PINHOLE_MPI_H
#define PINHOLE_MPI_H

//#include "Camera.h"
#include "World.h"
#include "Point2D.h"

class PinholeMPI : public Camera
{
public:
	int rank;
	int size;

public:
	// Constructors
	PinholeMPI(int rank, int size);
	PinholeMPI(const Point3D& eye, const Point3D& look, int rank, int size);
	PinholeMPI(const Point3D& eye, const Point3D& look, const float dist, int rank, int size);
	PinholeMPI(const Point3D& eye, const Point3D& look, const float dist, const float zf, int rank, int size);
	PinholeMPI(const PinholeMPI& p);

	// Destructor
	~PinholeMPI();

	virtual Camera* clone() const;

	PinholeMPI& operator=(const PinholeMPI& p);

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
inline void PinholeMPI::setDistance(const float dist)
{
	d = dist;
}

inline void PinholeMPI::setZoom(const float zf)
{
	zoom = zf;
}

#endif // PINHOLE_MPI_H