#ifndef CAMERA_H
#define CAMERA_H

#include "Point3D.h"
#include "Vector3D.h"

class World;

class Camera {
public:
	Camera();
	Camera(Point3D eye, Point3D look);
	Camera(const Camera& c);
	virtual ~Camera();

	virtual Camera* clone() const = 0;

	// Setters/Getters
	void setEyePos(const Point3D& eye);
	void setEyePos(const float x, const float y, const float z);
	void setLookAt(const Point3D& look);
	void setLookAt(const float x, const float y, const float z);
	void setUpVec(const Vector3D& upVec);
	void setUpVec(const float x, const float y, const float z);
	void setRoll(const double rollAngle);
	void setExposureTime(const double expTime);

    Point3D getEyePos();
    Point3D getLookAt();
    double getRoll();

	// Matrix Transformations
	// Translation
	void translate(const Vector3D& trans);
	void translate(const double dx, const double dy, const double dz);
	
    // Rotations
	virtual void rotateX(const double angle);
	virtual void rotateY(const double angle);
	virtual void rotateZ(const double angle);

	void computeUVW();
	virtual void renderScene(World& w) = 0;
protected:
	// Assignment operator
	Camera& operator=(const Camera& c);
	// Camera/Eye position
	Point3D eyePos;
	// Point the camera is looking at
	Point3D lookAt;
	// Up Vector (0, 1, 0) 
	Vector3D up;
	// Orthonormal Basis Vectors
	Vector3D u;
	Vector3D v;
	Vector3D w;
	// The aptly named exposure time
	double exposureTime;
	// roll angle for rotation about w vector
	double roll;
};

// Inline member functions

inline void Camera::setEyePos(const Point3D& eye)
{
	eyePos = eye;
}

inline void Camera::setEyePos(const float x, const float y, const float z)
{
	eyePos.x = x;
	eyePos.y = y;
	eyePos.z = z;
}

inline void Camera::setLookAt(const Point3D& look)
{
	lookAt = look;
}

inline void Camera::setLookAt(const float x, const float y, const float z)
{
	lookAt.x = x;
	lookAt.y = y;
	lookAt.z = z;
}

inline void Camera::setUpVec(const Vector3D& upVec)
{
	up = upVec;
}

inline void Camera::setUpVec(const float x, const float y, const float z)
{
	up.x = x;
	up.y = y;
	up.z = z;
}

inline void Camera::setRoll(const double rollAngle)
{
	roll = rollAngle;
}

inline void Camera::setExposureTime(const double expTime)
{
	exposureTime = expTime;
}

inline Point3D Camera::getEyePos()
{
    return eyePos;
}

inline Point3D Camera::getLookAt()
{
    return lookAt;
}

#endif // CAMERA_H
